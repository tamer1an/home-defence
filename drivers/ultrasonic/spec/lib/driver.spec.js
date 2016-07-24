"use strict";

var Cylon = require("cylon");

var Driver = lib("driver");

describe("UltraSonic", function () {
  var driver = new Driver({
    connection: {}
  });

  it("is a Cylon driver", function () {
    expect(driver).to.be.an.instanceOf(Cylon.Driver);
  });

  it("needs tests");
});
