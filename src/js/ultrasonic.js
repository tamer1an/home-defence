"use strict";

var Cylon = require('cylon');
var ultrasonic = require('ultrasonic');

Cylon.robot({
  connections: {
    arduino: {adaptor: 'firmata', port: 'COM3'}
  },

  devices: {
    ultrasonic: {driver: 'ultrasonic', pin: 11, pin2: 10}
  },

  work: function (my) {

    every((1).seconds(), function () {
      console.log('doing');

    });
  }
}).start();