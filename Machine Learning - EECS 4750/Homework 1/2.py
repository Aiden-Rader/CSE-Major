# -*- coding: utf-8 -*-
"""
Created on Wed Feb  5 19:25:08 2025

@author: Aiden Rader

Homework 1.2

Given a matrix M of shape n× n, implement the following operations using Numpy:
    a. Compute the determinant and inverse of matrix M (if invertible).
    b. Find the eigenvalues and eigenvectors of matrix M.
    c. Implement a function to check if M is a symmetric matrix and return True or False.
    d. Generate a random matrix R of shape n ×n and compute the matrix multiplication M * R.
    e. Return the trace (sum of diagonal elements) of the resultant matrix.
"""

import numpy as np

def comp_det_and_inverse(M):
    det = np.linalg.det(M)
    print('\n The determinate of matrix M is: \n', det)

    # Handle non-inversable matrix gracefully with error handling
    try: 
        inv = np.linalg.inv(M)
        print('\n The inverse of matrix M is: \n', inv)
    except np.linalg.LinAlgError:
        print("Matrix M is not invertable")
    
def find_eign(M):
    e_val = np.linalg.eigvals(M)
    e_vect = np.linalg.eig(M)
    print('\n The eignvalues of matrix M is: \n', e_val)
    print('\n The eignvectors of matrix M is: \n', e_vect)

# Note: this was done using array_equal and transposing M and comparing the two arrays
def is_symmetric(M):
    is_sym = np.array_equal(M, M.T)
    print('\n Is Matrix M symmetric: ', is_sym)

def rand_arr_comp(M):
    R = np.random.randint(50, size=M.shape)
    # print('\n Matrix R: \n', R)  # Debug statement if you want to see matrix R
    res = M * R
    print('\n Matrix\'s M * R = \n', res)
    
def get_trace(M):
    diag_sum = np.trace(M)
    print('\n Matrix M\'s trace is: ', diag_sum)


# MAIN CODE #

# Create n x n matrix with some hardcoded test values
M = np.array([[40, 32], [74, 21]])

# Initial print of the array
print(M)

# Sub-Parts Function calls #

# Part A.)
comp_det_and_inverse(M)

# Part B.)
find_eign(M)

# Part C.)
is_symmetric(M)

# Part D.)
rand_arr_comp(M)

# Part E.)
get_trace(M)