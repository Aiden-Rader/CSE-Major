# -*- coding: utf-8 -*-
"""
Classification using Gradient Boost

@author: aiden
"""

from sklearn.ensemble import GradientBoostingClassifier

# The predictTest function that we use for the RF model
def predictTest(trainFeatures, trainLabels, testFeatures):
    
    model = GradientBoostingClassifier(
        n_estimators=470,
        learning_rate=0.05,
        max_depth=4,
        subsample=0.8,
        random_state=42
    )
    
    # Fit the model with our training parameters
    model.fit(trainFeatures, trainLabels)
    
    # Return the probability statistics!
    return model.predict_proba(testFeatures)[:, 1]

