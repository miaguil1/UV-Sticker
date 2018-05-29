/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.intern.ble_ex1;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import java.util.List;
import java.util.UUID;

/**
 * Service for managing connection and data communication with a GATT server hosted on a
 * given Bluetooth LE device.
 */
public class BluetoothLeService extends Service
{
    private final static String TAG = BluetoothLeService.class.getSimpleName();

    private BluetoothManager mBluetoothManager;
    private BluetoothAdapter mBluetoothAdapter;
    private String mBluetoothDeviceAddress;
    private BluetoothGatt mBluetoothGatt;

    // Bluetooth Services that need to be read/write from
    private static BluetoothGattService mUVService;         //UV Service
    private static BluetoothGattService mTempService;       //Temperature Service
    private static BluetoothGattService mBatteryService;    //Battery Service

    // Bluetooth characteristics that we need to read/write
    private static BluetoothGattCharacteristic mUVCharacteristic;   //UV Characteristic
    private static BluetoothGattCharacteristic mBatteryCharacteristic;  //Battery Characteristic
    private static BluetoothGattCharacteristic mTemperatureCharacteristic;  //Temperature Characteristic

    // Bluetooth Custom Client Characteristic Configuration Descriptors
    private static BluetoothGattDescriptor mUVCccd; //UV Custom Client Characteristic Configuration Descriptor
    private static BluetoothGattDescriptor mBatteryCccd; //Battery Custom Client Characteristic Configuration Descriptor
    private static BluetoothGattDescriptor mTemperatureCccd; //Temperature Custom Client Characteristic Configuration Descriptor

    public final static UUID UUID_SERVICE_BODY_TEMPERATURE = UUID.fromString(GattAttributes.SERVICE_BODY_TEMPERATURE);
    public final static UUID UUID_TEMPERATURE = UUID.fromString(GattAttributes.TEMPERATURE);
    public final static UUID UUID_TEMPERATURE_CCC = UUID.fromString(GattAttributes.TEMPERATURE_CCC);
    public final static UUID UUID_TEMPERATURE_CUD = UUID.fromString(GattAttributes.TEMPERATURE_CUD);

    public final static UUID UUID_SERVICE_UV_MEASUREMENT = UUID.fromString(GattAttributes.SERVICE_UV_MEASUREMENT);

    public final static UUID UUID_POWER_DENSITY = UUID.fromString(GattAttributes.POWER_DENSITY);
    public final static UUID UUID_POWER_DENSITY_CCC = UUID.fromString(GattAttributes.POWER_DENSITY_CCC);
    public final static UUID UUID_POWER_DENSITY_CUD = UUID.fromString(GattAttributes.POWER_DENSITY_CUD);

    public final static UUID UUID_UV_INDEX = UUID.fromString(GattAttributes.UV_INDEX);
    public final static UUID UUID_UV_INDEX_CCC = UUID.fromString(GattAttributes.UV_INDEX_CCC);
    public final static UUID UUID_UV_INDEX_CUD = UUID.fromString(GattAttributes.UV_INDEX_CUD);

    public final static UUID UUID_SERVICE_BATTERY = UUID.fromString(GattAttributes.SERVICE_BATTERY);

    public final static UUID UUID_BATTERY_LEVEL = UUID.fromString(GattAttributes.BATTERY_LEVEL);
    public final static UUID UUID_BATTERY_LEVEL_CCC = UUID.fromString(GattAttributes.BATTERY_LEVEL_CCC);
    public final static UUID UUID_BATTERY_LEVEL_CUD = UUID.fromString(GattAttributes.BATTERY_LEVEL_CUD);

    private static String mUVValue = "sup";              //UV Message Value
    private static String mBatteryValue = "zoot";         //Battery Message Value
    private static String mTemperatureValue = "zip";     //Temperature Notifications


    private int mConnectionState = STATE_DISCONNECTED;

    private static final int STATE_DISCONNECTED = 0;
    private static final int STATE_CONNECTING = 1;
    private static final int STATE_CONNECTED = 2;

    public final static String ACTION_GATT_CONNECTED = "com.example.bluetooth.le.ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED = "com.example.bluetooth.le.ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED = "com.example.bluetooth.le.ACTION_GATT_SERVICES_DISCOVERED";
    public final static String ACTION_DATA_AVAILABLE = "com.example.bluetooth.le.ACTION_DATA_AVAILABLE";
    public final static String EXTRA_DATA = "com.example.bluetooth.le.EXTRA_DATA";


    // Implements callback methods for GATT events that the app cares about.  For example,
    // connection change and services discovered.
    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback()
    {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState)
        {
            String intentAction;
            if (newState == BluetoothProfile.STATE_CONNECTED)
            {
                intentAction = ACTION_GATT_CONNECTED;
                mConnectionState = STATE_CONNECTED;
                broadcastUpdate(intentAction);
                Log.d(TAG, "UV: Connected to GATT server.");
                // Attempts to discover services after successful connection.
                boolean service_discovery = mBluetoothGatt.discoverServices();  //Discovering Services
                Log.d(TAG, "UV: Attempting to start service discovery:" + service_discovery);   //Printing "Discovering Services" Results
            }

            else if (newState == BluetoothProfile.STATE_DISCONNECTED)
            {
                intentAction = ACTION_GATT_DISCONNECTED;
                mConnectionState = STATE_DISCONNECTED;
                Log.d(TAG, "UV: Disconnected from GATT server.");
                broadcastUpdate(intentAction);
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status)
        {
            if (status == BluetoothGatt.GATT_SUCCESS)
            {
                Log.d(TAG, "UV: onServicesDiscovered");

                // Linking UUID to Services
                mUVService = gatt.getService(UUID_SERVICE_UV_MEASUREMENT);          //UV Measurement Service assigned to specific UUID
                mTempService = gatt.getService(UUID_SERVICE_BODY_TEMPERATURE);      //Body Temperature Service assigned to specific UUID
                mBatteryService = gatt.getService(UUID_SERVICE_BATTERY);            //Battery Level Service assigned to specific UUID

                // Linking UUID to Characteristics
                mUVCharacteristic = mUVService.getCharacteristic(UUID_POWER_DENSITY);                       //UV Power Density Characteristics
                mTemperatureCharacteristic = mTempService.getCharacteristic(UUID_TEMPERATURE);              //Body Temperature Characteristics
                mBatteryCharacteristic = mBatteryService.getCharacteristic(UUID_BATTERY_LEVEL);             //Battery Level Characteristics

                // Linking UUID to Custom Client Configuration Descriptors
                mUVCccd = mUVCharacteristic.getDescriptor(UUID_POWER_DENSITY_CCC);                          //UV Power Density Descriptor
                mTemperatureCccd = mTemperatureCharacteristic.getDescriptor(UUID_TEMPERATURE_CCC);          //Body Temperature Descriptor
                mBatteryCccd = mBatteryCharacteristic.getDescriptor(UUID_BATTERY_LEVEL_CCC);                //Battery Level Descriptor

                broadcastUpdate(ACTION_GATT_SERVICES_DISCOVERED);
            }
            else
            {
                Log.d(TAG, "UV: onServicesDiscovered received: " + status);
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status)
        {
            if (status == BluetoothGatt.GATT_SUCCESS)
            {
//                broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
            }
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic)
        {
            Log.d(TAG, "UV: onCharacteristicChanged");
            //This is called when a characteristic notification changes
            //It broadcasts to the main activity with the changed data
            if(UUID_POWER_DENSITY.equals(characteristic.getUuid()))
            {
                mUVValue = characteristic.getStringValue(0);
                Log.d(TAG, String.format("UV: UV Power Density Value: %s", mUVValue));
            }
            if(UUID_TEMPERATURE.equals(characteristic.getUuid()))
            {
                mTemperatureValue = characteristic.getStringValue(0);
                Log.d(TAG, String.format("UV: Temperature Value: %s", mTemperatureValue));
            }
            if(UUID_BATTERY_LEVEL.equals(characteristic.getUuid()))
            {
                mBatteryValue = characteristic.getStringValue(0);
                Log.d(TAG, String.format("UV: Battery Value: %s", mBatteryValue));
            }

            broadcastUpdate(ACTION_DATA_AVAILABLE);
        }
    };

    public String getmUVValue()
    {
        return mUVValue;
    }

    public String getmTemperatureValue()
    {
        return mTemperatureValue;
    }

    public String getmBatteryValue()
    {
        return mBatteryValue;
    }

    private void broadcastUpdate(final String action)
    {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }

    public class LocalBinder extends Binder
    {
        BluetoothLeService getService()
        {
            return BluetoothLeService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent)
    {
        // After using a given device, you should make sure that BluetoothGatt.close() is called
        // such that resources are cleaned up properly.  In this particular example, close() is
        // invoked when the UI is disconnected from the Service.
        close();
        return super.onUnbind(intent);
    }

    private final IBinder mBinder = new LocalBinder();

    /**
     * Initializes a reference to the local Bluetooth adapter.
     *
     * @return Return true if the initialization is successful.
     */
    public boolean initialize()
    {
        // For API level 18 and above, get a reference to BluetoothAdapter through
        // BluetoothManager.
        if (mBluetoothManager == null)
        {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null)
            {
                Log.d(TAG, "UV: Unable to initialize BluetoothManager.");
                return false;
            }
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null)
        {
            Log.d(TAG, "UV: Unable to obtain a BluetoothAdapter.");
            return false;
        }

        return true;
    }

    /**
     * Connects to the GATT server hosted on the Bluetooth LE device.
     *
     * @param address The device address of the destination device.
     *
     * @return Return true if the connection is initiated successfully. The connection result
     *         is reported asynchronously through the
     *         {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     *         callback.
     */
    public boolean connect(final String address)
    {
        if (mBluetoothAdapter == null || address == null)
        {
            Log.d(TAG, "UV: BluetoothAdapter not initialized or unspecified address.");
            return false;
        }

        // Previously connected device.  Try to reconnect.
        if (mBluetoothDeviceAddress != null && address.equals(mBluetoothDeviceAddress) && mBluetoothGatt != null)
        {
            Log.d(TAG, "UV: Trying to use an existing mBluetoothGatt for connection.");
            if (mBluetoothGatt.connect())
            {
                mConnectionState = STATE_CONNECTING;
                return true;
            }
            else
            {
                return false;
            }
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        if (device == null)
        {
            Log.w(TAG, "Device not found.  Unable to connect.");
            return false;
        }
        // We want to directly connect to the device, so we are setting the autoConnect parameter to false
        mBluetoothGatt = device.connectGatt(this, false, mGattCallback);
        Log.d(TAG, "UV: Trying to create a new connection.");
        mBluetoothDeviceAddress = address;
        mConnectionState = STATE_CONNECTING;
        return true;
    }

    /**
     * Disconnects an existing connection or cancel a pending connection. The disconnection result
     * is reported asynchronously through the
     * {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     * callback.
     */
    public void disconnect()
    {
        if (mBluetoothAdapter == null || mBluetoothGatt == null)
        {
            Log.d(TAG, "UV: BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.disconnect();
    }

    /**
     * After using a given BLE device, the app must call this method to ensure resources are
     * released properly.
     */
    public void close()
    {
        if (mBluetoothGatt == null)
        {
            return;
        }
        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }

    /**
     * Request a read on a given {@code BluetoothGattCharacteristic}. The read result is reported
     * asynchronously through the {@code BluetoothGattCallback#onCharacteristicRead(android.bluetooth.BluetoothGatt, android.bluetooth.BluetoothGattCharacteristic, int)}
     * callback.
     *
     * @param characteristic The characteristic to read from.
     */
    public void readCharacteristic(BluetoothGattCharacteristic characteristic)
    {
        if (mBluetoothAdapter == null || mBluetoothGatt == null)
        {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.readCharacteristic(characteristic);
    }

    public void writeCharacteristicNotification(boolean uv_Notification, boolean temp_Notification, boolean battery_Notification)
    {
        Log.d(TAG, "UV: writeCharacteristicNotification");
        if (mBluetoothAdapter == null || mBluetoothGatt == null)
        {
            Log.d(TAG, "UV: BluetoothAdapter not initialized");
            return;
        }

//        mBluetoothGatt.setCharacteristicNotification(mUVCharacteristic, uv_Notification);   //Enabling or Disabling UV Characteristic Notification
//        byte[] uv_byteVal = new byte[1];
//        if(uv_Notification)
//        {
//            uv_byteVal[0] = 1;
//        }
//        else
//        {
//            uv_byteVal[0] = 0;
//        }
//        Log.d(TAG, "UV: UV Notification: "+uv_Notification);
//        mUVCccd.setValue(uv_byteVal);
//        mBluetoothGatt.writeDescriptor(mUVCccd);

        mBluetoothGatt.setCharacteristicNotification(mTemperatureCharacteristic, temp_Notification);   //Enabling or Disabling Temperature Characteristic Notification
        byte[] temp_byteVal = new byte[1];
        if(temp_Notification)
        {
            temp_byteVal[0] = 1;
        }
        else
        {
            temp_byteVal[0] = 0;
        }
        Log.d(TAG, "UV: Temperature Notification: "+temp_byteVal);
        mTemperatureCccd.setValue(temp_byteVal);
        mBluetoothGatt.writeDescriptor(mTemperatureCccd);

//        mBluetoothGatt.setCharacteristicNotification(mBatteryCharacteristic, battery_Notification);   //Enabling or Disabling Battery Characteristic Notification
//        byte[] battery_byteVal = new byte[1];
//        if(battery_Notification)
//        {
//            battery_byteVal[0] = 1;
//        }
//        else
//        {
//            battery_byteVal[0] = 0;
//        }
//        Log.d(TAG, "UV: Battery Notification:"+battery_Notification);
//        mBatteryCccd.setValue(battery_byteVal);
//        mBluetoothGatt.writeDescriptor(mBatteryCccd);
    }

    /**
     * Retrieves a list of supported GATT services on the connected device. This should be
     * invoked only after {@code BluetoothGatt#discoverServices()} completes successfully.
     *
     * @return A {@code List} of supported services.
     */
    public List<BluetoothGattService> getSupportedGattServices()
    {
        if (mBluetoothGatt == null) return null;

        return mBluetoothGatt.getServices();
    }
}
