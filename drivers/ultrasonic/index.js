"use strict";

var Driver = require("./lib/ultrasonic");

module.exports = {
  // Drivers your module provides, e.g. ["ultrasonic", "button"]
  drivers: [],

  // Modules intended to be used with yours, e.g. ["cylon-gpio"]
  dependencies: [],


  driver: function (opts) {
    return new Driver(opts);
  }
};
