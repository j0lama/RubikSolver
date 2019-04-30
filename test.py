import cv2
import sys

def drawSquare(image, pos, l):
	x = pos[0]
	y = pos[1]
	for i in range(l):
		image[x+i][y] = (0,0,0)
		image[x+i][y+l] = (0,0,0)
		image[x][y+i] = (0,0,0)
		image[x+l][y+i] = (0,0,0)
	return image

image = cv2.imread("imagen.jpg")
image = cv2.resize(image, (640, 480))

point = (int(sys.argv[1]), int(sys.argv[2]))

drawSquare(image, point, 20)

cv2.imwrite("test1.jpg", image)
