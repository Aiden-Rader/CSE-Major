# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 14:45:24 2025

@author: Aiden Rader

Homework 1.7

Considering the following dataset, write a Matplotlib script to plot:
    a. A line graph showing MSE vs. max_depth.
    b. A marker at each data point.
    c. The optimal depth where MSE stops decreasing significantly.

                    **SEE DATATABLE IN HOMEWORK 1 PROBLEM 7**
"""

import matplotlib.pyplot as plt
import numpy as np

# Here are array versions of the datatable
max_depth = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
mse = np.array([12.1, 8.5, 5.3, 3.9, 2.8, 2.5, 2.4, 2.3, 2.3, 2.2])

# Addition of optimal depth where MSE stops decreasing significantly, 
# this is also the middle of the max_depth array.
optimal_depth = 5

# Plot MSE vs. max_depth
plt.figure(figsize=(12, 6))
plt.plot(max_depth, mse, marker='s', linestyle='-', color='blue', label='MSE')

# Highlight optimal depth with a red marker, mark - 1 because we account for 0 indexing
plt.scatter(optimal_depth, mse[optimal_depth - 1], color='red', s=150, label=f'Optimal Depth ({optimal_depth})')

# Labels and title
plt.xlabel("Max Depth of Decision Tree")
plt.ylabel("Mean Squared Error (MSE)")
plt.title("MSE vs. Max Depth")

# Grid (easier to view) and Legend
plt.grid(True, alpha=0.5)
plt.legend()

# Show plot
plt.show()