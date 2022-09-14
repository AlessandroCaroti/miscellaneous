import numpy as np
import cv2 as cv2
from skimage import io, color
import os
from os import listdir
from os.path import isfile, join
import sys
from skimage.color import rgb2hsv, hsv2rgb, rgb2gray
import numpy as np
import cv2 as cv2
from scipy import signal
import matplotlib.pyplot as plt

import time

if __name__ == "__main__":
    img = cv2.imread('./tree.jpg')
    img_c = img.copy()
    gray = rgb2gray(img_c)


    print((gray).shape)
    #print(gray)
    gray = 1 - gray
    
    gray[gray < 0.4] = 0

    cv2.imwrite("tree_2.jpg", gray*256)
    #print(col_list)