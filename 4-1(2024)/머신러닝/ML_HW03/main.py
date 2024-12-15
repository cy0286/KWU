import torch
import torchvision.transforms as transforms
import torchvision.datasets as datasets
from Model import ResNet
from Director import Director

transform = transforms.Compose(
    [transforms.ToTensor(),
     transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
     transforms.Resize([128, 128])]) # Resize the images to 128x128 pixel

full_trainset = datasets.CIFAR10(root='../data', train=True, download=True, transform=transform)
trainset_size = len(full_trainset) // 10 

trainset, _ = torch.utils.data.random_split(full_trainset, [trainset_size, len(full_trainset) - trainset_size])
testset = datasets.CIFAR10(root='../data', train=False, download=True, transform=transform)

train_loader = torch.utils.data.DataLoader(trainset, batch_size=4, shuffle=True)
test_loader = torch.utils.data.DataLoader(testset, batch_size=4, shuffle=False)


model = ResNet()
director = Director(model, optimizer="SGD", learning_rate=0.01,
                    train_loader=train_loader, test_loader=test_loader)


director.run(epochs=10)
director.plot()