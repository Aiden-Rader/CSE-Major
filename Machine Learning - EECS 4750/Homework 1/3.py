# -*- coding: utf-8 -*-
"""
Created on Wed Feb  5 40:06:15 2025

@author: Aiden Rader

Homework 1.3

Write Python code for the following tasks, ensuring that the data manipulation and
conversions are executed correctly and efficiently. Make sure to handle edge cases and
provide appropriate error handling where necessary:
    
    a. Generate synthetic data consisting of 1000 samples. The feature matrix X should
    have 5 columns representing different features, and the target vector Y should
    contain class labels (0, 1, 2). Use `np.random.randn()` to generate random
    values for X and `np.random.randint()` to generate random class labels for
    Y.
    
    b. Convert the NumPy arrays representing features (X) and targets (Y) into a
    Pandas DataFrame. Name it as “xy_df”. Create a separate pandas Dataframe
    namely “xy_df_filtered” based on the following conditions:
        
        i. For class of Y = 0, select corresponding rows of X where the value in the
        second column of X is less than 0.
        
        ii. For Y = 1, select corresponding rows of X where the value in the third
        column of X is greater than 0.
        
        iii. For Y = 2, select corresponding rows of X where the value in the fourth
        column of X is between -1 and 1.
        
    c. Create separate NumPy arrays from (a.) for X and Y namely x_arr_filtered and
    “y_arr_filtered” based on the following conditions:
        
        i. For class of Y = 0, select corresponding rows of X where the value in the
        second column of X is less than 0; and
        
        ii. For Y = 1, select corresponding rows of X where the value in the third
        column of X is greater than 0; and
        
        iii. For Y = 2, select corresponding rows of X where the value in the fourth
        column of X is between -1 and 1.
"""

# General imports like numpy and pandas
import numpy as np
import pandas as pd

# Part A.)

# Generate random feature data for X and random class labels (targets) for Y
X = np.random.randn(1000, 5)
Y = np.random.randint(0, 3, size=1000)

# EDGE CASE: If X includes a NaN value || if X includes an infinite number
if (np.isnan(X).any() or np.isinf(X).any()):
    raise ValueError("Error: X contains NaN or infinite values!") 
    
# EDGE CASE: If there is an unexpected label value (outisde of 0:2 bounds)
expected_labels = [0, 1, 2]
unexpected_labels = np.setdiff1d(Y, expected_labels)
if unexpected_labels.size > 0:
    raise ValueError("Error: Y contains an unexpected number(s)!")

# Print to verify shape and uniqueness
print(X.shape)
print(Y.shape)
print(np.unique(Y))


# Part B.)

# We can make the column names for every column in array X by using pythons list comprehension, 
# this makes it easier to list which feature column is which for the filtering step.
xy_df = pd.DataFrame(X, columns=[f'Feature_{i+1}' for i in range(X.shape[1])])

# then we can just add the target values/labels to the end/right-most column of the dataframe!
xy_df['Target'] = Y

# EDGE CASE: Check if DataFrame was created correctly
if xy_df.isnull().values.any():
    raise ValueError("Error: DataFrame contains NaN values!")

# Verify by printing first 5 observations of dataframe
print(xy_df.head(5))
print('\n')

# Filtering steps
filter_y0 = xy_df[(xy_df['Target'] == 0) & (xy_df['Feature_2'] < 0)]
filter_y1 = xy_df[(xy_df['Target'] == 1) & (xy_df['Feature_3'] > 0)]
filter_y2 = xy_df[(xy_df['Target'] == 2) & (xy_df['Feature_4'].between(-1,1))]

# Combine all filtered conditions into filtered dataframe
xy_df_filtered = pd.concat([filter_y0, filter_y1, filter_y2])

# EDGE CASE: Check if filtered DataFrame is empty
if (xy_df_filtered.empty):
    raise ValueError("Error: The filtered DataFrame is empty!")

# Verify by printing first 5 of filtered dataframe
print(xy_df_filtered.head(5))
print('\n')


# Part C.)

# Convert just the filtered features to a numpy array! the iloc is selecting ALL columns besides the last one due to slicing method
x_arr_filtered = xy_df_filtered.iloc[:, :-1].to_numpy()

# Convert just the filtered targets to a numpy array! the iloc is selecting JUST the last column
y_arr_filtered = xy_df_filtered.iloc[:, -1].to_numpy()

# EDGE CASE: Check if extracted arrays are empty
if (x_arr_filtered.shape[0] == 0 or y_arr_filtered.shape[0] == 0):
    raise ValueError("Error: Filtered NumPy arrays are empty!")

# EDGE CASE: Check if filtered X and Y are aligned
if (x_arr_filtered.shape[0] != y_arr_filtered.shape[0]):
    raise ValueError("Error: Filtered X and Y arrays have different row counts!")

# Check the newly created numpy arrays shapes compare to original array shapes
print('Filtered X:',x_arr_filtered.shape)
print('Filtered Y:',y_arr_filtered.shape)
print('\n')

# Only print the first 5 rows of the newly seperated arrays becuase these are massive arrays
print('Filtered features (X) array:\n', x_arr_filtered[:5])
print('\n')
print('Filtered targets (Y) array:\n', y_arr_filtered[:5])
