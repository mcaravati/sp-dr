eval(require("fs").readFileSync("./spdr.js").toString());

var assert = require("assert")

async function main() {
    describe('Array', function () {
        describe('#indexOf()', function () {
            it('should return -1 when the value is not present', function () {
                assert.equal([1, 2, 3].indexOf(4), -1);
            });
        });
    });
}

Module.onRuntimeInitialized = main;