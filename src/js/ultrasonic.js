"use strict";

var Cylon = require('cylon');

Cylon.robot({
  connections: {
    arduino: {adaptor: 'firmata', port: 'COM3'}
  },

  devices: {
    ultrasonic: {driver: 'hcsr04', pin: 8, pin2: 9}
  },

  work: function (my) {

    every(100, function() {

      console.log('distance',my.ultrasonic.distance());

    });
  }
}).start();