"use strict";

var Cylon = require('cylon');

Cylon.robot({
  connections: {
    arduino: {adaptor: 'firmata', port: 'COM3'}
  },

  devices: {
    button: {driver: 'button', pin: 2}
  },

  work: function (my) {
    my.button.on('push', function () {
      console.log("Button pushed!");
    });
  }
}).start();