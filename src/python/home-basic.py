import RPi.GRIO as GPIO
import sys
import wave
import pyaudio
import time

channel = 7
CHUNK = 1024
GPIO.setmode(GPIO.BOARD)
GPIO.setup(channel,GPIO.IN)
p = pyaudio.PyAudio()

while True:
    if GPIO.input(channel)==GPIO.HIGH
        print('INTRUDER ALERT')
        #stream = p .open(format=p.get_format_width(wf.getsamwidth()))
    else:
         print('NO ALERT')
    time.sleep(1)

p.terminate()
GPIO.cleanup()
