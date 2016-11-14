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

inicial1=cv2.imread("arrowL.jpg")
gris1 = cv2.cvtColor(inicial1, cv2.COLOR_BGR2GRAY)
blur1 = cv2.GaussianBlur(gris1, (9, 9), 0)
canny1 = auto_canny(blur1)

inicial2=cv2.imread("arrowR.jpg")
gris2 = cv2.cvtColor(inicial2, cv2.COLOR_BGR2GRAY)
blur2 = cv2.GaussianBlur(gris2, (9, 9), 0)
canny2 = auto_canny(blur2)

inicial3=cv2.imread("arrowStop.jpg")
gris3 = cv2.cvtColor(inicial3, cv2.COLOR_BGR2GRAY)
blur3 = cv2.GaussianBlur(gris3, (9, 9), 0)
canny3 = auto_canny(blur3)


while True:

  cv2.imshow("Inicial Izquierda", inicial1)
  cv2.imshow("Inicial Derecha", inicial2)
  cv2.imshow("Inicial Stop", inicial3)
  cv2.imshow("Gris Izquierda", gris1)
  cv2.imshow("Gris Derecha", gris2)
  cv2.imshow("Gris Stop", gris3)
  cv2.imshow("Blur Izquierda", blur1)
  cv2.imshow("Blur Derecha", blur2)
  cv2.imshow("Blur Stop", blur3)
  cv2.imshow("Canny Izquierda", canny1)
  cv2.imshow("Canny Derecha", canny2)
  cv2.imshow("Canny Stop", canny3)
  
  key = cv2.waitKey(1) & 0xFF
  if key == ord("q"):
  
    break
 
# do a bit of cleanup
cv2.destroyAllWindows()