# -*- coding: utf-8 -*-
"""
Created on Wed Feb  5 18:53:13 2025

@author: Aiden Rader

Homework 1.1

"Write a function that takes a NumPy array and returns a standardized version of the
array, where each column has zero mean and unit variance."
"""

import numpy as np

def std_columns(np_arr):

    # Compute std & mean for EACH COLUMN (axis=0) in the passed array
    means = np.mean(np_arr, axis=0)
    stds = np.std(np_arr, axis=0)
    
    # Check if any column has std = 0
    if np.any(stds == 0):
        print("Error! STD is 0, Cannot Compute!")
        stds[stds == 0] = 1
    
    return (np_arr - means) / stds


# MAIN CODE #

# Make a 3x3 array with random variables in it
np_arr = np.random.randint(50, size=(3, 3))

# If we cannot use the random variable array we can always just hardcode one like the commented out one below
# np_arr = np.array([
#     [10, 20, 30],
#     [15, 25, 35],
#     [40, 50, 60]
# ])

# Check the numbers in the console to ensure they are correct
print("Original NumPy Array:\n", np_arr)

# We can now calculate the standardized version using our function!
standardized_arr = std_columns(np_arr)
print("Standardized array:\n", standardized_arr)


