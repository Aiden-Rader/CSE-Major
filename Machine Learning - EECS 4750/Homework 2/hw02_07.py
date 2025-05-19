# -*- coding: utf-8 -*-
"""
Created on Wed Apr 23 16:34:01 2025

@author: aiden
"""

from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Had to fetch it via openml since regular boston dataset is depreicated
boston_data = fetch_openml(name='boston', version=1, parser='auto', as_frame=True)
X = boston_data.data
y = boston_data.target

test_size = 0.3
n_components = 10
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)

# Scale the features!
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# No PCA Linear Regression
lin_reg_plain = LinearRegression()
lin_reg_plain.fit(X_train, y_train)
y_pred_plain = lin_reg_plain.predict(X_test)

print("-- Linear Regression w/o PCA --")
print("R2 Score:", r2_score(y_test, y_pred_plain))
print("MSE:", mean_squared_error(y_test, y_pred_plain))

print('')

# With PCA Linear Regression
pca = PCA(n_components=n_components)
X_train_pca = pca.fit_transform(X_train)
X_test_pca = pca.transform(X_test)

model_pca = LinearRegression()
model_pca.fit(X_train_pca, y_train)
y_pred_pca = model_pca.predict(X_test_pca)

print("-- Linear Regression w/ PCA --")
print("R2 Score:", r2_score(y_test, y_pred_pca))
print("MSE:", mean_squared_error(y_test, y_pred_pca))