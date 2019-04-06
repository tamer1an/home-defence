from RPi import GPIO

import time

pin = 7

GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin,GPIO.IN)

while True:
    if GPIO.input(pin):
        print('Input was HIGH')
    else:
        print('Input was LOW')

    time.sleep(1)
