"use strict";

var Cylon = require('cylon');

Cylon.robot({
    connections: {
        arduino: {adaptor: 'firmata', port: 'COM3'}
    },

    devices: {
        led: {driver: 'led', pin: 8}
    },

    work: function (my) {
        every((1).second(), function () {
            my.led.toggle();
        });
    }
}).start();