"use strict";

var Cylon = require('cylon');

Cylon.robot({
    connections: {
        arduino: {adaptor: 'firmata', port: 'COM3'}
    },

    devices: {
        maxbotix: {driver: 'maxbotix', pin: 11}
    },

    work: function (my) {
        every((1).seconds(), function () {
            my.maxbotix.range(function (data) {
                console.log("range: " + data);
            });
        });
    }
}).start();