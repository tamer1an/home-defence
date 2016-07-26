"use strict";

var Drivers = {
  "ultrasonic": require("./lib/ultrasonic")
};

module.exports = {
  drivers: Object.keys(Drivers),

  driver: function(opts) {
    if (Drivers[opts.driver]) {
      return new Drivers[opts.driver](opts);
    }

    return null;
  }
};
