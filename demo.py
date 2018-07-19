#!/usr/bin/python

import cv2
import numpy as np
import sys, math
from rubik_solver import utils

#Valores extraidos de las fotos de prueba

rojo = [68, 45, 200]
azul = [60, 17, 13]
verde = [56, 170, 7]
amarillo = [23, 190, 160]
naranja = [82, 62, 221]
blanco = [182, 182, 182]

def drawSquare(image, pos, l):
	x = pos[0]
	y = pos[1]
	for i in range(l):
		image[x+i][y] = (0,0,0)
		image[x+i][y+l] = (0,0,0)
		image[x][y+i] = (0,0,0)
		image[x+l][y+i] = (0,0,0)
	return image

def getMedia(image, pos, l):
	avg = [0, 0, 0]
	x = pos[0]
	y = pos[1]
	for i in range(1,l-1):
		for j in range(1, l-1):
			#print(image[i+x][j+y])
			avg[0] = avg[0] + image[i+x][j+y][0]
			avg[1] = avg[1] + image[i+x][j+y][1]
			avg[2] = avg[2] + image[i+x][j+y][2]
	div = (l-1)*(l-1)		
	avg[0] = avg[0]/div
	avg[1] = avg[1]/div
	avg[2] = avg[2]/div
	return avg

def getDistance(color, value):
	return math.sqrt((color[0]-value[0])**2 + (color[1]-value[1])**2 + (color[2]-value[2])**2)


def getColor(media):
	colores = {}
	colores['r'] = getDistance(rojo, media)
	colores['b'] = getDistance(azul, media)
	colores['g'] = getDistance(verde, media)
	colores['y'] = getDistance(amarillo, media)
	colores['o'] = getDistance(naranja, media)
	colores['w'] = getDistance(blanco, media)
	return min(colores.items(), key=lambda x: x[1])[0]



points = [(100, 190), (100, 290), (100, 390), (225, 190), (225, 290), (225, 390), (360, 190), (360, 290), (360, 390)]
lado = 30

cara_r = ""
cara_b = ""
cara_g = ""
cara_y = ""
cara_o = ""
cara_w = ""

for j in range(1, 7):
	image = cv2.imread("cara" + str(j) + ".jpg")
	image = cv2.resize(image, (640, 480))
	i = 1
	cara = ""
	pieza = ""
	for p in points:
		pieza = getColor(getMedia(image, p, lado))
		cara = cara + pieza
		if i == 5:
			color = pieza
			print("Cara detectada: " + color)
		i = i+1
	if color == "r":
		cara_r = cara
	elif color == "b":
		cara_b = cara
	elif color == "g":
		cara_g = cara
	elif color == "y":
		cara_y = cara
	elif color == "o":
		cara_o = cara
	elif color == "w":
		cara_w = cara

cube = cara_y + cara_b + cara_r + cara_g + cara_o + cara_w

print(cube)

print(utils.solve(cube, 'Kociemba'))