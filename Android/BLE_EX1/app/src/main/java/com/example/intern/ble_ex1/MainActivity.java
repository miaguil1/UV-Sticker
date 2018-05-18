package com.example.intern.ble_ex1;

import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
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
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ExpandableListView;
import android.widget.SimpleExpandableListAdapter;
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

    private ArrayList<ArrayList<BluetoothGattCharacteristic>> mGattCharacteristics = new ArrayList<ArrayList<BluetoothGattCharacteristic>>();

    private final String LIST_NAME = "NAME";
    private final String LIST_UUID = "UUID";

    private boolean mConnected = false;

    private boolean temp_Notification = false;
    private boolean uv_Notification = false;
    private boolean resp_Notification = false;

    private boolean temp_streaming = false;
    private boolean uv_streaming = false;
    private boolean resp_streaming = false;

    private LineGraphSeries<DataPoint> temp_series;
    private LineGraphSeries<DataPoint> resp_series;
    private LineGraphSeries<DataPoint> uv_series;
    private GraphView dataGraph;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content_main);

        mDeviceStatus = "Connected";

        final Intent startIntent = getIntent();
        mDeviceName = startIntent.getStringExtra(EXTRAS_DEVICE_NAME);    //Get Device Name from Previous Intent
        mDeviceAddress = startIntent.getStringExtra(EXTRAS_DEVICE_ADDRESS);  //Get Device Address from Previous Intent

        ((TextView) findViewById(R.id.ble_device_name_connected)).setText(mDeviceName); //Sets the Text of the Device name
        ((TextView) findViewById(R.id.ble_device_address_connected)).setText(mDeviceAddress);   //Sets the Text of the Device Address
        ((TextView) findViewById(R.id.ble_device_status)).setText(mDeviceStatus);   //Sets the Text of the Device Connection Status


        Intent gattServiceIntent = new Intent(this, BluetoothLeService.class);  //Creates an intent for the Bluetooth Service
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);   //Binds Service to the Gatt Service

        mBluetoothLeService.connect(mDeviceAddress);    //Connect to BLE Device on Creation

        //Connect U.I Elements
        CheckBox temp_CheckBox = (CheckBox) findViewById(R.id.temp_check);  //Temperature Checkbox
        CheckBox uv_CheckBox = (CheckBox) findViewById(R.id.uv_check);      //UV Checkbox
        CheckBox resp_CheckBox = (CheckBox) findViewById(R.id.resp_check);  //Respiration Checkbox
        dataGraph = (GraphView) findViewById(R.id.graph);             //Graphview to Display Data
        Button start_Button = (Button) findViewById(R.id.startBtn);         //Start button to start graphing and enable notifications of Selected Values
        Button stop_Button = (Button) findViewById(R.id.stopBtn);           //Stop button to stop graphing and disable notifications of Selected Values
        Button save_Button = (Button) findViewById(R.id.saveBtn);           //Save button to save data from enabled graph and Selected Values

        //Initializing Temperature Dataset on Graph
        temp_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("Temperature");
        temp_series.setColor(Color.RED);
        temp_series.setThickness(8);
        dataGraph.addSeries(temp_series);

        uv_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("UV Power Density");
        temp_series.setColor(Color.BLUE);
        temp_series.setThickness(8);
        dataGraph.addSeries(uv_series);

        resp_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("Respiration");
        temp_series.setColor(Color.GREEN);
        temp_series.setThickness(8);
        dataGraph.addSeries(resp_series);

        buttonClicked(start_Button, stop_Button, save_Button);
        checkClicked(temp_CheckBox, uv_CheckBox, resp_CheckBox);
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
        unbindService(mServiceConnection);
        mBluetoothLeService = null;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        if (mConnected)
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
                enableNotifications();
//                startGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        stop_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                disableNotifications();
                //stopGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        save_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                //saveGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
    }

    private void checkClicked(CheckBox temp_CheckBox, CheckBox uv_CheckBox, CheckBox resp_CheckBox)
    {
        temp_CheckBox.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                //temp_toggle = true;
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
                //temp_toggle = true;
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
        resp_CheckBox.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                //temp_toggle = true;
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
            if (BluetoothLeService.ACTION_GATT_CONNECTED.equals(action))
            {
                mConnected = true;
                updateConnectionState(R.string.connected);
                invalidateOptionsMenu();
            }
            else if (BluetoothLeService.ACTION_GATT_DISCONNECTED.equals(action))
            {
                mConnected = false;
                updateConnectionState(R.string.disconnected);
                invalidateOptionsMenu();
            }
            else if (BluetoothLeService.ACTION_GATT_SERVICES_DISCOVERED.equals(action))
            {
                // Show all the supported services and characteristics on the user interface.
//                displayGattServices(mBluetoothLeService.getSupportedGattServices());
            }
            else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action))
            {
//                displayData(intent.getStringExtra(BluetoothLeService.EXTRA_DATA));
            }
        }
    };

    private void enableNotifications()
    {
        if(uv_Notification)
        {
            mBluetoothLeService.setCharacteristicNotification(, true);
            uv_streaming = true;
        }
        if(resp_Notification)
        {
            mBluetoothLeService.setCharacteristicNotification(, true);
            resp_streaming = true;
        }
        if(temp_Notification)
        {
            mBluetoothLeService.setCharacteristicNotification(,true);
            temp_streaming = true;
        }
    }
    private void disableNotifications()
    {
        if(uv_streaming)
        {
            mBluetoothLeService.setCharacteristicNotification(, true);
            uv_streaming = false;
        }
        if(resp_streaming)
        {
            mBluetoothLeService.setCharacteristicNotification(, true);
            resp_streaming = false;
        }
        if(temp_streaming)
        {
            mBluetoothLeService.setCharacteristicNotification(,true);
            temp_streaming = false;
        }
    }
}
