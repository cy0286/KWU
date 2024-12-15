#!/usr/bin/env python
# coding: utf-8

# In[92]:


import os
import numpy as np
from PIL import Image
import torch
import torchvision
from torchvision import transforms, datasets
from torch.utils.data import DataLoader
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier

# PCA 구현
def pca(X, num_components):
    # 데이터의 평균을 계산
    mean = np.mean(X, axis=0)
    
    # 데이터에서 평균을 빼줌
    X = X.astype(np.float64)  # Convert X to float64
    mean = mean.astype(np.float64)  # Convert mean to float64
    X -= mean
    
    # 공분산 행렬 계산
    cov_matrix = np.cov(X, rowvar=False)
    
    # 공분산 행렬의 고유값과 고유벡터 계산
    eigenvalues, eigenvectors = np.linalg.eigh(cov_matrix)
    
    # 고유값을 내림차순으로 정렬
    sorted_indices = np.argsort(eigenvalues)[::-1]
    
    # 상위 num_components개의 고유벡터 선택
    top_indices = sorted_indices[:num_components]
    
    # 선택된 고유벡터로 데이터를 변환
    pca_result = np.dot(X, eigenvectors[:, top_indices])
    
    return pca_result

# 데이터셋 가져오기
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder(root="dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="dataset/Test", transform=transform)

train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

# PCA 적용
X_train, y_train = next(iter(train_dataloader))
X_test, y_test = next(iter(test_dataloader))

num_components = 1  # Set the number of PCA components
X_train_pca = pca(X_train.view(X_train.size(0), -1).numpy(), num_components)
X_test_pca = pca(X_test.view(X_test.size(0), -1).numpy(), num_components)

# KNN 모델 훈련
knn_model = KNeighborsClassifier(n_neighbors=1)
knn_model.fit(X_train_pca, y_train)

# 예측 및 정확도 계산
y_pred = knn_model.predict(X_test_pca)
accuracy = accuracy_score(y_test, y_pred)

print(f"Accuracy: {accuracy * 100:.2f}%")


# In[94]:


import os
import numpy as np
from PIL import Image
from sklearn.decomposition import PCA
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier
import torch
from torchvision import transforms, datasets
from torch.utils.data import DataLoader

# 데이터셋 가져오기
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder(root="dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="dataset/Test", transform=transform)

train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

# PCA 적용
X_train, y_train = next(iter(train_dataloader))
X_test, y_test = next(iter(test_dataloader))

num_components = 1  # Set the number of PCA components

# Scikit-learn PCA 사용
pca_model = PCA(n_components=num_components)
X_train_pca = pca_model.fit_transform(X_train.view(X_train.size(0), -1).numpy())
X_test_pca = pca_model.transform(X_test.view(X_test.size(0), -1).numpy())

# KNN 모델 훈련
knn_model = KNeighborsClassifier(n_neighbors=1)
knn_model.fit(X_train_pca, y_train)

# 예측 및 정확도 계산
y_pred = knn_model.predict(X_test_pca)
accuracy = accuracy_score(y_test, y_pred)

print(f"Accuracy: {accuracy * 100:.2f}%")


# In[1]:


import os
import numpy as np
import torch
import torchvision
from torchvision import transforms, datasets
from torch.utils.data import DataLoader
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier

# LDA 구현
def lda(X, y, num_components, reg_param=1e-2):
    # 데이터의 클래스 수
    classes = np.unique(y)
    num_classes = len(classes)
    
    # 데이터의 차원
    num_features = X.shape[1]
    
    # 클래스별 평균 벡터 계산
    class_means = np.array([np.mean(X[y == c], axis=0) for c in classes])
    
    # 전체 평균 벡터 계산
    overall_mean = np.mean(X, axis=0)
    
    # 클래스 간 산포 행렬과 클래스 내 산포 행렬 계산
    Sb = np.dot((class_means - overall_mean).T, (class_means - overall_mean))
    Sw = sum([np.dot((X[y == c] - class_mean).T, X[y == c] - class_mean) for c, class_mean in zip(classes, class_means)])
    Sw += reg_param * np.eye(num_features)
    
    # 고유값 분해
    eigenvalues, eigenvectors = np.linalg.eigh(np.dot(np.linalg.inv(Sw), Sb))
    
    # 고유값을 내림차순으로 정렬
    sorted_indices = np.argsort(eigenvalues)[::-1]
    
    # 상위 num_components개의 고유벡터 선택
    top_indices = sorted_indices[:num_components]
    
    # 선택된 고유벡터로 데이터를 변환
    lda_result = np.dot(X, eigenvectors[:, top_indices])
    
    return lda_result

# 데이터셋 가져오기
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder(root="dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="dataset/Test", transform=transform)

train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

# LDA 적용
X_train, y_train = next(iter(train_dataloader))
X_test, y_test = next(iter(test_dataloader))

num_components = 1  # Set the number of LDA components
X_train_lda = lda(X_train.view(X_train.size(0), -1).numpy(), y_train.numpy(), num_components)
X_test_lda = lda(X_test.view(X_test.size(0), -1).numpy(), y_test.numpy(), num_components)

# KNN 모델 훈련
knn_model = KNeighborsClassifier(n_neighbors=1)
knn_model.fit(X_train_lda, y_train)

# 예측 및 정확도 계산
y_pred = knn_model.predict(X_test_lda)
accuracy = accuracy_score(y_test, y_pred)

print(f"Accuracy: {accuracy * 100:.2f}%")


# In[5]:


import os
import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier
import torch
from torchvision import transforms, datasets
from torch.utils.data import DataLoader

# 데이터셋 가져오기
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])

train_dataset = datasets.ImageFolder(root="dataset/Training", transform=transform)
test_dataset = datasets.ImageFolder(root="dataset/Test", transform=transform)

train_dataloader = DataLoader(train_dataset, batch_size=len(train_dataset), shuffle=False)
test_dataloader = DataLoader(test_dataset, batch_size=len(test_dataset), shuffle=False)

# LDA 적용
X_train, y_train = next(iter(train_dataloader))
X_test, y_test = next(iter(test_dataloader))

num_components = 1  # Set the number of LDA components
lda_model = LinearDiscriminantAnalysis(n_components=num_components)
X_train_lda = lda_model.fit_transform(X_train.view(X_train.size(0), -1).numpy(), y_train.numpy())
X_test_lda = lda_model.transform(X_test.view(X_test.size(0), -1).numpy())

# KNN 모델 훈련
knn_model = KNeighborsClassifier(n_neighbors=1)
knn_model.fit(X_train_lda, y_train)

# 예측 및 정확도 계산
y_pred = knn_model.predict(X_test_lda)
accuracy = accuracy_score(y_test, y_pred)

print(f"Accuracy: {accuracy * 100:.2f}%")

