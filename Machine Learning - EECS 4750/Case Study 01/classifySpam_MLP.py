# -*- coding: utf-8 -*-
"""
Classification using MLP and scaling

@author: aiden
"""

from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler

# The predictTest function that we use for the MLP model
def predictTest(trainFeatures, trainLabels, testFeatures):
    scaler = StandardScaler()

    trainScaled = scaler.fit_transform(trainFeatures)
    testScaled = scaler.transform(testFeatures)
    
    model = MLPClassifier(
        hidden_layer_sizes=(64,),
        activation='logistic',
        solver='adam',
        max_iter=1000,
        alpha= 0.01,
        random_state=42
    )
    
    model.fit(trainScaled, trainLabels)
    
    return model.predict_proba(testScaled)[:, 1], 'MLP'
