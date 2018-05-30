package com.example.intern.ble_ex1;

import android.os.Environment;
import android.util.Log;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;

import jxl.Range;
import jxl.Sheet;
import jxl.Workbook;
import jxl.WorkbookSettings;
import jxl.format.Alignment;
import jxl.format.Colour;
import jxl.write.Label;
import jxl.write.Number;
import jxl.write.WritableCell;
import jxl.write.WritableCellFormat;
import jxl.write.WritableFont;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;

public class Excel
{
    private final static String TAG = Excel.class.getSimpleName();
    private String outputFile;
    private WritableCellFormat headerFormat;
    private WritableCellFormat dataFormat;
    private String fileLocation;
    private WritableWorkbook excelWorkbook;
    private WritableSheet excelSheetTemperature;
    private WritableSheet excelSheetUV;
    private WritableSheet excelSheetBattery;

    private String Poop;
    public Excel()
    {
        Poop = "POOOP!";
    }
    //Input the file name for the Excel File
    public void setOutputFile(String inputFile)
    {
        outputFile = inputFile;
    }

    public void createWorkbook()
    {
        Log.d(TAG, "UV: createWorkbook");
        //exports must use a temp file while writing to avoid memory hogging
        WorkbookSettings wbSettings = new WorkbookSettings();
        wbSettings.setUseTemporaryFileDuringWrite(true);
        //Set the language to English
        wbSettings.setLocale(new Locale("en", "EN"));

        File internalData = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS), "SAVED_DATA");
        if(!internalData.mkdirs())
        {
            Log.d(TAG, "UV: Directories not created");
        }

        //add on the your app's path
        Log.d(TAG, String.format("UV: %s", internalData.toString()));
        //make them in case they're not there
        if(!internalData.isDirectory())
        {
            internalData.mkdirs();
            Log.d(TAG, "UV: Make Directories");
        }
        //create a standard java.io.File object for the Workbook to use
        File wbfile = new File(internalData,(outputFile+".xlsx"));

        excelWorkbook = null;

        try
        {
            //create a new WritableWorkbook using the java.io.File and
            //WorkbookSettings from above
            excelWorkbook = Workbook.createWorkbook(wbfile, wbSettings);
        }
        catch(IOException ex)
        {
            Log.d(TAG,String.format("UV: %s", ex.getStackTrace().toString()));
            Log.d(TAG, String.format("UV: %s", ex.getMessage()));
            Log.d(TAG, String.format("UV: Poop %s", Poop));
        }
        Log.d(TAG, String.format("UV: %s", wbfile.getAbsolutePath()));
    }

    public void createSheet()
    {
        Log.d(TAG, "UV: createSheet");

        try
        {
            excelSheetTemperature = excelWorkbook.createSheet("Temperature Data", 0);
            excelSheetUV = excelWorkbook.createSheet("UV Data", 1);
            excelSheetBattery = excelWorkbook.createSheet("Battery Level", 2);

            WritableFont headerFont = new WritableFont(WritableFont.TIMES, 12, WritableFont.BOLD);
            headerFormat = new WritableCellFormat(headerFont);

            WritableFont dataFont = new WritableFont(WritableFont.TIMES, 10, WritableFont.NO_BOLD);
            dataFormat = new WritableCellFormat(headerFont);

            //Label = column and row
            Label counterLabel = new Label(0,0, "Time");
            Label temperatureHeadingLabel = new Label(1,0, "Temperature (C)");
            Label uvHeadingLabel = new Label(1,0, "UV Power Density (mW/cm^2)");
            Label batteryHeadingLabel = new Label(1,0, "Battery (%)");

            counterLabel.setCellFormat(headerFormat);
            temperatureHeadingLabel.setCellFormat(headerFormat);
            uvHeadingLabel.setCellFormat(headerFormat);
            batteryHeadingLabel.setCellFormat(headerFormat);

            headerFormat.setAlignment(Alignment.CENTRE);

            excelSheetTemperature.addCell(counterLabel);
            excelSheetTemperature.addCell(temperatureHeadingLabel);

            excelSheetUV.addCell(counterLabel);
            excelSheetUV.addCell(uvHeadingLabel);

            excelSheetBattery.addCell(counterLabel);
            excelSheetBattery.addCell(batteryHeadingLabel);

            excelWorkbook.write();
        }
        catch(WriteException e)
        {
            e.printStackTrace();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }

    public void writeData(ArrayList<Double> counter, ArrayList<Double> data, boolean uv_Notification, boolean temp_Notification, boolean battery_Notification)
    {
        Log.d(TAG, "UV: writeData");
        if(!temp_Notification)
        {
            int row = 0;
            for(int i = 0; i <counter.size(); i++)
            {
                row = i + 1;
                //Column, Row
                Number counter1 = new Number(0, row, counter.get(i));
                Number data1 = new Number(1, row, data.get(i));
                try
                {
                    excelSheetTemperature.addCell(counter1);
                    excelSheetTemperature.addCell(data1);
                    Log.d(TAG, "UV: Writing Data");
                }
                catch(WriteException e)
                {
                    Log.d(TAG, "UV: writeData didn't work");
                    e.printStackTrace();
                }
            }
        }
        try
        {
            excelWorkbook.write();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }

    public void closeWorkbook()
    {
        Log.d(TAG, "UV: closeWorkbook");
        try
        {
            excelWorkbook.close();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        catch (WriteException e)
        {
            e.printStackTrace();
        }
    }
}
