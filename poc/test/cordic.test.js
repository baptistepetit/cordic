import chai from 'chai';
import { calculateCordicCosine } from '../src/cordic.js'

const expect = chai.expect;

describe('Cordic', function() {
    const errorMax = 0.01;
    const cordicIterations = 20;
    const testNumber = 5;

    let testAngles = [];
    for (let i = 0; i < testNumber; i++) {
        testAngles.push(i * 2 * Math.PI / testNumber);
    }

    describe('Cos', function() {
        let testTuples = [];

        testAngles.forEach(angle => {
            testTuples.push({
                angle: angle,
                result: calculateCordicCosine(angle, cordicIterations).cos,
                expected: Math.cos(angle)
            });
        });

        testTuples.forEach(testTuple => {
            it('should be close to Math.cos at ' + testTuple.angle + ' (rad)',
                function() {
                    expect(testTuple.result).closeTo(testTuple.expected, errorMax);
                }
            );
        });
    });

    describe('Sin', function() {
        let testTuples = [];

        testAngles.forEach(angle => {
            testTuples.push({
                angle: angle,
                result: calculateCordicCosine(angle, cordicIterations).sin,
                expected: Math.sin(angle)
            });
        });

        testTuples.forEach(testTuple => {
            it('should be close to Math.sin at ' + testTuple.angle + ' (rad)',
                function() {
                    expect(testTuple.result).closeTo(testTuple.expected, errorMax);
                }
            );
        });
    });
});
