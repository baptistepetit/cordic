import chai from 'chai';
import { calculateCordicCosine, setupCordicConstants } from '../src/cordic.js'

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
        setupCordicConstants(cordicIterations);

        testAngles.forEach(angle => {
            testTuples.push({
                angle: angle,
                result: calculateCordicCosine(angle).cos,
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
        setupCordicConstants(cordicIterations);

        testAngles.forEach(angle => {
            testTuples.push({
                angle: angle,
                result: calculateCordicCosine(angle).sin,
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
