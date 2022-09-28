# -*- coding: utf-8 -*-

from google.colab import drive
drive.mount('/content/drive')

from __future__ import print_function, division
import torch
from torch import nn
import torch.nn.functional as F
import torch.optim as optim
import torch.nn as nn
import torch.optim as optim
from torch.optim import lr_scheduler
import numpy as np
import torchvision
from torchvision import datasets, models, transforms
import matplotlib.pyplot as plt
import time
import os
import copy
import math
#from create_dataset import *
#from load_dataset_multi import *
from torch.autograd import Variable

import os
import glob
import random
import torch
import numpy as np
from torch.utils.data import Dataset
from PIL import Image
import torchvision.transforms as transforms
import torchvision.transforms.functional as TF

class ImageDataset(Dataset):
	def __init__(self, root, mode="train"):
		if mode == "train":
			self.path_1 = os.path.join(root, "train/depths")
			self.list_depth = [os.path.join("/content/drive/My Drive/Colab Notebooks/distillation/data/train/depths", s) for s in os.listdir(self.path_1)]

			self.list_image = [w.replace('depths', 'images') for w in self.list_depth]
			self.list_image = [w.replace('_depth', '_image') for w in self.list_image]
			# self.list_image = [w.replace('png', 'tif') for w in self.list_image]
			self.list_label= [w.replace('depths', 'labels') for w in self.list_depth]
			self.list_label = [w.replace('_depth', '_label') for w in self.list_label]
			self.list_normal= [w.replace('depths', 'normals') for w in self.list_depth]
			self.list_normal = [w.replace('_depth', '_normal') for w in self.list_normal]
			# self.list_label = [w.replace('png', 'tif') for w in self.list_label]
		else:
			self.path_1 = os.path.join(root, "val/depths")
			self.list_depth = [os.path.join("/content/drive/My Drive/Colab Notebooks/distillation/data/val/depths", s) for s in os.listdir(self.path_1)]
			self.list_image = [w.replace('depths', 'images') for w in self.list_depth]
			self.list_image = [w.replace('_depth', '_image') for w in self.list_image]
			# self.list_image = [w.replace('png', 'tif') for w in self.list_image]
			self.list_label= [w.replace('depths', 'labels') for w in self.list_depth]
			self.list_label = [w.replace('_depth', '_label') for w in self.list_label]
			self.list_normal= [w.replace('depths', 'normals') for w in self.list_depth]
			self.list_normal = [w.replace('_depth', '_normal') for w in self.list_normal]
			# self.list_label = [w.replace('png', 'tif') for w in self.list_label]
		
		self.merged_list = list(zip(self.list_image, self.list_label, self.list_depth, self.list_normal))

		
		return image_B.type(torch.FloatTensor),image_A.type(torch.FloatTensor), image_C.type(torch.FloatTensor), image_D.type(torch.FloatTensor)

	def __len__(self):
		return len(self.merged_list)


train_set = ImageDataset(root="/content/drive/My Drive/Colab Notebooks/distillation/data", mode = 'train')
val_set = ImageDataset(root="/content/drive/My Drive/Colab Notebooks/distillation/data", mode = 'val')

batch_size, c = (2,0)
train_loader = torch.utils.data.DataLoader(dataset=train_set, batch_size=batch_size, shuffle=True)
val_loader = torch.utils.data.DataLoader(dataset=val_set, batch_size=batch_size, shuffle=False)

if __name__ == "__main__":

	train_len = len(train_loader)
	val_len = len(val_loader)
	print("number of tuples in training set is: ", train_len)
	print("number of tuples in validation set is: ", val_len)

	model = UNet(3,13,1).cuda(c)
	if torch.cuda.device_count() > 1:
		print("Let's use", torch.cuda.device_count(), "GPUs!")
		# dim = 0 [30, xxx] -> [10, ...], [10, ...], [10, ...] on 3 GPUs
		model = nn.DataParallel(model)
	#model = nn.DataParallel(UNet(3,6,1))
	model.cuda()

	#KL_loss = torch.tensor([0])
	opt = optim.Adam(model.parameters(), lr=1e-4) #optimizer 1
	#print(model.parameters)

	scheduler = optim.lr_scheduler.MultiStepLR(opt, [100, 150,200], gamma=0.5)
	total_epoch = 100


	learn_rate = 0.001

	for epoch in range(total_epoch):
		print("\nepoch number: ", epoch)

		model.train()
		
		iter_train_loader = iter(train_loader)
		for k in range(train_len):
			image, depth, label, normal = next(iter_train_loader)
			#image, depth, label = next(iter_train_loader)
			train_image = Variable(image).cuda(c)
			train_depth = Variable(depth).cuda(c)
			train_label = Variable(label.type(torch.LongTensor)).cuda(c)
			train_normal = Variable(normal).cuda(c)

			output1, output2, output3,bottleneck2, bottleneck1 = model(train_image)
			
			opt.zero_grad()
			
			train_loss = #calculate the loss
			opt_kl.zero_grad()
	 

			train_loss.backward()
	 
			opt.step()
	 
		t = time.time()
		scheduler.step()
		model.eval()
		with torch.no_grad():
			iter_test_loader = iter(val_loader)
			for k in range(val_len):
				test_image, test_depth, test_label, normal_test = next(iter_test_loader)
				x = Variable(test_image).cuda(c)
				y_1 = Variable(test_depth).cuda(c)
				cuda_test_label = Variable(test_label.type(torch.LongTensor)).cuda(c)
				test_normal = Variable(normal_test).cuda(c)
			
				pred1, pred2, pred3, latent1, latent2 = model(x)

				#compute the metrics
			torch.save(model, "/content/drive/My Drive/Colab Notebooks/distillation/new/three_tasks_model.pkl")