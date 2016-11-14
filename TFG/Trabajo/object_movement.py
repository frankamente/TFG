from __future__ import print_function
from imutils.video import VideoStream
import imutils
#import serial
import time

import numpy as np
import cv2
import argparse#construct the argument parseand parse the argum



print("[INFO] waiting for camera to warmup...")
vs = VideoStream(0).start()
time.sleep(2.0)
# define the lower and upper boundaries of the "orange"
# ball in the HSV color space
orangeLower = (4, 190, 75)
orangeUpper = (41, 255, 255)




# loop over the frames from the video stream
while True:
	# grab the next frame from the video stream, resize the
	# frame, and convert it to the HSV color space
	frame = vs.read()
	frame = imutils.resize(frame, width=500)
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

# construct a mask for the color "orange", then perform
	# a series of dilations and erosions to remove any small
	# blobs left in the mask
	mask = cv2.inRange(hsv, orangeLower, orangeUpper)
	mask1 = cv2.erode(mask, None, iterations=2)
	mask2 = cv2.dilate(mask1, None, iterations=2)

	# find contours in the mask and initialize the current
	# (x, y) center of the ball
	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
	cv2.CHAIN_APPROX_SIMPLE)
	cnts = cnts[0] if imutils.is_cv2() else cnts[1]
	center = None
    # only proceed if at least one contour was found
	if len(cnts) > 0:
    # find the largest contour in the mask, then use
    # it to compute the minimum enclosing circle and
    # centroid
	    c = max(cnts, key=cv2.contourArea)
	    ((x, y), radius) = cv2.minEnclosingCircle(c)
	    M = cv2.moments(c)
	    if M["m00"] != 0:
	    	cX = int(M["m10"] / M["m00"])
	    	cY = int(M["m01"] / M["m00"])
	    else:
	    	cX, cY, = 0, 0
	    center = cX, cY
	    # only proceed if the radius meets a minimum size
	    if radius > 7:
			# draw the circle and centroid on the frame
			cv2.circle(frame, (int(x), int(y)), int(radius),
			(0, 255, 255), 2)
			cv2.circle(frame, center, 5, (0, 0, 255), -1)

			print("Funciona")
	    else:
	    	print("NO")
	# show the frame to our screen
	cv2.imshow("Frame", frame)
	cv2.imshow("MASK", mask)
	key = cv2.waitKey(1) & 0xFF
 
	# if the 'q' key is pressed, stop the loop
	if key == ord("q"):
		break
 
# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()