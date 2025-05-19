# -*- coding: utf-8 -*-
"""
Created on Tue Apr 22 20:04:01 2025

@author: aiden
"""

from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

breast_cancer_data = load_breast_cancer(as_frame=True)
df = breast_cancer_data.frame
X = df.drop(columns='target') # Everything but Target Column
y = df['target'] # Just the Target Column

test_size = 0.3

# Train Test Split the data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)

# Single Decision Tree
dtc = DecisionTreeClassifier(random_state=42)
dtc.fit(X_train, y_train)
y_pred_dtc = dtc.predict(X_test)
print("Single Decision Tree Accuracy:", accuracy_score(y_test, y_pred_dtc))

# AdaBoost with decision stumps
base_tree = DecisionTreeClassifier(max_depth=1, random_state=42)
ada = AdaBoostClassifier(estimator=base_tree, n_estimators=50, random_state=42)
ada.fit(X_train, y_train)
y_pred_ada = ada.predict(X_test)
print("AdaBoost Accuracy:", accuracy_score(y_test, y_pred_ada))