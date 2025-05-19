# -*- coding: utf-8 -*-
"""
Created on Mon Apr 21 08:32:31 2025

@author: aiden
"""

from sklearn.datasets import load_iris
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import numpy as np
import matplotlib.pyplot as plt


# First we will define random k-values in a hard coded range, for now we can make it 1-10, we can also define a global variable for accuracies
k_values = list(range(1, 11))
accuracies = []

# Load and Look at dataset, not meaningful but I was curious...
iris_data = load_iris()
X = iris_data.data
y = iris_data.target

''' 
We can see there is no need to clean the data, as expected since its a sklearn dataset!

Now lets split the data into testing and splitting using sklearns train_test_split function

Then we can use StandardScalar to scale it since it is a distance based algorithm!
'''

test_size = 0.25

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=42)
scalar = StandardScaler()
X_train = scalar.fit_transform(X_train)
X_test = scalar.transform(X_test)

# Now we can apply those
for k in k_values:
    knn = KNeighborsClassifier(n_neighbors=k, leaf_size=40)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    acc = accuracy_score(y_test, y_pred)
    accuracies.append(acc)

# Create the graph
plt.plot(k_values, accuracies, marker='o')
plt.xlabel('K Values')
plt.ylabel('Accuracy')
plt.title('KNN Accuracy using Different K Values')
plt.grid()
plt.show()

# Debug statement to tell me what my set testing size is
print(f'Running with Test Size: {test_size} on split')

# We can also print the best k value using numpy!
best_k = k_values[np.argmax(accuracies)]
best_acc = max(accuracies)
print(f"Best K: {best_k} with Accuracy: {best_acc:.4f}")