# -*- coding: utf-8 -*-
"""
Created on Sun Mar 23 00:34:38 2025

@author: Aiden Rader
"""

# Exploring Datasets with different ways to examine our spam data before training the model

import pandas as pd
import matplotlib.pyplot as plt

# When reading in the csv, I chose no header since we are have no particular header for these!
df = pd.read_csv(r"C:\Users\aiden\OneDrive - University of Toledo\Spring 2025 UT (NOW)\Machine Learning\Homework\Case Study 01\spam2.csv", header=None)

dataset = 'spam2'

print(df.shape)  # This is really the only one I need since there are no headers

""" 
From looking at the shape I can see that there are 31 columns and 1499 rows.
from this I can assume atleast that the 31st column is our target value for the supervised learning part
"""

# GENERAL DATASET INFORMATION #

# Look at first 5 rows
print(df.head())

# Search for null values
print(df.info())

# Gives us a good summary of data (i.e. mean, std, etc.)
print(df.describe())

# Make sure the 31st column is the target column from quick glance
print(df.iloc[:, 30])

# Lets us know for sure this is our target column by giving us what values are in it
print(df.iloc[:, 30].unique())


# CORRELATIONS AND DISTRIBUTIONS #

# Gives us distribution of either 0's or 1's
print(df.iloc[:, 30].value_counts(normalize=True) * 100)

# shows correlations with our data
print(df.corr())


"""
This next portion will be the data visualization portion using matplotlib!
"""

# Count of Ham (0) and Spam (1)
df.iloc[:, 30].value_counts().plot(kind='bar')
plt.title("Spam vs. Ham Distribution for " + dataset)
plt.xlabel("Class Label (0 = Ham, 1 = Spam)")
plt.ylabel("Frequency")
plt.xticks(rotation=0)
plt.grid(True)
plt.show()

"""
Label distribution shows a fairly balanced dataset:
58.6% ham, 41.4% spam — this means we don't need to worry much about any class imbalance.
"""

# Plot histograms of first 6 features
df.iloc[:, :6].hist(bins=30, figsize=(12, 8))
plt.suptitle("Distributions of First 6 Word Features")
plt.tight_layout()
plt.show()



