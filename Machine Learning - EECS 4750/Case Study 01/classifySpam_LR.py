# -*- coding: utf-8 -*-
"""
Classification using Linear Regression and Scaling becuase we can!

@author: aiden
"""

from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler

# The predictTest function that we use for the LR model
def predictTest(trainFeatures, trainLabels, testFeatures):
    scaler = StandardScaler()
    trainScaled = scaler.fit_transform(trainFeatures)
    testScaled = scaler.transform(testFeatures)

    model = LogisticRegression(
        penalty='l2',
        C=1.0,
        solver='lbfgs',
        max_iter=500,
        random_state=42
    )
    model.fit(trainScaled, trainLabels)

    return model.predict_proba(testScaled)[:, 1], 'LR'
