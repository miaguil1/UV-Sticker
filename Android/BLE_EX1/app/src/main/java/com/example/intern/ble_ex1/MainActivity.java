package com.example.intern.ble_ex1;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.CheckBox;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.LineGraphSeries;
import com.jjoe64.graphview.series.DataPoint;

public class MainActivity extends AppCompatActivity
{
    private boolean temp_Notification = false;
    private boolean uv_Notification = false;
    private boolean resp_Notification = false;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.content_main);

        //Connect U.I Elements
        CheckBox temp_CheckBox = (CheckBox) findViewById(R.id.temp_check);
        CheckBox uv_CheckBox = (CheckBox) findViewById(R.id.uv_check);
        CheckBox resp_CheckBox = (CheckBox) findViewById(R.id.resp_check);
        GraphView graph = (GraphView) findViewById(R.id.graph);
        Button start_Button = (Button) findViewById(R.id.startBtn);
        Button stop_Button = (Button) findViewById(R.id.stopBtn);
        Button save_Button = (Button) findViewById(R.id.saveBtn);

        LineGraphSeries<DataPoint> temp_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("Temperature");
        temp_series.setColor(Color.RED);
        temp_series.setThickness(8);
        graph.addSeries(temp_series);
        LineGraphSeries<DataPoint> uv_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("UV Power Density");
        temp_series.setColor(Color.BLUE);
        temp_series.setThickness(8);
        graph.addSeries(uv_series);
        LineGraphSeries<DataPoint> resp_series = new LineGraphSeries<>(new DataPoint[] {});
        temp_series.setTitle("Respiration");
        temp_series.setColor(Color.GREEN);
        temp_series.setThickness(8);
        graph.addSeries(resp_series);

        buttonClicked(start_Button, stop_Button, save_Button);
        checkClicked(temp_CheckBox, uv_CheckBox, resp_CheckBox);
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        // Inflate the menu; this adds items to the action bar if it is present.
//        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
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
//                startGraph(temp_Notification, uv_Notification, resp_Notification);
            }
        });
        stop_Button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
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
}
