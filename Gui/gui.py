import tkinter as tk
from tkinter import ttk

import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style

#from drawnow import *

import serial_2 as sp1

from openpyxl import Workbook
import pandas as pd
import numpy as np
import sys
import time

LARGE_FONT = ("Verdana", 12)
TITLE_FONT = ("Times",16)
NORM_FONT = ("Helvetica", 10)
SMALL_FONT = ("Helvetica", 8)
style.use("ggplot")


rawdata_resp = []  #Raw Data from Arduino.
rawdata_uv = [] #Capacitance value from the Sensor
respiration = []  #Transforming the Data from the Arduino into something Useful
UV_value = []  #Transforming the Data from the Arduino into something Useful
seconds = [] #Time Since Data has been Captured

resp_graph = Figure(figsize=(5, 5), dpi=100, tight_layout=True)
resp_subplot = resp_graph.add_subplot(1,1,1)

uv_graph = Figure(figsize=(5, 5), dpi=100, tight_layout=True)
uv_subplot = uv_graph.add_subplot(1,1,1)

start_time = 0
stop_time = 0
record = 0
sensors = [0]*24


def init_gui():
    app = psoc_Sensors()
    ani_resp = animation.FuncAnimation(resp_graph,recordData,interval=100)
    ani_uv = animation.FuncAnimation(uv_graph, recordData, interval=100)
    app.geometry("1280x720")
    app.mainloop()

def popupmsg(msg):
    popup = tk.Tk()
    popup.wm_title("Pop-Up Message!")
    label = ttk.Label(popup, text=msg, font=NORM_FONT)
    label.grid(row=0,column=0)
    B1 = ttk.Button(popup, text="Okay", command = popup.destroy)
    B1.grid(row=0,column=1)
    popup.mainloop()

def record_start(value):
    global record
    global start_time
    if value == 0:
        record = 1
        start_time = time.time()

def record_stop(value):
    global record
    global start_time
    global rawdata_resp
    global rawdata_uv
    global seconds
    global respiration
    global UV_value
    if value == 1:
        record = 0
        start_time = 0
    #Saving the Data to an Excel Spread Sheet
    save_data()
    rawdata_resp = []
    rawdata_uv = []
    seconds = []
    respiration = []
    UV_value = []

def print_Name1():
        print("Carl!")

def save_data():
    global seconds
    global rawdata_resp
    global rawdata_uv
    global respiration
    global UV_value
    dest_filename = 'C:/Users/Intern/Documents/Data/test3.xlsx'
    wb = Workbook()
    ws = wb.active
    ws.title = "Sample #1"
    ws.cell(row=1, column=1, value="Time (s)")
    ws.cell(row=1, column=2, value="Raw Data Respiration")
    ws.cell(row=1, column=3, value="Raw Data UV")
    ws.cell(row=1, column=4, value="Respiration (Ohm)")
    ws.cell(row=1, column=5, value="UV (index)")

    for i in range(1,len(seconds)):
        ws.cell(row=i+1, column=1, value=seconds[i-1])
        ws.cell(row=i+1, column=2, value=rawdata_resp[i-1])
        ws.cell(row=i+1, column=3, value=rawdata_uv[i-1])
        ws.cell(row=i+1, column=4, value=respiration[i-1])
        ws.cell(row=i+1, column=5, value=UV_value[i-1])
    wb.save(filename = dest_filename)

def update_single_Fig():
    global resp_subplot
    resp_subplot.clear()
    resp_subplot.set_title("Individual Sensor Readout")
    resp_subplot.set_ylabel("Capacitance")  # Set ylabels
    resp_subplot.set_xlabel("Time (s)")
    resp_subplot.set_xlim([0, 50])
    resp_subplot.set_ylim([0, 3])
    resp_subplot.ticklabel_format(useOffset=False)

def update_total_Fig():
    print('Hello')


def recordData(i):
    # start data collection
    global record
    global rawdata_resp
    global rawdata_uv
    global respiration
    global UV_value
    global seconds
    data = 0
    resp1 = 0
    uv1 = 0
    if (record == 1):
        while (sp1.wait() == 0):
            pass
        indicator = sp1.read_8()
        data_resp = 0
        data_uv = 0
        if indicator == b's':
            #data_resp = sp1.read_dec()
            data_uv = sp1.read_dec()

        resp1 = float(data_resp)
        uv1 = float(data_uv)
        resp2 = ((resp1 - 2048)/2048) * 3.3
        uv2 = ((uv1 - 2048)/2048) * 3.3
        count = time.time() - start_time
        rawdata_resp.append(resp1)
        rawdata_uv.append(uv1)
        respiration.append(resp2)
        UV_value.append(uv2)
        seconds.append(count)
        update_single_Fig()
        resp_subplot.plot(seconds, UV_value)
        # print(data_resp)
        # print(resp2)
        print(data_uv)
        print(uv2)
        #uv_subplot.plot(seconds, UV_value)
        #resp_subplot.pause(.000001)
        # count = count + 1
        # if (count > 50):
        #     rawdata.pop(0)
        #     pressure.pop(0)

class psoc_Sensors(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        #tk.Tk.iconbitmap(self, default="sw-caution.gif")
        tk.Tk.wm_title(self, "Wearable Sensor BLE Gui")

        container = tk.Frame(self)
        container.grid(row=0,column=0)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.create_menu(container)
        self.frames = {}

        for F in (Intro_Page, Help_Page, Main_Page):
            frame = F(container, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(Intro_Page)

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

    def create_menu(self, container):
        menubar = tk.Menu(container)

        fileMenu = tk.Menu(menubar, tearoff=0)
        fileMenu.add_command(label="Save Graph", command=lambda: popupmsg("Not supported just yet!"))
        fileMenu.add_command(label="Export Excel", command=lambda: popupmsg("Not supported just yet!"))
        fileMenu.add_separator()
        fileMenu.add_command(label="Exit", command=quit)
        menubar.add_cascade(label="File", menu=fileMenu)

        subMenu = tk.Menu(menubar, tearoff=1)
        subMenu.add_command(label="Sensor Calibration", command=lambda: popupmsg("Not supported just yet!"))
        subMenu.add_command(label="Save settings", command=lambda: popupmsg("Not supported just yet!"))
        menubar.add_cascade(label="Settings", menu=subMenu)

        editMenu = tk.Menu(menubar, tearoff=1)
        editMenu.add_command(label="Help Menu", command=lambda: self.show_frame(Help_Page))
        editMenu.add_separator()
        editMenu.add_command(label="Print Name", command=lambda: print_Name1())
        menubar.add_cascade(label="Help", menu=editMenu)

        tk.Tk.config(self, menu=menubar)


class Intro_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label1 = tk.Label(self, text=("Welcome to Wearable Sensor BLE Gui!"), font=LARGE_FONT)
        label1.grid(row=0,column=0)

        label2 = tk.Label(self, text=("Designed by the Biomedical Wearable Lab @ UCSD"), font=TITLE_FONT)
        label2.grid(row=1, column=0)

        button1 = ttk.Button(self, text="Start!", command=lambda: controller.show_frame(Main_Page))
        button1.grid(row=2, column=0)

        # button2 = ttk.Button(self, text="Quit", command=_quit())
        # button2.grid(row=3, column=0)

        button3 = ttk.Button(self, text="Help Me!", command=lambda: controller.show_frame(Help_Page))
        button3.grid(row=4, column=0)


class Help_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)

        label = tk.Label(self, text=("Welcome to Help Menu!"), font=TITLE_FONT)
        label.grid(row=0,column=0)

        button1 = tk.Button(self, text="go Back to intro Page", command=lambda: controller.show_frame(Intro_Page))
        button1.grid(row=1,column=0)

        button2 = tk.Button(self, text="Go Back to main Page", command=lambda: controller.show_frame(Main_Page))
        button2.grid(row=2,column=0)

class Main_Page(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.create_Button()

        canvas_frame_resp = tk.Frame(self)
        canvas_resp = FigureCanvasTkAgg(resp_graph, canvas_frame_resp)
        canvas_resp.show()
        canvas_resp.get_tk_widget().pack()
        canvas_frame_resp.grid(row=6, column=0, columnspan=5)

        canvas_frame_uv = tk.Frame(self)
        canvas_uv = FigureCanvasTkAgg(uv_graph, canvas_frame_uv)
        canvas_uv.show()
        canvas_uv.get_tk_widget().pack()
        canvas_frame_uv.grid(row=6, column=10, columnspan=5)

        toolbar_frame_resp = tk.Frame(self)
        toolbar_resp = NavigationToolbar2TkAgg(canvas_resp, toolbar_frame_resp)
        toolbar_resp.update()
        canvas_resp._tkcanvas.pack(side=tk.TOP)
        toolbar_frame_resp.grid(row=7, column=0, columnspan=2)

        toolbar_frame_uv = tk.Frame(self)
        toolbar_uv = NavigationToolbar2TkAgg(canvas_uv, toolbar_frame_uv)
        toolbar_uv.update()
        canvas_uv._tkcanvas.pack(side=tk.TOP)
        toolbar_frame_uv.grid(row=7, column=10, columnspan=2)


    def create_Button(self):
        button_frame = tk.Frame(self)
        button2 = ttk.Button(button_frame, text="Start", command=lambda: record_start(record))
        button2.grid(row=0,column=0)
        button3 = ttk.Button(button_frame, text="Stop", command=lambda: record_stop(record))
        button3.grid(row=0,column=1)
        button_frame.grid(row=4,column=0)

def main():
    init_gui()

if __name__ == "__main__":
    main()
