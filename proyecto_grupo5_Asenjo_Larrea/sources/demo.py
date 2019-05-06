#!/usr/bin/python

import cv2
import numpy as np
import sys, math
from rubik_solver import utils
import time
import serial
import os

#Valores extraidos de las fotos de prueba

rojo = [33, 18, 159]
azul = [72, 25, 16]
verde = [20, 156, 68]
amarillo = [0, 197, 198]
naranja = [59, 50, 213]
blanco = [152, 170, 180]

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



points = [(180, 262), (180, 302), (180, 342), (235, 262), (235, 302), (235, 342), (290, 262), (290, 302), (290, 342)]
lado = 20

cara_r = ""
cara_b = ""
cara_g = ""
cara_y = ""
cara_o = ""
cara_w = ""
ack = ''

print('Inicio del programa')

# Conectar con Arduino
arduino = serial.Serial('/dev/ttyACM0', 9600)

# Esperar a un enter
raw_input('Pulsa cualquier tecla...')

# Tomar fotos de las diferentes caras
arduino.write('DETECTAR')
for i in range(1,7):
	ack = arduino.readline()
	print('ACK: ' + ack)
	os.system('python takePhoto.py cara' + str(i) + '.jpg')
	arduino.write('NEXT')


for j in range(1, 7):
	image = cv2.imread("cara" + str(j) + ".jpg")
	image = cv2.resize(image, (640, 480))
	i = 1
	cara = ""
	pieza = ""
	print('\ncara' + str(j))
	for p in points:
		print(getMedia(image, p, lado))
		pieza = getColor(getMedia(image, p, lado))
		cara = cara + pieza
		if i == 5:
			color = pieza
		i = i+1
	if color == "r":
		cara_r = cara[::-1]
		print('Comprobacion de que la cara es correcta:')
                print(cara_r)
                entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
                if(entrada != ''):
                        cara_r = entrada
	elif color == "b":
		cara_b = cara[6] + cara[3] + cara[0] + cara[7] + cara[4] + cara[1] + cara[8] + cara[5] + cara[2]
		print('Comprobacion de que la cara es correcta:')
                print(cara_b)
                entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
                if(entrada != ''):
                        cara_b = entrada
	elif color == "g":
		cara_g = cara[2] + cara[5] + cara[8] + cara[1] + cara[4] + cara[7] + cara[0] + cara[5] + cara[6]
		print('Comprobacion de que la cara es correcta:')
                print(cara_g)
                entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
                if(entrada != ''):
                        cara_g = entrada
	elif color == "y":
		cara_y = cara[::-1]
		print('Comprobacion de que la cara es correcta:')
                print(cara_y)
                entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
                if(entrada != ''):
                        cara_y = entrada
	elif color == "o":
		cara_o = cara
		print('Comprobacion de que la cara es correcta:')
                print(cara_o)
                entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
                if(entrada != ''):
                        cara_o = entrada
	elif color == "w":
		cara_w = cara[::-1]
		print('Comprobacion de que la cara es correcta:')
        	print(cara_w)
        	entrada = raw_input('Introduce la secuencia de colores correcta o pulsa enter...')
        	if(entrada != ''):
                	cara_w = entrada

cube = cara_y + cara_b + cara_r + cara_g + cara_o + cara_w

print(cube)

movements = utils.solve(cube, 'Kociemba')

print(movements)

ack = arduino.readline()
print('ACK: ' + ack)

print('COMENZANDO A RESOLVER EL CUBO...')

for mov in movements:
	print(str(mov))
	arduino.write(str(mov))
	ack = arduino.readline()
	print(ack)

arduino.write('E')
print('CUBO RESUELTO HDP')
