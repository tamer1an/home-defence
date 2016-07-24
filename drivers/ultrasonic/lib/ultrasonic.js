"use strict";

var Cylon = require("cylon");

var events = [
  /**
   * Emitted when the has detected the current range
   *
   * @event range
   * @value distance the current distance in inches
   */
  "range",

  /**
   * Emitted when the has detected the current range
   *
   * @event rangeCm
   * @value distance the current distance in centimeters
   */
  "rangeCm"
];

var UltraSonic = module.exports = function UltraSonic(opts) {
  UltraSonic.__super__.constructor.apply(this, arguments);
  opts = opts || {};

  if (this.pin == null) {
    throw new Error("No pin specified for Maxbotix. Cannot proceed");
  }

  // Include a list of commands that will be made available to external APIs.
  this.commands = {
    range: this.range,
    rangeCm: this.rangeCm,
    hello: this.hello
  };

  this.events = events;
};

Cylon.Utils.subclass(UltraSonic, Cylon.Driver);

UltraSonic.prototype.start = function (callback) {
  Cylon.Logger.debug("US on pin " + this.pin + " started");

  // this.connection.analogRead(this.pin, function(err, readVal) {
  //   if (err) { return; }
  //   this.analogValue = readVal;
  //   this.emit("range", this.range());
  //   this.emit("rangeCm", this.rangeCm());
  // }.bind(this));

  callback();
};

UltraSonic.prototype.halt = function (callback) {
  callback();
};
UltraSonic.prototype.hello = function () {
  Cylon.Logger.info("Hello World!");
};
UltraSonic.prototype.range = function (callback) {
  // var models = ["lv", "xl", "xl-long", "hr", "hr-long"],
  //     distance = this.rangeCm();
  //
  // if (models.indexOf(this.model) > -1) {
  //   distance = distance * 0.3937;
  // }
  //
  // if (typeof callback === "function") {
  //   callback(null, distance);
  // }

  return "distance";
};
UltraSonic.prototype.rangeCm = function (callback) {
  // var distance;
  //
  // switch (this.model) {
  //   case "lv":
  //     distance = (this.analogValue / 2.0) / 0.3937;
  //     break;
  //   case "xl-long":
  //     distance = this.analogValue * 2.0;
  //     break;
  //   case "hr":
  //     distance = this.analogValue * 0.5;
  //     break;
  //   case "xl":
  //   case "hr-long":
  //     distance = this.analogValue;
  //     break;
  //   default:
  //     distance = this.analogValue; // raw data, in case of unknown model
  // }
  //
  // if (typeof callback === "function") {
  //   callback(null, distance);
  // }

  return "distance";
};