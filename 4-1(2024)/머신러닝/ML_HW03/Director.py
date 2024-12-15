import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

class Director:
    def __init__(self, model, optimizer, learning_rate, train_loader, test_loader):
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.model = model.to(self.device) # GPU or CPU
        
        # Set optimizer
        self.optimizer = self.set_optimizer(optimizer, learning_rate)
        self.train_loader = train_loader
        self.test_loader = test_loader
        self.criterion = nn.CrossEntropyLoss() # Loss function

        self.train_accuracies = [] # List to store train accuracies
        self.test_accuracies = [] # List to store test accuracies

    def set_optimizer(self, optimizer, learning_rate):
        # Initialize optimizer
        if optimizer == "SGD":
            return optim.SGD(self.model.parameters(), lr=learning_rate, momentum=0.9)
        elif optimizer == "Adam":
            return optim.Adam(self.model.parameters(), lr=learning_rate)
        else:
            raise ValueError("Invalid optimizer")

    def train(self):
        self.model.train() # Set the model to training mode
        correct = 0
        total = 0
    
        for i, data in enumerate(self.train_loader):
            inputs, labels = data[0].to(self.device), data[1].to(self.device)
            self.optimizer.zero_grad() # Zero the parameter gradients
            outputs = self.model(inputs) # Output the model prediction results
            loss = self.criterion(outputs, labels) # Loss calculation
            loss.backward() # Gradients calculation
            self.optimizer.step() # Update parameter

            with torch.no_grad():
                _, predicted = torch.max(outputs.data, 1) # Get the predicted class
                total += labels.size(0) # Update total number of labels
                correct += (predicted == labels).sum().item() # Update number of correct predictions
        
        train_accuracy = 100 * correct / total # Calculate training accuracy
        print(f'Train Accuracy: {train_accuracy} %')
        self.train_accuracies.append(train_accuracy) # Store training accuracy
            

    def test(self):
        self.model.eval() # Set the model to test mode
        correct = 0
        total = 0
        with torch.no_grad():
            for data in self.test_loader:
                images, labels = data[0].to(self.device), data[1].to(self.device)
                outputs = self.model(images) # Output the model prediction results
                _, predicted = torch.max(outputs.data, 1) # Get the predicted class
                total += labels.size(0) # Update total number of labels
                correct += (predicted == labels).sum().item() # Update number of correct predictions
        
        test_accuracy = 100 * correct / total # Calculate test accuracy
        print(f'Test Accuracy: {test_accuracy} %')
        self.test_accuracies.append(test_accuracy) # Store test accuracy
    
    def plot(self):
        # Plot training and testing accuracies
        epochs = range(1, len(self.train_accuracies) + 1) # X-axis values
        plt.plot(epochs, self.train_accuracies, label='Train Accuracy')
        plt.plot(epochs, self.test_accuracies, label='Test Accuracy')
        plt.xlabel('Epoch')
        plt.ylabel('Accuracy')
        plt.title('2021202058_SCY')
        plt.legend()
        plt.show()
        

    def run(self, epochs):
        # Run training and testing for a number of epochs
        for epoch in range(epochs):
            print(f'Epoch {epoch + 1}/{epochs}')
            self.train()
            self.test()