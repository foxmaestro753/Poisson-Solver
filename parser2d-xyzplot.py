import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
from scipy.interpolate import griddata

# Read the data from the CSV file
# Assuming the CSV file has columns 'x', 'y', and 'z' for the coordinates and voltage
data = pd.read_csv('square.csv')

# Extract x, y, and z values from the DataFrame
x = data['x'].values
y = data['y'].values
z = data['voltage'].values

# Create a grid for interpolation
xi = np.linspace(min(x), max(x), 100)
yi = np.linspace(min(y), max(y), 100)
xi, yi = np.meshgrid(xi, yi)

# Perform cubic interpolation
zi = griddata((x, y), z, (xi, yi), method='cubic')

# Create the 3D surface plot
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

surf = ax.plot_surface(xi, yi, zi, cmap='viridis', edgecolor='none', alpha=0.8)

# Set labels and title
ax.set_xlabel('X Coordinate')
ax.set_ylabel('Y Coordinate')
ax.set_zlabel('Voltage')
ax.set_title('3D Surface Voltage Plot')

# Add color bar
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10)

# Show the plot
plt.show()