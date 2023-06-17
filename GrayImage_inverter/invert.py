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
    img_path  = './tree.jpg'
    if not os.path.exists(img_path):
        raise FileNotFoundError(f"file {img_path} not exist")
    img = cv2.imread(img_path)
    img_c = img.copy()
    gray = rgb2gray(img_c)


    print((gray).shape)
    #print(gray)
    gray = 1 - gray
    
    gray[gray < 0.4] = 0

    filename, extension = os.path.splitext(img_path)
    cv2.imwrite(f"{filename}_inverted{extension}", gray*256)
    #print(col_list)