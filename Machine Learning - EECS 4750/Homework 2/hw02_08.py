# -*- coding: utf-8 -*-
"""
Created on Wed Apr 23 16:55:21 2025

@author: aiden
"""

from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.multiclass import OneVsRestClassifier, OneVsOneClassifier
from sklearn.metrics import accuracy_score

# Load the digits datasets
digits_data = load_digits()
X = digits_data.data
y = digits_data.target

test_size = 0.3

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)

# Scale the features!
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Create the SVM model we will use for both OvR and OvO
svm = SVC(kernel='rbf', random_state=42)

# using One-vs-Rest (OvR)
ovr_model = OneVsRestClassifier(svm)
ovr_model.fit(X_train, y_train)
y_pred_ovr = ovr_model.predict(X_test)
acc_ovr = accuracy_score(y_test, y_pred_ovr)
print("One-vs-Rest (OvR) Accuracy:", acc_ovr)

# using One-vs-One (OvO)
ovo_model = OneVsOneClassifier(svm)
ovo_model.fit(X_train, y_train)
y_pred_ovo = ovo_model.predict(X_test)
acc_ovo = accuracy_score(y_test, y_pred_ovo)
print("One-vs-One (OvO) Accuracy:", acc_ovo)
