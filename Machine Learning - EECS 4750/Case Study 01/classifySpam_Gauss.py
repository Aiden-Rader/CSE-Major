# -*- coding: utf-8 -*-
"""
Demo of 10-fold cross-validation using Gaussian naive Bayes on spam data

@author: FJS
"""

import numpy as np
import matplotlib.pyplot as pl
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import cross_val_score
from sklearn.metrics import roc_auc_score

def aucCV(features,labels):
    model = GaussianNB()
    scores = cross_val_score(model, features, labels, cv=10,scoring='roc_auc')
    
    return scores

def predictTest(trainFeatures,trainLabels,testFeatures):
    model = GaussianNB()
    model.fit(trainFeatures,trainLabels)
    
    # Use predict_proba() rather than predict() to use probabilities rather
    # than estimated class labels as outputs
    
    return model.predict_proba(testFeatures)[:,1], 'Gaussian'
    
# Run this code only if being used as a script, not being imported
if __name__ == "__main__":
    data = np.loadtxt('spam2.csv',delimiter=',')
    # Randomly shuffle rows of data set then separate labels (last column)
    shuffleIndex = np.arange(np.shape(data)[0])
    np.random.shuffle(shuffleIndex)
    data = data[shuffleIndex,:]
    features = data[:,:-1]
    labels = data[:,-1]
    
    # Evaluating classifier accuracy using 10-fold cross-validation
    print("10-fold cross-validation mean AUC: ",
          np.mean(aucCV(features,labels)))
    
    # Arbitrarily choose all odd samples as train set and all even as test set
    # then compute test set AUC for model trained only on fixed train set
    trainFeatures = features[0::2,:]
    trainLabels = labels[0::2]
    testFeatures = features[1::2,:]
    testLabels = labels[1::2]
    testOutputs = predictTest(trainFeatures,trainLabels,testFeatures)
    print("Test set AUC: ", roc_auc_score(testLabels,testOutputs))
    
    # Examine outputs compared to labels
    sortIndex = np.argsort(testLabels)
    nTestExamples = testLabels.size
    pl.subplot(2,1,1)
    pl.plot(np.arange(nTestExamples),testLabels[sortIndex],'b.')
    pl.xlabel('Sorted example number')
    pl.ylabel('Target')
    pl.subplot(2,1,2)
    pl.plot(np.arange(nTestExamples),testOutputs[sortIndex],'r.')
    pl.xlabel('Sorted example number')
    pl.ylabel('Output (predicted target)')
    