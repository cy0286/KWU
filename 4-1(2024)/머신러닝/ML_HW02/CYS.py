# -*- coding: utf-8 -*-

import copy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn import datasets
from sklearn.cluster import KMeans
import warnings
warnings.filterwarnings("ignore") # To use eliminate seaborn warnings

# Seed setting
seed_num = 2022
#np.random.seed(seed_num)
iteration = 100     # Number of times to repeat steps E and M.


class EM:
    def __init__(self, n_clusters, iteration):

        """
        Expectation-Maximization (EM) clustering algorithm
        
        Parameter
        - n_clusters : Number of clusters to partition the data
        - iteration : Number of iterations for EM alrgorithm

        Attributes
        - n_clusters : Number of clusters
        - iteration : Number of iterations
        - mean : Mean vectors for each cluster
        - sigma : Covariance matrix for each cluster
        - pi : Prior probability that each cluster

        """

        self.n_clusters = n_clusters # Initialize number of clusters attribute   
        self.iteration = iteration # Initialize number of iterations attribute
        self.mean = np.zeros((3, 4)) # Initialize mean vectors
        self.sigma = np.zeros((3, 4, 4)) # Initialize covariance matrices
        self.pi = np.zeros((3)) # Initialize prior probablility

    def initialization(self, data):

        """
        Initialize cluster parameters(mean, sigma, and pi)
        
        Parameter
        - data : Input data matrix
        """

        # Randomly select data points as initial mean vectors for each cluster
        self.mean = data[np.random.choice(data.shape[0], size = self.n_clusters, replace=False)]
        # Initialize covariance matrices for each cluster as identity matrices
        self.sigma = np.array([np.eye(4)] * self.n_clusters)
        # Initialize prior probabilities for each cluster uniformly
        self.pi = np.ones(self.n_clusters) / self.n_clusters

    def multivariate_gaussian_distribution(self, data, mean, sigma):

        """
        Calculate multivariate Gaussian probability density function
        Computes the probability density function (PDF) value for a given data point with respect 
        to a multivariate Gaussian distribution defined by the mean vector and covariance matrix

        Parameter
        - data : Input data point
        - mean : Mean vector of the distribution
        - sigma : Covariance matrix of the distribution
        """
        
        # Calculate the difference between the data point and the mean vector
        diff = data - mean
        # Calculate the determinant of the covariance matrix
        det_sigma = np.linalg.det(sigma)
        # Calculate the inverse of the covariance matrix
        inv_sigma = np.linalg.inv(sigma)
        # Calculate the constant term in the Gaussian distribution formula
        constant = 1 / ((2 * np.pi) ** (4 / 2) * det_sigma ** 0.5)
        # Calculate the exponent term in the Gaussian distribution formul
        exponent = -0.5 * np.dot(diff, np.dot(inv_sigma, diff.T))
        # Calculate the probability density function value
        return constant * np.exp(exponent)
    
    def expectation(self, data):

        """
        Expectation step of the EM algorithm
        Computes the posterior probabilities of each data point 
        belonging to each cluster in the EM algorithm
        
        Parameter
        - data : Input data matrix
        """

        # Initialize an array to store posterior probabilities
        posterior = np.zeros((data.shape[0], self.n_clusters))

        for n in range(data.shape[0]): # Loop through each data point
            total_likelihood = 0
            for k in range(self.n_clusters): # Loop through each cluster
                # Get parameters for the current cluster
                pi = self.pi[k]
                mean = self.mean[k]
                sigma = self.sigma[k]

                # Calculate the likelihood of the data point belonging to the current cluster
                likelihood = self.multivariate_gaussian_distribution(data[n], mean, sigma)
                # Calculate the unnormalized posterior probability
                temp = pi * likelihood
                total_likelihood += temp
                posterior[n][k] = temp
            posterior[n] /= total_likelihood  # Normalize the posterior probabilities for the current data point
        return posterior
    
    def maximization(self, data, posterior):

        """
        Maximization step of the EM algorithm
        Updates cluster parameters based on data and posterior probabilities

        Parameter
        - data : Input data matrix
        - posterior : Posterior probabilities of data point belonging to each cluster
        """

        for k in range(self.n_clusters): # Loop through each cluster
            
            # Update mean for the current cluster
            mean_sum = np.zeros_like(self.mean[k]) 
            for i in range(data.shape[0]):
                mean_sum += posterior[i, k] * data[i] # Accumulate the weighted sum of data points
            # Update mean by dividing the sum by the total posterior probability for the cluster
            self.mean[k] = mean_sum / np.sum(posterior[:, k]) 
            
            # Update covariance matrix for the current cluster
            sigma_sum = np.zeros_like(self.sigma[k]) 
            for i in range(data.shape[0]):
                diff = data[i] - self.mean[k] # Compute the difference between the data point and the mean
                sigma_sum += posterior[i, k] * np.outer(diff, diff) # Accumulate the weighted sum of outer products
            # Update covariance matrix by dividing the sum by the total posterior probability for the cluster
            self.sigma[k] = sigma_sum / np.sum(posterior[:, k])  

            # Update the prior probability for the current cluster
            self.pi[k] = np.mean(posterior[:, k])  

    def fit(self, data):

        """
        Fit the EM model to the input data
        Fits the EM model to the given input data by initializing cluster parameters, 
        performing iterations of the expectation-maximization algorithm, and returning 
        the predicted cluster assignments for each data point

        Parameter
        - data : Input data matrix
        """
         
        self.initialization(data = data) # Initialize cluster parameters
        
        for i in range(self.iteration): # Perform iterations of the expectation-maximization algorithm
            posterior = self.expectation(data = data)
            self.maximization(data = data, posterior = posterior)
            
        # Format predictions by selecting the cluster with the highest posterior probabilit
        prediction = np.argmax(posterior, axis=1)
        return prediction
    
def plotting(data, labels):

    """
    Plot pairwise relationships in a dataset
    Visualizes pairwise relationships between features 
    in the input data matrix using a seaborn pairplo

    Parameter
    - data : Input data matrix
    - labels : Labels for each data point
    """
    # Create a pairplot using seaborn and assigning colors based on the provided labels
    sns.pairplot(pd.DataFrame(data=data, columns=iris['feature_names']).assign(labels=labels), hue='labels')
    plt.show()

if __name__ == '__main__':
    # Loading and labeling data
    iris = datasets.load_iris()
    original_data = pd.DataFrame(data=np.c_[iris['data'], iris['target']], columns=iris['feature_names'] + ['labels'])
    original_data['labels'] = original_data['labels'].map({0: 'setosa', 1: 'versicolor', 2: 'virginica'})
    plotting(original_data.drop(columns=['labels']), original_data['labels']) # Visualize the original data
    
    data = iris['data']
    
    # Unsupervised learning(clustering) using EM algorithm
    EM_model = EM(n_clusters=3, iteration=iteration)
    EM_pred = EM_model.fit(data)
    EM_pd = pd.DataFrame(data=np.c_[data, EM_pred], columns=iris['feature_names'] + ['labels'])
    EM_pd['labels'] = EM_pd['labels'].map({0:'setosa', 1:'versicolor', 2:'virginica'})
    plotting(EM_pd.drop(columns=['labels']), EM_pd['labels']) # Visualize clustering results using EM algorithm
    
    # Print EM algorithm results
    print(f'pi :            {EM_model.pi}')
    print(f'count / total : {np.bincount(EM_pred) / 150}')
    
    # Unsupervised learning(clustering) using KMeans algorithm
    KM_model = KMeans(n_clusters=3, init='random', random_state=seed_num, max_iter=iteration).fit(data)
    KM_pred = KM_model.predict(data)
    KM_pd = pd.DataFrame(data=np.c_[data, KM_pred], columns=iris['feature_names'] + ['labels'])
    KM_pd['labels'] = KM_pd['labels'].map({0:'setosa', 1:'versicolor', 2:'virginica'})
    plotting(KM_pd.drop(columns=['labels']), KM_pd['labels'] )# Visualize clustering results using KMeans algorithm
    
    # Evaluate and print clustering performance
    for idx in range(2):
        EM_point = np.argmax(np.bincount(EM_pred[idx*50:(idx+1)*50]))
        KM_point = np.argmax(np.bincount(KM_pred[idx*50:(idx+1)*50]))
        EM_pred = np.where(EM_pred == idx, 3, EM_pred)
        EM_pred = np.where(EM_pred == EM_point, idx, EM_pred)
        EM_pred = np.where(EM_pred == 3, EM_point, EM_pred)
        KM_pred = np.where(KM_pred == idx, 3, KM_pred)
        KM_pred = np.where(KM_pred == KM_point, idx, KM_pred)
        KM_pred = np.where(KM_pred == 3, KM_point, KM_pred)
    
    EM_hit = np.sum(iris['target']==EM_pred)
    KM_hit = np.sum(iris['target']==KM_pred)
    print(f'EM Accuracy: {round(EM_hit / 150,2)}    Hit: {EM_hit} / 150')
    print(f'KM Accuracy: {round(KM_hit / 150,2)}    Hit: {KM_hit} / 150')