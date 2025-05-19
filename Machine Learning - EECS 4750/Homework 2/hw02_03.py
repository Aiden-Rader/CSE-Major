# -*- coding: utf-8 -*-
"""
Created on Tue Apr 22 10:27:28 2025

@author: aiden
"""

from sklearn.datasets import load_breast_cancer
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt

breast_cancer_data = load_breast_cancer(as_frame=True)
df = breast_cancer_data.frame
X = df.drop(columns='target') # Everything but Target Column
y = df['target'] # Just the Target Column

# Set up some global variables
test_size = 0.3
max_depth = 4
n_estimators = list(range(1,26))
accuracies = []

# Test the split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)

# 1 tree to 25 trees
for n in n_estimators:
    rfc = RandomForestClassifier(
        n_estimators=n,
        max_depth=max_depth,
        random_state=42
        )
    rfc.fit(X_train, y_train)
    y_pred = rfc.predict(X_test)
    # acc = rfc.score(y_test, y_pred) # Testing this out, this did not return what I thought it would
    acc = accuracy_score(y_test, y_pred)
    accuracies.append(acc)


# Debug statement to tell me what my set testing size is
print(f'Running with Test Size: {test_size} split')

plt.plot(n_estimators, accuracies, marker='o')
plt.xlabel('Number of Trees')
plt.ylabel('Accuracy Score')
plt.title('Random Tree Classifier Accuracies with n_estimators')
plt.grid()
plt.show()