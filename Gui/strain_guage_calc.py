import numpy as np
import matplotlib.pyplot as plt

x = np.arange(14000, 14350, 0.1)
y = 3.3*((x/(1000+x))-0.5)
plt.plot(x,y,'r')
plt.show()

r1a = 1400
r1b = 14000
r1c = 140000
rx = 14350
r2 = 14000
va1 = (r2/(r1a+r2))
vb1 = (rx/(r1a+rx))
vdiff1 = 3.3*(va1 - vb1)
print(vdiff1)
va2 = (r2/(r1b+r2))
vb2 = (rx/(r1b+rx))
vdiff2 = 3.3*(va2 - vb2)
print(vdiff2)
va3 = (r2/(r1c+r2))
vb3 = (rx/(r1c+rx))
vdiff3 = 3.3 *(va3 - vb3)
print(vdiff3)

#switch position
va4 = (r1a/(r1a+r2))
vb4 = (r1a/(r1a+rx))
vdiff4 = 3.3*(va4 - vb4)
print(vdiff4)

va5 = (r1b/(r1b+r2))
vb5 = (r1b/(r1b+rx))
vdiff5 = 3.3*(va5 - vb5)
print(vdiff5)

va6 = (r1c/(r1c+r2))
vb6 = (r1c/(r1c+rx))
vdiff6 = 3.3*(va6 - vb6)
print(vdiff6)

gain = 3.3/vdiff2
print(gain)