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

template1=cv2.imread("arrowL.jpg")
template1 = cv2.cvtColor(template1, cv2.COLOR_BGR2GRAY)
template1 = cv2.GaussianBlur(template1, (9, 9), 0)
template1 = auto_canny(template1)

giroizq=0
giroder=0
stop=0
i=0

template2=cv2.imread("arrowR.jpg")
template2 = cv2.cvtColor(template2, cv2.COLOR_BGR2GRAY)
template2 = cv2.GaussianBlur(template2, (9, 9), 0)
template2 = auto_canny(template2)

template3=cv2.imread("arrowStop.jpg")
template3 = cv2.cvtColor(template3, cv2.COLOR_BGR2GRAY)
template3 = cv2.GaussianBlur(template3, (9, 9), 0)
template3 = auto_canny(template3)

print("[INFO] waiting for camera to warmup...")
vs = VideoStream(0).start()
time.sleep(2.0)

while True:
	# grab the next frame from the video stream, resize the
	# frame, and convert it to the HSV color space
	frame = cv2.imread("imagen.jpg")
	frame = imutils.resize(frame, width=500)
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	#gaussian = GaussianBlur(greyImg, Size(9, 9), 2, 2);
	blurred = cv2.GaussianBlur(gray, (9, 9), 0)
	#canny = cv2.Canny(blurred, 10, 200)
	canny = auto_canny(blurred)
 
	(_, cnts , _) = cv2.findContours(canny.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:10]
	
	mask = np.ones(frame.shape[:2], dtype="uint8") * 255
	recorte = np.ones(frame.shape[:2], dtype="uint8") * 255
	for c in cnts:
		# approximate the contour
		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.02 * peri, True)
	 
		# if our approximated contour has four points, then
		# we can assume that we have found our screen
		if len(approx) == 4:
			area = cv2.contourArea(c)
			if area > 10000:
				screenCnt = approx
				x,y,w,h = cv2.boundingRect(c)
   				cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
   				recorte=canny[y:y+h,x:x+w ]
				cv2.drawContours(mask, [c], -1, 0, -1)
				#recorte=imutils.resize(recorte, width=271)
				#recorte=imutils.resize(recorte, height=195)
				recorte=cv2.resize(recorte, (271, 195)) 
				m1=mse(recorte,template1)
				s1=ssim(recorte,template1)
				m2=mse(recorte,template2)
				s2=ssim(recorte, template2)
				s3=ssim(recorte, template3)
				#print("\nM1: ")
				#print(m1)
				#print("\nM2: ")
				#print(m2)
				#print("\nS1: ")
				#print(s1)
				#print("\nS2: ")
				#print(s2)
				if (s1) > (s2) and (s1) > (s3):
					giroizq=giroizq+1
					i=i+1
					#print("Giro Izquierda")
				elif s2>s1 and s2>s3:
					giroder=giroder+1
					i=i+1
					#print("Giro Derecha")
				elif (s3) > (s1) and (s3) > (s2):
					stop=stop+1
					i=i+1
				if i==20:
					i=0
					if giroizq > giroder and giroizq > stop:
						print("Giro Izquierda")
						giroizq=0
						giroder=0
						stop=0
					elif giroder > giroizq and giroder > stop:
						print("Giro Derecha")
						giroder=0
						giroizq=0
						stop=0
					elif stop > giroizq and stop > giroder:
						print("Stop")
						giroder=0
						giroizq=0
						stop=0

				break
			M = cv2.moments(c)
			if M["m00"] != 0:
				cX = int(M["m10"] / M["m00"])
				cY = int(M["m01"] / M["m00"])
			else:
				cX, cY, = 0, 0
			center = cX, cY

	# show the frame to our screen
	image = frame.copy()
	cv2.imshow("Frame", frame)
	#cv2.imshow("Gray", gray)
	#cv2.imshow("Blurred", blurred)
	#cv2.imshow("Edges", canny)
	image = cv2.bitwise_and(image, image, mask=mask)
	#cv2.imshow("Mask", mask)
	#cv2.imshow("After", image)
	cv2.imshow("Recorte", recorte)
	cv2.imshow("Giro Izquierda", template1)
	cv2.imshow("Giro Derecha", template2)
	cv2.imshow("Stop", template3)



	key = cv2.waitKey(1) & 0xFF

	# if the 'q' key is pressed, stop the loop
	if key == ord("q"):
		break
 
# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()
