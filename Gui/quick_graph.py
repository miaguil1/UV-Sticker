import serial
import numpy as np
from matplotlib import pyplot as plt
from drawnow import *

port1 = serial.Serial(port='COM4', baudrate=115200, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, timeout=None)

plt.ion()  # set plot to animated

rawdata = [] # Raw Data from Arduino.
voltage = [] # Transforming the Data from the Arduino into something Useful
count = 0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(1700,1800)                                 #Set y min and max values
    plt.title('YSK Breathing Flex-Sensor')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Raw Data')                            #Set ylabels
    plt.plot(rawdata, 'ro-', label='Raw Values')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    plt.ylim(0,3.3)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(voltage, 'b^-', label='Voltage (V)') #plot pressure data
    plt2.set_ylabel('Voltage (V)')                    #label second y axis
    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend

# start data collection
while 1:
    while(port1.inWaiting()==0):
        pass
    #data = 0
    indicator = port1.read()
    if indicator == b's':
        temp_a = port1.read()
        temp_b = port1.read()
        data = (temp_b[0] << 8) | temp_a[0]
    rd = float(data) - 2048
    print(rd)
    v = (rd/2048)*3.3
    rawdata.append(rd)
    voltage.append(v)
    drawnow(makeFig)
    plt.pause(.000001)
    count = count + 1
    if (count > 50):
        rawdata.pop(0)
        voltage.pop(0)