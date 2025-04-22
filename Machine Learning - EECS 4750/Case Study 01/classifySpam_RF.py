# -*- coding: utf-8 -*-
"""
Classification using RF

@author: aiden
"""
from sklearn.ensemble import RandomForestClassifier

# The predictTest function that we use for the RF model
def predictTest(trainFeatures, trainLabels, testFeatures):
    
    model = RandomForestClassifier(
        n_estimators=500,
        max_features="sqrt",
        max_depth=None,
        random_state=42
    )
    
    model.fit(trainFeatures, trainLabels)
    
    return model.predict_proba(testFeatures)[:, 1], 'RF'

