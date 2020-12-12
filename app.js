function generateAngleLUT(size) {
    let lut = [];
    for (let index = 0; index < size; index++) {
        lut.push(Math.atan(Math.pow(2, -index)));
    }
    return lut;
}

function calculateGainFromAngleLUT(lut) {
    let gain = 1;
    lut.forEach(element => {
        gain = gain * Math.cos(element);
    });
    return gain;
}

const iterations = 20;
const angleLut = generateAngleLUT(iterations);
const gain = calculateGainFromAngleLUT(angleLut);

console.log("Generated CORDIC Angle LUT is: ", angleLut);
console.log("CORDIC Gain is: ", gain);
