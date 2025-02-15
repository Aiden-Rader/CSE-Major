# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 13:31:08 2025

@author: Aiden Rader

Homework 1.6

You have trained a Linear Regression model and obtained the following predictions:
    X_test = np.array([1, 2, 3, 4, 5])
    y_test = np.array([2.1, 2.9, 3.8, 5.0, 6.1])
    y_pred = np.array([2.0, 3.0, 4.0, 5.0, 6.0])

Write a Matplotlib script to plot:
    - A scatter plot for the actual values (y_test).
    - A line plot for the predicted values (y_pred).
    - Label axes and add a legend
"""

# General imports
import numpy as np
import matplotlib.pyplot as plt

# Generate plt script given the actual and predicited values
X_test = np.array([1, 2, 3, 4, 5])
y_test = np.array([2.1, 2.9, 3.8, 5.0, 6.1])
y_pred = np.array([2.0, 3.0, 4.0, 5.0, 6.0])

# Create the plt figure
plt.figure(figsize=(12,6))

# Scatter Plot (y_test which is red dots)
plt.scatter(X_test, y_test, color='red', label='Actual Values', marker='o', s=75)

# Line Plot (y_pred which are blue squares)
plt.plot(X_test, y_pred, color='blue', label='Predicted Values', marker='s')

# Labels, Title and Legend
plt.xlabel("X_test (Feature Values)")
plt.ylabel("Target (y_test / y_pred)")
plt.title("Actual vs. Predicted Values (Linear Regression)")
plt.legend()

# Added a grid line so it is easier to see the two graphs
plt.grid(True, alpha=0.5)
plt.show()
