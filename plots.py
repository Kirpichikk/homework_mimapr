import matplotlib.pyplot as plt 
import numpy as np 

with open ('cubic20.txt') as f:
    lines = f.readlines()

line_cubic_20 = [float(i) for i in lines]

with open ('linear20.txt') as f:
    lines = f.readlines()

line_linear_20 = [float(i) for i in lines]

x_values = np.linspace(1, 9, len(line_linear_20))
y_values = [1/81 * (44*np.exp(72)-44*np.exp(81-9*x)-9*(37+17*x)) for x in x_values]
for i in y_values:
    print(i)
plt.figure(figsize=(10,10))
#plt.plot(x_values, y_values)
plt.plot(x_values, line_linear_20, label="linear_40")



plt.grid()
plt.legend()
plt.show()

x_values = np.linspace(1, 9, len(line_cubic_20))
y_values = [1/81 * (44*np.exp(72)-44*np.exp(81-9*x)-9*(37+17*x)) for x in x_values]

plt.figure(figsize=(10,10))
#plt.plot(x_values, y_values)
plt.plot(x_values, line_cubic_20, label="cubic_40")

plt.grid()
plt.legend()
plt.show()

with open ('cubic40.txt') as f:
    lines = f.readlines()

line_cubic_40 = [float(i) for i in lines]

with open ('linear40.txt') as f:
    lines = f.readlines()

line_linear_40 = [float(i) for i in lines]

x_values = np.linspace(1, 9, len(line_linear_40))
y_values = [1/81 * (44*np.exp(72)-44*np.exp(81-9*x)-9*(37+17*x)) for x in x_values]
for i in y_values:
    print(i)
plt.figure(figsize=(10,10))
#plt.plot(x_values, y_values)
plt.plot(x_values, line_linear_40, label="linear_40")



plt.grid()
plt.legend()
plt.show()

x_values = np.linspace(1, 9, len(line_cubic_40))
y_values = [1/81 * (44*np.exp(72)-44*np.exp(81-9*x)-9*(37+17*x)) for x in x_values]

plt.figure(figsize=(10,10))
#plt.plot(x_values, y_values)
plt.plot(x_values, line_cubic_40, label="cubic_40")

plt.grid()
plt.legend()
plt.show()
