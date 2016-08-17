from RPi import GPIO
from picamera import PiCamera

import time

import smtplib
from email.utils import formatdate
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEImage import MIMEImage

fromaddr = '......@gmail.com'
toaddrs  = '......@gmail.com'
username = '......@gmail.com'
password = '......'
server = smtplib.SMTP('smtp.gmail.com:587')

server.starttls()
server.login(username,password)

pin = 7

camera = PiCamera()
camera.rotation = 180

GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin,GPIO.IN)

while True:
    if GPIO.input(pin) == GPIO.HIGH:
        print('INTRUDER ALERT')            
        camera.capture('/home/pi/alarm/image.jpg')    
                
        #prepare email
	msg = MIMEMultipart()
        formatdate(localtime = True)
        body = 'INTRUDER ALERT!'
        msg['Date'] = formatdate(localtime = True)
        msg['Subject'] = body +' '+ formatdate(localtime = True)
        content = MIMEText(body, 'plain')
        msg.attach(content)
        msg.attach(MIMEImage(file("image.jpg").read()))
               
        #send email      
        server.sendmail(fromaddr, toaddrs, msg.as_string())            
        
    else:
        print('NO ALERT')
        
    time.sleep(2)
    
GPIO.cleanup()
server.quit()
