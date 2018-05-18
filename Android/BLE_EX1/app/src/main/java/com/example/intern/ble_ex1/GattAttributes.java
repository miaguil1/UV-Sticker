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
    //Service and Characteristic by type
    public static String SERVICE_UV_MEASUREMENT = "0000DB42-0000-1000-8000-00805F9B34FB";

    public static String POWER_DENSITY = "0000E5CB-0000-1000-8000-00805F9B34FB";
    public static String POWER_DENSITY_CCC = "F1AFCB7C-5E7A-4310-8724-51C94A47BE8F";
    public static String POWER_DENSITY_CUD = "574F6677-66D9-4CFE-8331-4A3CE2AB0338";

    public static String UV_INDEX = "0000C3C2-0000-1000-8000-00805F9B34FB";
    public static String UV_INDEX_CCC = "B1834A0D-D687-4867-BDE5-3623A7A3DA08";
    public static String UV_INDEX_CUD = "29F41965-4240-4A16-B9F7-F69AB4AE1F0C";

    public static String SERVICE_BATTERY = "00005C96-0000-1000-8000-00805F9B34FB";

    public static String BATTERY_LEVEL = "00006922-0000-1000-8000-00805F9B34FB";
    public static String BATTERY_LEVEL_CCC = "A1FF0EA4-3D9F-4B9E-B377-74B4F7CB621E";
    public static String BATTERY_LEVEL_CUD = "4F79B4DD-A637-4E69-9AD4-BEA72221FA94";

    public static String SERVICE_BODY_TEMPERATURE = "00008CD4-0000-1000-8000-00805F9B34FB";

    public static String TEMPERATURE = "000046AA-0000-1000-8000-00805F9B34FB";
    public static String TEMPERATURE_CCC = "9E28D8F3-69B4-46B0-9645-5CC8E11509F6";
    public static String TEMPERATURE_CUD = "5DDE3F27-1255-4FE2-A295-16CD0ED7B81B";

    static
    {
        //Services
        attributes.put(SERVICE_UV_MEASUREMENT, "UV Measurement Service");   //UV Measurement Service
        attributes.put(SERVICE_BATTERY, "Battery Level Service");     //Battery Measurement Service
        attributes.put(SERVICE_BODY_TEMPERATURE, "Body Temperature Service");       //Body Temperature Service
        //Characteristics
        attributes.put(POWER_DENSITY, "Power Density Measurement");         //UV Power Density Measurement for UV Measurement Service
        attributes.put(UV_INDEX, "UV Index Measurement");                   //UV Index Measurement for UV Measurement Service
        attributes.put(BATTERY_LEVEL, "Battery Level Measurement");       //Battery Level Measurement for Battery Level Service
        attributes.put(TEMPERATURE, "Body Temperature Measurement");        //Body Temperature Measurement for Body Temperature Service
        //Client Characteristic Configuration
        attributes.put(POWER_DENSITY_CCC, "Power Density Client Configuration");         //UV Power Density Client Configuration for UV Measurement Service
        attributes.put(UV_INDEX_CCC, "UV Index Client Configuration");                   //UV Index Client Configuration for UV Measurement Service
        attributes.put(BATTERY_LEVEL_CCC, "Battery Level Client Configuration");       //Battery Level Client Configuration for Battery Level Service
        attributes.put(TEMPERATURE_CCC, "Body Temperature Client Configuration");        //Body Temperature Client Configuration for Body Temperature Service
        //Client User Description
        attributes.put(POWER_DENSITY_CUD, "Power Density Client User Description");         //UV Power Density Client User Description for UV Measurement Service
        attributes.put(UV_INDEX_CUD, "UV Index Client User Description");                   //UV Index Client User Description for UV Measurement Service
        attributes.put(BATTERY_LEVEL_CUD, "Battery Level Client User Description");       //Battery Level Client User Description for Battery Level Service
        attributes.put(TEMPERATURE_CUD, "Body Temperature Client User Description");        //Body Temperature Client User Description for Body Temperature Service
    }

    public static String lookup(String uuid, String defaultName)
    {
        String name = attributes.get(uuid);
        return name == null ? defaultName : name;
    }
}
