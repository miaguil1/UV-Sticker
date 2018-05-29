package com.example.intern.ble_ex1;

import android.bluetooth.BluetoothGattCharacteristic;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.graphics.Color;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.LineGraphSeries;
import com.jjoe64.graphview.series.DataPoint;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class MainActivity extends AppCompatActivity
{
    private final static String TAG = MainActivity.class.getSimpleName();

    public static final String EXTRAS_DEVICE_NAME = "DEVICE_NAME";
    public static final String EXTRAS_DEVICE_ADDRESS = "DEVICE_ADDRESS";

    private String mDeviceStatus;
    private String mDeviceName;
    private String mDeviceAddress;

    private BluetoothLeService mBluetoothLeService;
    private BluetoothGattCharacteristic mNotifyCharacteristic;

    private final String LIST_NAME = "NAME";
    private final String LIST_UUID = "UUID";

    private boolean mConnectionState = false;

    private boolean temp_Notification = false;
    private boolean uv_Notification = false;
    private boolean battery_Notification = false;

    private boolean temp_streaming = false;
    private boolean uv_streaming = false;
    private boolean battery_streaming = false;

    private CheckBox uv_CheckBox;
    private CheckBox temp_CheckBox;
    private CheckBox battery_CheckBox;

    private LineGraphSeries<DataPoint> temp_series;
    private LineGraphSeries<DataPoint> battery_series;
    private LineGraphSeries<DataPoint> uv_series;
    private GraphView dataGraph;

    private static TextView temperatureValue;

    private DataPoint[] temp_data;

    private double counter;
    private int maxDataSet;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content_main);

        mDeviceStatus = "Connected";
        counter = 0;
        maxDataSet = 10000;

        mBluetoothLeService = new BluetoothLeService();     //Initializing Bluetooth Service Object

        final Intent startIntent = getIntent();
        mDeviceName = startIntent.getStringExtra(EXTRAS_DEVICE_NAME);    //Get Device Name from Previous Intent
        mDeviceAddress = startIntent.getStringExtra(EXTRAS_DEVICE_ADDRESS);  //Get Device Address from Previous Intent

        ((TextView) findViewById(R.id.ble_device_name_connected)).setText(mDeviceName); //Sets the Text of the Device name
        ((TextView) findViewById(R.id.ble_device_address_connected)).setText(mDeviceAddress);   //Sets the Text of the Device Address
        ((TextView) findViewById(R.id.ble_device_status)).setText(mDeviceStatus);   //Sets the Text of the Device Connection Status

        Intent gattServiceIntent = new Intent(this, BluetoothLeService.class);  //Creates an intent for the Bluetooth Service
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);   //Binds Service to the Gatt Service

        Log.d(TAG, String.format("UV: %s",mDeviceAddress));
        Log.d(TAG, String.format("UV: %s",mDeviceName));
        Boolean connectionString = mBluetoothLeService.connect(mDeviceAddress);    //Connect to BLE Device on Creation
        Log.d(TAG, String.format("UV: Connection State %b",connectionString));

        //Connect U.I Elements
        temp_CheckBox = (CheckBox) findViewById(R.id.temp_check);  //Temperature Checkbox
        uv_CheckBox = (CheckBox) findViewById(R.id.uv_check);      //UV Checkbox
        battery_CheckBox = (CheckBox) findViewById(R.id.battery_check);  //Respiration Checkbox

        Button start_Button = (Button) findViewById(R.id.startBtn);         //Start button to start graphing and enable notifications of Selected Values
        Button stop_Button = (Button) findViewById(R.id.stopBtn);           //Stop button to stop graphing and disable notifications of Selected Values
        Button save_Button = (Button) findViewById(R.id.saveBtn);           //Save button to save data from enabled graph and Selected Values

        temperatureValue = (TextView) findViewById(R.id.temp_value);        //Initializing Textview to display BLE Temperature Data

        temp_data = new DataPoint[1];
        temp_data[0] = new DataPoint(0,0);

        dataGraph = (GraphView) findViewById(R.id.graph);             //Graphview to Display Data
        //Initializing Temperature Dataset on Graph
        temp_series = new LineGraphSeries<>(temp_data);
        temp_series.setTitle("Temperature");
        temp_series.setColor(Color.RED);
        temp_series.setThickness(8);
        temp_series.setDrawDataPoints(true);        //Setting Data Points to be visible on graph
        temp_series.setDataPointsRadius(5);         //Setting the radius of the Data Point
        dataGraph.addSeries(temp_series);
        dataGraph.getViewport().setYAxisBoundsManual(true);
        dataGraph.getViewport().setMinY(20);
        dataGraph.getViewport().setMaxY(32);

        dataGraph.getViewport().setXAxisBoundsManual(true);
        dataGraph.getViewport().setMinX(0);
        dataGraph.getViewport().setMaxX(10);

        dataGraph.getViewport().setScrollable(true);    //Enable Horizontal Scrolling
//        uv_series = new LineGraphSeries<>(new DataPoint[] {});
//        temp_series.setTitle("UV Power Density");
//        temp_series.setColor(Color.BLUE);
//        temp_series.setThickness(8);
//        dataGraph.addSeries(uv_series);
//
//        battery_series = new LineGraphSeries<>(new DataPoint[] {});
//        battery_series.setTitle("Respiration");
//        battery_series.setColor(Color.GREEN);
//        battery_series.setThickness(8);
//        dataGraph.addSeries(battery_series);

        buttonClicked(start_Button, stop_Button, save_Button);
        checkClicked(temp_CheckBox, uv_CheckBox, battery_CheckBox);
    }

    @Override
    protected void onResume()
    {
        Log.d(TAG, "UV: onResume");
        super.onResume();
        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
        if (mBluetoothLeService != null)
        {
            final boolean result = mBluetoothLeService.connect(mDeviceAddress);
            Log.d(TAG, "UV: Connect request result=" + result);
        }
    }

    @Override
    protected void onPause()
    {
        Log.d(TAG, "UV: onPause");
        super.onPause();
        unregisterReceiver(mGattUpdateReceiver);
    }

    @Override
    protected void onDestroy()
    {
        Log.d(TAG, "UV: onDestroy");
        super.onDestroy();
        mBluetoothLeService.close();
        unbindService(mServiceConnection);
        mBluetoothLeService = null;
//        mServiceConnection = false;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        if (mConnectionState)
        {
            menu.findItem(R.id.menu_connect).setVisible(false);
            menu.findItem(R.id.menu_disconnect).setVisible(true);
        }
        else
        {
            menu.findItem(R.id.menu_connect).setVisible(true);
            menu.findItem(R.id.menu_disconnect).setVisible(false);
        }
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch(item.getItemId())
        {
            case R.id.menu_connect:
                mBluetoothLeService.connect(mDeviceAddress);
                return true;
            case R.id.menu_disconnect:
                mBluetoothLeService.disconnect();
                return true;
            case android.R.id.home:
                onBackPressed();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void buttonClicked(Button start_Button, Button stop_Button, Button save_Button)
    {
        start_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                mBluetoothLeService.writeCharacteristicNotification(uv_Notification, temp_Notification, battery_Notification);
//                startGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        stop_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                uv_Notification = false;
                temp_Notification = false;
                battery_Notification = false;
                if(uv_CheckBox.isChecked())
                {
                    uv_CheckBox.setChecked(uv_Notification);
                }
                if(temp_CheckBox.isChecked())
                {
                    temp_CheckBox.setChecked(temp_Notification);
                }
                if(battery_CheckBox.isChecked())
                {
                    battery_CheckBox.setChecked(battery_Notification);
                }
                mBluetoothLeService.writeCharacteristicNotification(uv_Notification, temp_Notification, battery_Notification);
                //stopGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        save_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                uv_Notification = false;
                temp_Notification = false;
                battery_Notification = false;
                mBluetoothLeService.writeCharacteristicNotification(uv_Notification, temp_Notification, battery_Notification);
                //saveGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
    }

    private void checkClicked(CheckBox temp_CheckBox, CheckBox uv_CheckBox, CheckBox battery_CheckBox)
    {
        temp_CheckBox.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(((CheckBox)view).isChecked())
                {
                    temp_Notification = true;
                }
                else
                {
                    temp_Notification = false;
                }
            }

        });
        uv_CheckBox.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(((CheckBox)view).isChecked())
                {
                    uv_Notification = true;
                }
                else
                {
                    uv_Notification = false;
                }
            }

        });
        battery_CheckBox.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(((CheckBox)view).isChecked())
                {
                    battery_Notification = true;
                }
                else
                {
                    battery_Notification = false;
                }
            }

        });
    }

    private void updateConnectionState(final int resourceId)
    {
        runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                ((TextView) findViewById(R.id.ble_device_status)).setText(resourceId);   //Sets the Text of the Device Connection Status
            }
        });
    }

    private static IntentFilter makeGattUpdateIntentFilter()
    {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_CONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED);
        intentFilter.addAction(BluetoothLeService.ACTION_DATA_AVAILABLE);
        return intentFilter;
    }

    // Code to manage Service lifecycle.
    private final ServiceConnection mServiceConnection = new ServiceConnection()
    {

        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service)
        {
            mBluetoothLeService = ((BluetoothLeService.LocalBinder) service).getService();
            if (!mBluetoothLeService.initialize())
            {
                Log.d(TAG, "Unable to initialize Bluetooth");
                finish();
            }
            // Automatically connects to the device upon successful start-up initialization.
            mBluetoothLeService.connect(mDeviceAddress);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName)
        {
            mBluetoothLeService = null;
        }
    };

    // Handles various events fired by the Service.
    // ACTION_GATT_CONNECTED: connected to a GATT server.
    // ACTION_GATT_DISCONNECTED: disconnected from a GATT server.
    // ACTION_GATT_SERVICES_DISCOVERED: discovered GATT services.
    // ACTION_DATA_AVAILABLE: received data from the device.  This can be a result of read
    //                        or notification operations.
    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            final String action = intent.getAction();
            switch(action)
            {
                case BluetoothLeService.ACTION_GATT_CONNECTED:
                    mConnectionState = true;
                    updateConnectionState(R.string.connected);
                    invalidateOptionsMenu();
                    Log.d(TAG, "UV: BLE GATT Connected");
                    break;

                case BluetoothLeService.ACTION_GATT_DISCONNECTED:
                    mConnectionState = false;
                    updateConnectionState(R.string.disconnected);
                    invalidateOptionsMenu();
                    Log.d(TAG, "UV: BLE GATT Disconnected");
                    break;

                case BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED:
                    // Show all the supported services and characteristics on the user interface.
//                displayGattServices(mBluetoothLeService.getSupportedGattServices());
                    Log.d(TAG, "UV: BLE GATT Services Discovered");
                    break;
                case BluetoothLeService.ACTION_DATA_AVAILABLE:
                    Log.d(TAG, "UV: BLE GATT Action Data Available");
//                    displayData(intent.getStringExtra(BluetoothLeService.EXTRA_DATA));
                    String gattTemperatureValue = mBluetoothLeService.getmTemperatureValue();
                    if(temp_Notification)
                    {
                        temperatureValue.setText(gattTemperatureValue);
                        recordData(gattTemperatureValue);
                    }
                    else
                    {
                        temperatureValue.setText("Zoot");
                    }
                    break;
                default:
                    break;
            }
        }
    };

    // Convert String Data to Int Data and Save Data to Graph
    private void recordData(String gattTemperatureValue)
    {
        double tempValue = Double.parseDouble(gattTemperatureValue);
        counter = counter + 8;
        DataPoint values = new DataPoint(counter, tempValue);
        temp_series.appendData(values, true, maxDataSet);
        dataGraph.animate();
    }

    private void saveData()
    {


    }
}
