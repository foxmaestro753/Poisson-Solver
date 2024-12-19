# Import necessary libraries
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Path to the CSV file containing the data
csv_file_path = "cube.csv"

# Read the CSV file into a pandas DataFrame
data = pd.read_csv(csv_file_path)

# Extract 'x', 'y', 'z' coordinates and 'value' (voltage) from the DataFrame
x = data['x']
y = data['y']
z = data['z']
value = data['voltage']

# Create a new figure for the 3D plot with specific size
fig = plt.figure(figsize=(10, 8))

# Create a 3D axis for the plot
ax = fig.add_subplot(111, projection='3d')

# Scatter plot the data points, using 'value' for coloring the points
sc = ax.scatter(x, y, z, c=value, cmap='viridis', marker='o')

# Add a color bar to the plot to represent the voltage (value)
cbar = plt.colorbar(sc, ax=ax, label='Voltage')

# Set the labels for the axes
ax.set_xlabel('X Coordinate')
ax.set_ylabel('Y Coordinate')
ax.set_zlabel('Z Coordinate')

# Set the title for the plot
ax.set_title('3D Voltage Distribution')

# Show the plot
plt.show()