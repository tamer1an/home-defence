"use strict";

var Cylon = require('cylon');

Cylon.robot({
  connections: {
    arduino: {adaptor: 'firmata', port: 'COM3'}
  },

  devices: {
    ultrasonic: {driver: 'hcsr04', pin: 10, pin2: 11}
  },

  work: function (my) {
    console.log('US work start');

    every((1).seconds(), function () {
        console.log('data', my.ultrasonic.distance());
    });
  }
}).start();