from picamera import PiCamera
from time import sleep
import sys

camera = PiCamera()

camera.capture(sys.argv[1], resize=(640, 480))

exit()
