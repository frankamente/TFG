from __future__ import print_function
from imutils.video import VideoStream
import imutils
#import serial
import time
from skimage.measure import compare_ssim as ssim
import matplotlib.pyplot as plt
import numpy as np
import cv2
import argparse#construct the argument parseand parse the argum

def auto_canny(image, sigma=0.33):
  # compute the median of the single channel pixel intensities
  v = np.median(image)
 
  # apply automatic Canny edge detection using the computed median
  lower = int(max(0, (1.0 - sigma) * v))
  upper = int(min(255, (1.0 + sigma) * v))
  edged = cv2.Canny(image, lower, upper)
 
  # return the edged image
  return edged

def mse(imageA, imageB):
  # the 'Mean Squared Error' between the two images is the
  # sum of the squared difference between the two images;
  # NOTE: the two images must have the same dimension
  err = np.sum((imageA.astype("float") - imageB.astype("float")) ** 2)
  err /= float(imageA.shape[0] * imageA.shape[1])
  
  # return the MSE, the lower the error, the more "similar"
  # the two images are
  return err
 
def compare_images(imageA, imageB, title):
  # compute the mean squared error and structural similarity
  # index for the images
  m = mse(imageA, imageB)
  s = ssim(imageA, imageB)
  
  # setup the figure
  fig = plt.figure(title)
  plt.suptitle("MSE: %.2f, SSIM: %.2f" % (m, s))
 
  # show first image
  ax = fig.add_subplot(1, 2, 1)
  plt.imshow(imageA, cmap = plt.cm.gray)
  plt.axis("off")
 
  # show the second image
  ax = fig.add_subplot(1, 2, 2)
  plt.imshow(imageB, cmap = plt.cm.gray)
  plt.axis("off")
 
  # show the images
  plt.show()

inicial=cv2.imread("prueba.jpg")
#inicial = imutils.resize(inicial, width=500)
gris = cv2.cvtColor(inicial, cv2.COLOR_BGR2GRAY)

blur = cv2.GaussianBlur(inicial, (9, 9), 0)
blur2 = cv2.GaussianBlur(gris, (9, 9), 0)

canny = auto_canny(inicial)
canny1 = auto_canny(gris)
canny2 = auto_canny(blur)
canny3 = auto_canny(blur2)




while True:

  cv2.imshow("Original", inicial)
  cv2.imshow("Gris", gris)
  cv2.imshow("Desenfoque color", blur)
  cv2.imshow("Desenfoque gris", blur2)
  cv2.imshow("Contorno sin desenfoque color", canny)
  cv2.imshow("Contorno sin desenfoque gris", canny1)
  cv2.imshow("Contorno con desenfoque color", canny2)
  cv2.imshow("Contorno con desenfoque gris", canny3)
  






  
  key = cv2.waitKey(1) & 0xFF
  if key == ord("q"):
  
    break
 
# do a bit of cleanup
cv2.destroyAllWindows()