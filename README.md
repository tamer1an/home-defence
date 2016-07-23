# home-defence
Arduino Cylon.js Home Security Automation

How to Install (https://cylonjs.com/documentation/platforms/arduino/)
To get started, just install the NPM module:

`$ npm install cylon cylon-firmata`
How to Use
This quick example blinks an LED connected to an Arduino once per second:

var Cylon = require('cylon');
```javascript
Cylon.robot({
  connections: {
    arduino: { adaptor: 'firmata', port: '/dev/ttyACM0' }
  },

  devices: {
    led: { driver: 'led', pin: 13 }
  },

  work: function(my) {
    every((1).second(), my.led.toggle);
  }
}).start();
```
How to Connect
Upload the Firmata Firmware to the Arduino
This section assumes you're using an Arduino Uno or another compatible board. If you already have the Firmata sketch installed, you can skip straight to the examples.

OS X
First plug the Arduino into your computer via the USB/serial port. A dialog box will appear telling you that a new network interface has been detected. Click "Network Preferences…", and when it opens, simply click "Apply".

Install the cylon-firmata module:

`$ npm install cylon cylon-firmata`
Once plugged in, use Gort's gort scan serial command to find out your connection info and serial port address:

`$ gort scan serial`
Use the gort arduino install command to install avrdude, this will allow you to upload firmata to the arduino:

`$ gort arduino install`
Once the avrdude uploader is installed we upload the firmata protocol to the arduino, use the arduino serial port address found when you ran gort scan serial:

`$ gort arduino upload firmata /dev/tty.usbmodem1421`
Now you are ready to connect and communicate with the Arduino using serial port connection

Ubuntu
First plug the Arduino into your computer via the USB/serial port.

Install the cylon-firmata module:

`$ npm install cylon cylon-firmata`
Once plugged in, use Gort's gort scan serial command to find out your connection info and serial port address:

`$ gort scan serial`
Use the gort arduino install command to install avrdude, this will allow you to upload firmata to the arduino:

`$ gort arduino install`
Once the avrdude uploader is installed we upload the firmata protocol to the arduino, use the arduino serial port address found when you ran gort scan serial, or leave it blank to use the default address ttyACM0:

`$ gort arduino upload firmata /dev/ttyACM0`
Now you are ready to connect and communicate with the Arduino using serial port connection

Windows
First plug the Arduino into your computer via the USB/serial port.

Install the cylon-firmata module:

`$ npm install cylon cylon-firmata`
Then download and install gort for your OS from the gort.io downloads page and install it.

Open a command prompt window by right clicking on the start button and choose Command Prompt (Admin) (on windows 8.1). Then navigate to the folder where you uncompressed gort (uncomress to a folder first if you haven't done this yet).

Once inside the gort folder, first install avrdude which we'll use to upload firmata to the arduino.

`$ gort arduino install`
When the installation is complete, close the command prompt window and open a new one. We need to do this for the env variables to reload.

`$ gort scan serial`
Take note of your arduinos serialport address (COM1, COM2, COM3 etc). You need to already have installed the arduino drivers from arduino.cc/en/Main/Software. Finally upload the firmata protocol sketch to the arduino.

`$ gort arduino upload firmata <COMX>`
Make sure to substitute <COMX> with the apropiate serialport address.

Now you are ready to connect and communicate with the Arduino using serial port connection.

Using arduino IDE
Open arduino IDE and go to File > Examples > Firmata > StandardFirmata and open it. Select the appriate port for your arduino and click upload. Wait for the upload to finish and you should be ready to start using Gobot with your arduino.
