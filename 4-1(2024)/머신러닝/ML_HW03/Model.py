import torch
import torch.nn as nn

class ResNetBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1):
        super(ResNetBlock, self).__init__()
        # First convolutional layer
        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU() # ReLU activation
         # Second convolutional layer
        self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(out_channels)

        # Downsample layer for matching dimensions
        self.downsample = nn.Sequential()
        if stride != 1 or in_channels != out_channels:
            self.downsample = nn.Sequential(nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                                            nn.BatchNorm2d(out_channels),)
        
    def forward(self, x):
        identity = x  # Save the input tensor
        
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        out = self.conv2(out)
        out = self.bn2(out)

        # Adjust input dimensions if needed
        if self.downsample is not None:
            identity = self.downsample(identity)
           
        out += identity # skip connection
        out = self.relu(out)
        return out

class ResNet(nn.Module):
    def __init__(self, out_class=10):
        super(ResNet, self).__init__()
        self.in_channels = 64
        # Initial convolutional layer
        self.conv1 = nn.Conv2d(3, 64, kernel_size=7, stride=2, padding=3, bias=False)
        self.bn1 = nn.BatchNorm2d(64)
        self.relu = nn.ReLU()

        # Max pooling layer
        self.maxpool = nn.MaxPool2d(kernel_size=3, stride=2, padding=1)

        # ResNet blocks for each layer
        self.layer1_block1 = ResNetBlock(64, 64)
        self.layer1_block2 = ResNetBlock(64, 64)
        self.layer1_block3 = ResNetBlock(64, 64)
        
        self.layer2_block1 = ResNetBlock(64, 128, stride=2)
        self.layer2_block2 = ResNetBlock(128, 128)
        self.layer2_block3 = ResNetBlock(128, 128)
        self.layer2_block4 = ResNetBlock(128, 128)
        
        self.layer3_block1 = ResNetBlock(128, 256, stride=2)
        self.layer3_block2 = ResNetBlock(256, 256)
        self.layer3_block3 = ResNetBlock(256, 256)
        self.layer3_block4 = ResNetBlock(256, 256)
        self.layer3_block5 = ResNetBlock(256, 256)
        self.layer3_block6 = ResNetBlock(256, 256)
        
        self.layer4_block1 = ResNetBlock(256, 512, stride=2)
        self.layer4_block2 = ResNetBlock(512, 512)
        self.layer4_block3 = ResNetBlock(512, 512)
        self.avgpool = nn.AdaptiveAvgPool2d((1, 1)) # Adaptive average pooling
        self.fc = nn.Linear(512, out_class) # Fully connected layer

    def forward(self, x):
        x = self.conv1(x)
        x = self.bn1(x)
        x = self.relu(x)
        x = self.maxpool(x)

        x = self.layer1_block1(x)
        x = self.layer1_block2(x)
        x = self.layer1_block3(x)
        
        x = self.layer2_block1(x)
        x = self.layer2_block2(x)
        x = self.layer2_block3(x)
        x = self.layer2_block4(x)
        
        x = self.layer3_block1(x)
        x = self.layer3_block2(x)
        x = self.layer3_block3(x)
        x = self.layer3_block4(x)
        x = self.layer3_block5(x)
        x = self.layer3_block6(x)
        
        x = self.layer4_block1(x)
        x = self.layer4_block2(x)
        x = self.layer4_block3(x)

        x = self.avgpool(x)
        x = torch.flatten(x, 1) # Flatten the tensor
        x = self.fc(x)
        return x