# -*- coding: utf-8 -*-
"""
Created on Sun Feb  9 12:51:45 2025

@author: Aiden Rader

Homework 1.5

Write a program that:
    a. Generate synthetic regression data using make_regression.
    b. Train models (Linear Regression, KNN Regressor, Decision Tree Regressor).
    c. Evaluate models using MSE and R² score.
    d. Visualize predictions using scatter plots and line graphs.
    e. Plot error vs. model complexity (k for KNN, depth for Decision Tree).
"""

# General imports
import pandas as pd
import matplotlib.pyplot as plt

# scikit-learn import(s)
from sklearn.datasets import make_regression
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.neighbors import KNeighborsRegressor
from sklearn.tree import DecisionTreeRegressor
from sklearn.metrics import mean_squared_error, r2_score

# Part A.)

# Make random data using 1000 samples, 6 or so features, some noise so that it is realistic, and a state reproducibility 
X, y = make_regression(n_samples=1000, n_features=6, noise=10, random_state=42)

# Convert to Pandas DataFrame to see what the data looks like
regression_df = pd.DataFrame(X, columns=[f'Feature_{i+1}' for i in range(X.shape[1])])
regression_df['Target'] = y

# Verify first 5 rows in the dataset
print("Preview of the dataset:")
print(regression_df.head(5))


# Part B.)

# Train test split data based upon X and y arrays!
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# LinearRegression Model w/ prediction
reg_model = LinearRegression()
reg_model.fit(X_train, y_train)
reg_y_pred = reg_model.predict(X_test)

# KNNRegression Model w/ prediction (addition of n_neighbors, more generalized model)
knn_model = KNeighborsRegressor(n_neighbors=5)
knn_model.fit(X_train, y_train)
knn_y_pred = knn_model.predict(X_test)

# Decsion Tree Regression Model w/ prediction (addition of a max_depth)
dtr_model = DecisionTreeRegressor(max_depth=5)
dtr_model.fit(X_train, y_train)
dtr_y_pred = dtr_model.predict(X_test)


# Part C.)

# LinearRegression MSE and R2 score
reg_mse = mean_squared_error(y_test, reg_y_pred)
reg_r2 = r2_score(y_test, reg_y_pred)

# KNNRegression MSE and R2 score
knn_mse = mean_squared_error(y_test, knn_y_pred)
knn_r2 = r2_score(y_test, knn_y_pred)

# Decsion Tree Regression MSE and R2 score
dtr_mse = mean_squared_error(y_test, dtr_y_pred)
dtr_r2 = r2_score(y_test, dtr_y_pred)

# Print Evaluation Metrics
print("\nModel Performance:\n")
print(f'Linear Regression\nMSE: {reg_mse:.2f} \nR2: {reg_r2:.2f}\n')
print(f'KNN Regression\nMSE: {knn_mse:.2f} \nR2: {knn_r2:.2f}\n')
print(f'Decision Tree Regression\nMSE: {dtr_mse:.2f} \nR2: {dtr_r2:.2f}\n')


# Part D.)

# Create the plt figure and make the scatter plots for each Training Senario
plt.figure(figsize=(12,6))
plt.scatter(y_test, reg_y_pred, alpha=0.6, label="Linear Regression", color="blue")
plt.scatter(y_test, knn_y_pred, alpha=0.6, label="KNN Regression", color="green")
plt.scatter(y_test, dtr_y_pred, alpha=0.6, label="Decision Tree", color="red")
plt.plot([-400, 300], [-400, 300], color="black", linestyle="--")
plt.xlabel("True Values")
plt.ylabel("Predicted Values")
plt.title("Model Predictions vs. True Values")
plt.legend()
plt.show()

# Part E.)
knn_errors = []
k_vals = list(range(1,20))
for k in k_vals:
    knn = KNeighborsRegressor(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    knn_errors.append(mean_squared_error(y_test, y_pred))

tree_errors = []
depth_vals = list(range(1, 20))
for depth in depth_vals:
    dtr = DecisionTreeRegressor(max_depth=depth)
    dtr.fit(X_train, y_train)
    y_pred = dtr.predict(X_test)
    tree_errors.append(mean_squared_error(y_test, y_pred))
    
# Plot Error vs. Model Complexity between KNN and Decision Tree Regressors
plt.figure(figsize=(12, 6))
plt.plot(k_vals, knn_errors, label="KNN: MSE vs. k", marker='o', linestyle='dashed')
plt.plot(depth_vals, tree_errors, label="Decision Tree: MSE vs. Depth", marker='s', linestyle='dashed')
plt.xlabel("Model Complexity")
plt.ylabel("Mean Squared Error")
plt.title("Model Complexity vs. Error")
plt.legend()
plt.show()
