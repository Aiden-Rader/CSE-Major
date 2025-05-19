# -*- coding: utf-8 -*-
"""
Created on Wed Apr 23 12:48:47 2025

@author: aiden
"""

from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

wine_data = load_wine(as_frame=True)
df = wine_data.frame
X = df.drop(columns='target') # Everything but Target Column
y = df['target'] # Just the Target Column

test_size = 0.3

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)

# Scale the features (VERY important for SVMs!)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

'''
Now we can load the two kernel types including:
    Linear
    Radial Basis Function (RBF)
'''

# Linear Kernel
svm_linear = SVC(kernel='linear')
svm_linear.fit(X_train, y_train)
y_pred_linear = svm_linear.predict(X_test)
acc_linear = accuracy_score(y_test, y_pred_linear)
print(f"Linear Kernel Accuracy: {acc_linear}")

# RBF Kernel
svm_rbf = SVC(kernel='rbf')
svm_rbf.fit(X_train, y_train)
y_pred_rbf = svm_rbf.predict(X_test)
acc_rbf = accuracy_score(y_test, y_pred_rbf)
print(f"RBF Kernel Accuracy: {acc_rbf}")