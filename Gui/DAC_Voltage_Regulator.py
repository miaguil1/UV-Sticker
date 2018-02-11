import matplotlib.pyplot as plt
import decimal
import numpy
V_FB = 1.22
V_DAC =  numpy.linspace(0, 3.3, num=50)
print(V_DAC)
R1 = 51100
R2 = 5900
Rb = 10000
I_b = (V_DAC - V_FB)/Rb
I_2 = V_FB/R2
V_OUT = R1*(I_2 - I_b) + V_FB
plt.plot(V_DAC, V_OUT)
plt.xlabel('Voltage of DAC')
plt.ylabel('Voltage of Output')
plt.title('Output Voltage due to DAC')
plt.show()