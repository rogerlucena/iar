import numpy as np
import torchvision.transforms as transforms
import torchvision.datasets as dset
import torchvision.utils as vutils
from PIL import ImageFile
import torch

ImageFile.LOAD_TRUNCATED_IMAGES = True


class Data:
    def __init__(self, dataset_train, dataset_train_original, dataloader_train,
                 dataset_test, dataset_test_original, dataloader_test,
                 batch_size_train, batch_size_test):
        self.train = dataset_train
        self.train_original = dataset_train_original
        self.loader_train = dataloader_train
        self.num_train_samples = len(dataset_train)
        self.test = dataset_test
        self.test_original = dataset_test_original
        self.loader_test = dataloader_test
        self.num_test_samples = len(dataset_test)
        self.batch_size_train = batch_size_train
        self.batch_size_test = batch_size_test


def loadImgs(des_dir="./data/", img_size=100, batch_size_train=40, batch_size_test=100):

    dataset_train = dset.ImageFolder(root=des_dir + "train/",
                               transform=transforms.Compose([
                                   transforms.Resize(img_size),
                                   transforms.RandomCrop(75, padding=4),
                                   transforms.RandomHorizontalFlip(),
                                   transforms.ToTensor(),
                                   transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
                               ]))

    dataset_train_original = dset.ImageFolder(root=des_dir + "train/",
                               transform=transforms.Compose([
                                   transforms.Resize(img_size),
                                   transforms.ToTensor(),
                               ]))

    dataset_test = dset.ImageFolder(root=des_dir + "test/",
                               transform=transforms.Compose([
                                   transforms.Resize(img_size),
                                   transforms.RandomCrop(75, padding=4),
                                   transforms.RandomHorizontalFlip(),
                                   transforms.ToTensor(),
                                   transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
                               ]))

    dataset_test_original = dset.ImageFolder(root=des_dir + "test/",
                               transform=transforms.Compose([
                                   transforms.Resize(img_size),
                                   transforms.ToTensor(),
                               ]))

    dataloader_train = torch.utils.data.DataLoader(dataset_train, batch_size=batch_size_train, shuffle=True)

    dataloader_test = torch.utils.data.DataLoader(dataset_test, batch_size=batch_size_test, shuffle=True)

    data = Data(dataset_train, dataset_train_original, dataloader_train,
                dataset_test, dataset_test_original, dataloader_test,
                batch_size_train, batch_size_test)
    return data
