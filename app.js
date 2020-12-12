function generateAngleLUT(size) {
    let lut = [];
    for (let index = 0; index < size; index++) {
        lut.push(Math.atan(Math.pow(2, -index)));
    }
    return lut;
}

const iterations = 20;
const angleLut = generateAngleLUT(iterations);

console.log("Generated CORDIC Angle LUT is: ", angleLut);
