# -*- coding: utf-8 -*-
"""
Created on Wed Apr 23 16:01:07 2025

@author: aiden
"""

# Had to add this because of a annoying warning message, ignore this
import os
os.environ["OMP_NUM_THREADS"] = "1"

from sklearn.datasets import load_wine
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt


wine_data = load_wine(as_frame=True)
df = wine_data.frame
X = df.drop(columns='target') # Everything but Target Column
y = df['target'] # Just the Target Column

cluster_range = range(1, 9)

# Elbow Method
inertia = []

# Scale JUST the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

for n in cluster_range:
    kmeans = KMeans(n_clusters=n, random_state=42, n_init='auto')
    kmeans.fit(X_scaled)
    inertia.append(kmeans.inertia_)

plt.plot(cluster_range, inertia, marker='o')
plt.xlabel('Number of Clusters (k)')
plt.ylabel('Inertia')
plt.title('Elbow Method - KMeans on Wine Dataset')
plt.grid()
plt.show()