# Import necessary libraries
import pandas as pd
import matplotlib.pyplot as plt

# Read data from a CSV file into a pandas DataFrame
df = pd.read_csv('line.csv')

# Extract 'x' and 'value' columns from the DataFrame for plotting
x = df['x']  # Distance along the semiconductor
y = df['voltage']  # Voltage values corresponding to each x position

# Create a line plot with x on the x-axis and y on the y-axis
plt.plot(x, y)

# Set the label for the x-axis (Distance)
plt.xlabel('Distance along the semiconductor')

# Set the label for the y-axis (Voltage)
plt.ylabel('Voltage')

# Set the title of the plot
plt.title('Distance vs Voltage')

# Display the plot
plt.show()