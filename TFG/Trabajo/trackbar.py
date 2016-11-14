import cv2
import numpy as np
from imutils.video import VideoStream
import imutils
#import serial
import time
import argparse#construct the argument parseand parse the argum


def nothing(x):
    pass


vs = VideoStream(0).start()
time.sleep(2.0)

# Create a black image, a window
img = np.zeros((300,512,3), np.uint8)
cv2.namedWindow('image')

# create trackbars for color change
cv2.createTrackbar('R','image',0,255,nothing)
cv2.createTrackbar('G','image',0,255,nothing)
cv2.createTrackbar('B','image',0,255,nothing)
cv2.createTrackbar('R1','image',0,255,nothing)
cv2.createTrackbar('G1','image',0,255,nothing)
cv2.createTrackbar('B1','image',0,255,nothing)

# create switch for ON/OFF functionality
switch = '0 : OFF \n1 : ON'
cv2.createTrackbar(switch, 'image',0,1,nothing)

while(1):
    frame = vs.read()
    frame = imutils.resize(frame, width=500)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    cv2.imshow('image',frame)
    k = cv2.waitKey(1) & 0xFF
    if k == 27:
        break
    
    r = cv2.getTrackbarPos('R','image')
    g = cv2.getTrackbarPos('G','image')
    b = cv2.getTrackbarPos('B','image')
    s = cv2.getTrackbarPos(switch,'image')
    r1 = cv2.getTrackbarPos('R1','image')
    g1 = cv2.getTrackbarPos('G1','image')
    b1 = cv2.getTrackbarPos('B1','image')
    s1 = cv2.getTrackbarPos(switch,'image')
    orangeLower = (r, g, b)
    orangeUpper = (r1, g1, b1)
    mask = cv2.inRange(hsv, orangeLower, orangeUpper)
    cv2.imshow('hola',mask)
cv2.destroyAllWindows()