import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.interpolate import griddata

# Read the data from the CSV file
# Assuming the CSV file has columns 'x', 'y', and 'voltage'
data = pd.read_csv('square.csv')

# Extract x, y, and voltage values from the DataFrame
x = data['x'].values
y = data['y'].values
voltage = data['voltage'].values

# Create a grid for interpolation
xi = np.linspace(min(x), max(x), 100)
yi = np.linspace(min(y), max(y), 100)
X, Y = np.meshgrid(xi, yi)

# Perform cubic interpolation
Z = griddata((x, y), voltage, (X, Y), method='cubic')

# Create the contour plot
plt.figure(figsize=(8, 6))
contour = plt.contourf(X, Y, Z, levels=20, cmap='viridis')
plt.colorbar(contour, label="Voltage")
plt.title("Voltage Contour Plot")
plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.grid(True, linestyle='--', alpha=0.7)
plt.show()