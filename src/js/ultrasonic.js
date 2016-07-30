"use strict";

var Cylon = require('cylon');

Cylon.robot({
  connections: {
    arduino: {adaptor: 'firmata', port: 'COM3'}
  },

  devices: {
    ultrasonic: {driver: 'hcsr04', pin: 11, pin2: 10}
  },

  work: function (my) {
    console.log('US work start');

    // every((1).seconds(), function () {
    //     console.log(my.ultrasonic.distance());
    // });
  }
}).start();