import numpy as np
from scipy.optimize import curve_fit

threads = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16])
efficiency = np.array([1, 0.956, 0.697, 0.595, 0.575, 0.564, 0.492, 0.50, 0.47, 0.43, 0.395, 0.471, 0.44, 0.386, 0.390, 0.367])

def hyperbola(x, a, b):
    return a / (x + b)


params, covariance = curve_fit(hyperbola, threads, efficiency)

a, b = params

print("Param a:", a)
print("Param b:", b)

import matplotlib.pyplot as plt
x_fit = np.linspace(1, 16, 100)
y_fit = hyperbola(x_fit, a, b)
plt.scatter(threads, efficiency, label='Данные')
plt.plot(x_fit, y_fit, 'r', label='Аппроксимация')
plt.xlabel('Количество потоков')
plt.ylabel('Эффективность')
plt.legend()
plt.show()

