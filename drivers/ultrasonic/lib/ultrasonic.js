"use strict";

var Cylon = require("cylon");

var Ultrasonic = module.exports = function Ultrasonic(opts) {
  Ultrasonic.__super__.constructor.apply(this, arguments);
  opts = opts || {};

  // Include a list of commands that will be made available to external APIs.
  this.commands = {
    // This is how you register a command function for the API;
    // the command should be added to the prototype, see below.
    hello: this.hello
  };
};

Cylon.Utils.subclass(Ultrasonic, Cylon.Driver);

Ultrasonic.prototype.start = function(callback) {
  callback();
};

Ultrasonic.prototype.halt = function(callback) {
  callback();
};

Ultrasonic.prototype.hello = function() {
  Cylon.Logger.info("Hello World!");
};
