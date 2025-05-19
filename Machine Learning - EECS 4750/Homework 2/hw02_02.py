# -*- coding: utf-8 -*-
"""
Created on Mon Apr 21 14:32:48 2025

@author: aiden
"""

from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.preprocessing import StandardScaler

# Load the 'heart' dataset
heart_data = fetch_openml('heart-disease', version=1, as_frame=True, parser='auto')
df = heart_data.frame
X = df.drop(columns='target') # Everything but Target Column
y = df['target'] # Just the Target Column

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Scale these features
scalar = StandardScaler()
X_train = scalar.fit_transform(X_train)
X_test = scalar.transform(X_test)

# First we make a baseline regular DTC (no prunning yet)
clf_reg = DecisionTreeClassifier(random_state=42)
clf_reg.fit(X_train, y_train)
y_pred_reg = clf_reg.predict(X_test)

print("-- No Pruning Model --")
print('')
print("Accuracy:", accuracy_score(y_test, y_pred_reg))
print('')
print(classification_report(y_test, y_pred_reg))


# The Prunned version of the DTC
clf_pruned = DecisionTreeClassifier(max_depth=4, min_samples_leaf=5, random_state=42)
clf_pruned.fit(X_train, y_train)
y_pred_pruned = clf_pruned.predict(X_test)

print("-- Pruning Model --")
print('')
print("Accuracy:", accuracy_score(y_test, y_pred_pruned))
print('')
print(classification_report(y_test, y_pred_pruned))
