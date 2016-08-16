import smtplib
from email.utils import formatdate
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEImage import MIMEImage

body = 'INTRUDER ALERT!'

msg = MIMEMultipart()   
msg['Date'] = formatdate(localtime = True)
msg['Subject'] = body

fromaddr = '......@gmail.com'
toaddrs  = '......@gmail.com'
username = '......@gmail.com'
password = '......'
server = smtplib.SMTP('smtp.gmail.com:587')

content = MIMEText(body, 'plain')
msg.attach(content)
msg.attach(MIMEImage(file("image.jpg").read()))
    
server.starttls()
server.login(username,password)
server.sendmail(fromaddr, toaddrs, msg.as_string())
server.quit() 

#server.close()        