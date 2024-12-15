# -*- coding: utf-8 -*-

import numpy as np
      
def feature_normalization(data): # 10 points
    # parameter 
    feature_num = data.shape[1]
    data_point = data.shape[0]
    
    # you should get this parameter correctly
    normal_feature = np.zeros([data_point, feature_num])
    mu = np.zeros([feature_num])
    std = np.zeros([feature_num])
    
    # your code here
    # calculate mean and standard deviation
    mu = np.mean(data, axis = 0)
    std = np.std(data, axis = 0)

    # normalize data
    normal_feature = (data - mu) / std
    # end

    return normal_feature

 # split the data and labels into training and testing sets based on the split factor
def split_data(data, label, split_factor):
    return  data[:split_factor], data[split_factor:], label[:split_factor], label[split_factor:]

def get_normal_parameter(data, label, label_num): # 20 points
    # parameter
    feature_num = data.shape[1]
    
    # you should get this parameter correctly    
    mu = np.zeros([label_num,feature_num])
    sigma = np.zeros([label_num,feature_num])

    # your code here
    # calculate mean and standard deviation for each feature for data with label i
    for i in range(label_num):
        mu[i] = np.mean(data[label == i], axis=0)
        sigma[i] = np.std(data[label == i], axis=0)
    # end
    
    return mu, sigma

def get_prior_probability(label, label_num): # 10 points
    # parameter
    data_point = label.shape[0]
    
    # you should get this parameter correctly
    prior = np.zeros([label_num])
    
    # your code here
    # calculate prior probability for each label
    for i in range(label_num):
        prior[i] = np.sum(label == i) / data_point
    # end
    return prior

def Gaussian_PDF(x, mu, sigma): # 10 points
    # calculate a probability (PDF) using given parameters
    # you should get this parameter correctly
    pdf = 0
    
    # your code here
    # calculate the exponent part
    exponent = -(x - mu) ** 2 / (2 * sigma ** 2)
    # calculate the pdf using the Gaussian formula
    pdf = (1 / (np.sqrt(2 * np.pi * sigma ** 2))) * np.exp(exponent)
    # end
    
    return pdf

def Gaussian_Log_PDF(x, mu, sigma): # 10 points
    # calculate a probability (PDF) using given parameters
    # you should get this parameter correctly
    log_pdf = 0
    
    # your code here
    # calculate the exponent part
    exponent = -(x - mu) ** 2 / (2 * sigma ** 2)
    # calculate the log pdf using the Gaussian formula
    log_pdf = -0.5 * np.log(2 * np.pi * sigma ** 2) + exponent
    # end
    
    return log_pdf

def Gaussian_NB(mu, sigma, prior, data): # 40 points
    # parameter
    data_point = data.shape[0]
    label_num = mu.shape[0]
    
    # you should get this parameter correctly   
    likelihood = np.zeros([data_point, label_num])
    posterior = np.zeros([data_point, label_num])
    ## evidence can be ommitted because it is a constant
    
    # your code here
        ## Function Gaussian_PDF or Gaussian_Log_PDF should be used in this section
    # loop through each data point
    for i in range(data_point):
        # Loop through each class 
        for j in range(label_num):
            # calculate the log likelihood
            likelihood[i, j] = np.sum(Gaussian_Log_PDF(data[i], mu[j], sigma[j]))
            # calculate the posterior probability
            posterior[i, j] = likelihood[i, j] + np.log(prior[j])
            
            #likelihood[i, j] = np.prod(Gaussian_PDF(data[i], mu[j], sigma[j]))
            #posterior[i, j] = np.log(likelihood[i, j]) + np.log(prior[j])
    # end
    return posterior

# predicts class labels based on posterior probabilities
def classifier(posterior):
    data_point = posterior.shape[0]
    prediction = np.zeros([data_point])
    
    prediction = np.argmax(posterior, axis=1)
    
    return prediction
        
# calculates classification accuracy
def accuracy(pred, gnd):
    data_point = len(gnd)
    
    hit_num = np.sum(pred == gnd)

    return (hit_num / data_point) * 100, hit_num

    ## total 100 point you can get 