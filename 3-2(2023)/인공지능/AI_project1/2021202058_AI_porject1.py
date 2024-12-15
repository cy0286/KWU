import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import fetch_lfw_people

# ## LWF(Labed Faces in ther World)

# 각 인물당 최소 얼굴 이미지 수와 크기 설정
people = fetch_lfw_people(min_faces_per_person = 20, resize = 0.7)
# 데이터셋에서 첫 번째 얼굴 이미지의 크기를 확인
images_shape = people.images[0].shape

# LFW 데이터셋에 있는 이미지의 샘플

# 2행 5열의 서브플롯 생성하여 그림 (Matplotlib figure)과 서브플롯 (axes)을 반환
fig, axes = plt.subplots(2, 5, figsize=(15,8),subplot_kw= {'xticks':(),'yticks':()})

# 이미지, 해당 인물의 인덱스, 및 서브플롯을 묶어 반복
for target, image, ax in zip(people.target,people.images, axes.ravel()):
    ax.imshow(image) 
    ax.set_title(people.target_names[target])
    
# 그림 표시
plt.show()


# Data shape

# 데이터셋의 구조와 클래스의 수
print('people.images.shape : {}'.format(people.images.shape))
print('class : {}'.format(len(people.target_names)))


# 각각의 인물에 대한 이미지의 개수

# 배열에서 각 클래스의 등장 횟수를 계산하는 함수
counts = np.bincount(people.target)

for i,(count,name) in enumerate(zip(counts,people.target_names)):
    # 클래스 이름과 해당 클래스의 등장 횟수 출력
    print("{0:25} {1:3}".format(name,count))
    
    # 3번째 인물마다 공백 라인 삽입
    if (i+1) % 3 ==0 :
        print()

# 데이터 편중 막기 위해 20개 데이터 선택
mask = np.zeros(people.target.shape, dtype=np.bool_)
for target in np.unique(people.target):
    mask[np.where(people.target==target)[0][:20]]=1

# 훈련, 테스트 데이터 생성
x_people = people.data[mask]
y_people = people.target[mask]

# 데이터 스케일링을 수행하여 픽셀 값을 0에서 1 사이로 정규화
x_people = x_people/255.


# ## PCA with whitening 

from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split

# 전처리한 데이터를 분할
x_train, x_test, y_train, y_test = train_test_split(x_people, y_people, stratify=y_people, random_state=0)

# PCA를 활용하여 화이트닝을 적용
pca = PCA(n_components=100, whiten=True, random_state=0)
pca.fit(x_train)

# PCA를 사용하여 훈련 데이터 변환
x_train_pca = pca.transform(x_train)

# Scatter plot을 생성
plt.figure(figsize=(8, 6))
plt.scatter(x_train_pca[:, 0], x_train_pca[:, 1], c=y_train, cmap='viridis', s=20)
plt.title('PCA Results')
plt.xlabel('First Principal Component')
plt.ylabel('Second Principal Component')
plt.colorbar(label='Target Class')
plt.show()

# 이미지의 높이와 너비를 설정
h, w = 87, 65

# 고유 얼굴 성분 출력
eigenfaces = pca.components_.reshape(-1, h, w)

# 처음 10개의 고유 얼굴 성분을 출력
num_eigenfaces_to_display = 10
plt.figure(figsize=(12, 6))

for i in range(num_eigenfaces_to_display):
    plt.subplot(2, 5, i + 1)  # 2x5 그리드 형태로 이미지 출력
    plt.imshow(eigenfaces[i])
    plt.title(f'Eigenface {i + 1}')
    plt.axis('off')

plt.show()


# ## KNN

from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
import mglearn

# 전처리한 데이터를 분할
x_train, x_test, y_train, y_test = train_test_split(x_people, y_people, stratify = y_people, random_state = 0)

# 머신러닝 라이브러리 import
knn = KNeighborsClassifier(n_neighbors=1) # 이웃의 수
knn.fit(x_train, y_train) # 모델 학습

print("테스트 정확도 : {:.3f}".format(knn.score(x_test, y_test)))


# ## KNN with PCA  whitening

from sklearn.decomposition import PCA


# PCA whitening 사용

# PCA를 활용하여 화이트닝을 적용
pca = PCA(n_components=100, whiten=True, random_state=0)
pca.fit(x_train)

# PCA를 사용하여 훈련 데이터와 테스트 데이터 변환
x_train_pca = pca.transform(x_train)
x_test_pca = pca.transform(x_test)

# KNN을 k=1로 생성하고 훈련 데이터에 맞춥
knn = KNeighborsClassifier(n_neighbors=1)
knn.fit(x_train_pca, y_train)

print('테스트 정확도: {:.3f}'.format(knn.score(x_test_pca, y_test)))


# PCA whitening 사용 x

# PCA 활용, 화이트닝 적용 x
pca = PCA(n_components=100, whiten=False, random_state=0)
pca.fit(x_train)

# PCA를 사용하여 훈련 데이터와 테스트 데이터 변환
x_train_pca = pca.transform(x_train)
x_test_pca = pca.transform(x_test)

# KNN을 k=1로 생성하고 훈련 데이터에 맞춥
knn = KNeighborsClassifier(n_neighbors=1)
knn.fit(x_train_pca, y_train)

print('테스트 정확도: {:.3f}'.format(knn.score(x_test_pca, y_test)))

print('pca.components_.shape {}'.format(pca.components_.shape))

# 10x10 그리드의 서브플롯을 생성하여 주성분 벡터를 시각화
fig, axes = plt.subplots(10, 10, figsize=(12, 12), subplot_kw={'xticks': (), 'yticks': ()})

# 주성분 벡터(components)를 순회하며 시각화
for i, (comp, ax) in enumerate(zip(pca.components_, axes.ravel())): 
    ax.imshow(comp.reshape(images_shape)) 
    ax.set_title('Eigenface{}'.format(i+1), fontsize = 8)

plt.tight_layout()
plt.show()

# 얼굴 이미지 데이터에 PCA를 적용하고 결과를 시각화
mglearn.plots.plot_pca_faces(x_train, x_test, images_shape)


# ## CNN

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import classification_report
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
from keras.utils import to_categorical

# 데이터 불러오기
people = fetch_lfw_people(min_faces_per_person=20, resize=0.7)

# 이미지 shape 확인
images_shape = people.images[0].shape

# 데이터 준비
X = people.images
y = LabelEncoder().fit_transform(people.target)

# 데이터 분할 (학습 데이터 및 테스트 데이터)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 데이터 전처리: 이미지를 0~1 범위로 스케일링
X_train = X_train / 255.0
X_test = X_test / 255.0

# CNN 모델 구축
model = Sequential()
model.add(Conv2D(32, (3, 3), activation='relu', input_shape=(images_shape[0], images_shape[1], 1)))
model.add(MaxPooling2D((2, 2)))
model.add(Conv2D(64, (3, 3), activation='relu'))
model.add(MaxPooling2D((2, 2)))
model.add(Conv2D(128, (3, 3), activation='relu'))
model.add(MaxPooling2D((2, 2)))
model.add(Flatten())
model.add(Dense(128, activation='relu'))
model.add(Dense(len(people.target_names), activation='softmax'))

# 모델 컴파일
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# 모델 학습
model.fit(X_train.reshape(-1, images_shape[0], images_shape[1], 1), y_train, epochs=100, batch_size=32, validation_split=0.2)

# 모델 평가
test_loss, test_accuracy = model.evaluate(X_test.reshape(-1, images_shape[0], images_shape[1], 1), y_test)
print("테스트 정확도:", test_accuracy)