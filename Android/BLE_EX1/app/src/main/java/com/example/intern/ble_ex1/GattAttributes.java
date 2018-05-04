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

import java.util.HashMap;

/**
 * This class includes a small subset of standard GATT attributes for demonstration purposes.
 */
public class GattAttributes
{
    private static HashMap<String, String> attributes = new HashMap();
    //Services
    public static String UV_MEASUREMENT = "7D2EA28A-F7BD-485A-BD9D-92AD6ECFE93E"; //0xDB42
    public static String BATTERY_LEVEL = "7D2EA28A-F7BD-485A-BD9D-92AD6ECFE93E";  //0x5C96
    public static String BODY_TEMPERATURE = "07D2EA28A-F7BD-485A-BD9D-92AD6ECFE93E";   //0x8CD4
    public static String HEART_RATE = "0000180d-0000-1000-8000-00805f9b34fb";

    //Characteristics
    public static String POWER_DENSITY = "7D2EBAAD-F7BD-485A-BD9D-92AD6ECFE93E";  //0xE5CB
    public static String UV_INDEX = "7D2EBAAD-F7BD-485A-BD9D-92AD6ECFE93E";   //0xC3C2
    public static String BATTERY_PERCENT = "7D2EBAAD-F7BD-485A-BD9D-92AD6ECFE93E";    //0x6922
    public static String TEMPERATURE = "7D2EBAAD-F7BD-485A-BD9D-92AD6ECFE93E";    //0x46AA

    static
    {
        //Services
        attributes.put(HEART_RATE, "Heart Rate Service"); //Example Service
        attributes.put(UV_MEASUREMENT, "UV Measurement Service");   //UV Measurement Service
        attributes.put(BATTERY_LEVEL, "Battery Level Service");     //Battery Measurement Service
        attributes.put(BODY_TEMPERATURE, "Body Temperature Service");       //Body Temperature Service
        //Characteristics
        attributes.put("00002a29-0000-1000-8000-00805f9b34fb", "Manufacturer Name String"); //Example Characteristic
        attributes.put(POWER_DENSITY, "Power Density Measurement");         //UV Power Density Measurement for UV Measurement Service
        attributes.put(UV_INDEX, "UV Index Measurement");                   //UV Index Measurement for UV Measurement Service
        attributes.put(BATTERY_PERCENT, "Battery Level Measurement");       //Battery Level Measurement for Battery Level Service
        attributes.put(TEMPERATURE, "Body Temperature Measurement");        //Body Temperature Measurement for Body Temperature Service
    }

    public static String lookup(String uuid, String defaultName)
    {
        String name = attributes.get(uuid);
        return name == null ? defaultName : name;
    }
}
