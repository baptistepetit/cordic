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

function calculateCordicRotation(cordicParams, cordicAngles) {
    let x_i = cordicParams.x_zero;
    let y_i = cordicParams.y_zero;
    let z_i = cordicParams.angle;

    for (let i = 0; i < cordicAngles.length; i++) {
        let sign_i = z_i < 0 ? -1 : 1;

        let x_i_next = x_i - sign_i * y_i * Math.pow(2, -i);
        let y_i_next = y_i + sign_i * x_i * Math.pow(2, -i);
        let z_i_next = z_i - sign_i * cordicAngles[i];

        x_i = x_i_next;
        y_i = y_i_next;
        z_i = z_i_next;
    }

    return {x_n: x_i, y_n: y_i};
}

const iterations = 20;
const angleLut = generateAngleLUT(iterations);
const gain = calculateGainFromAngleLUT(angleLut);
const params = {x_zero: gain, y_zero: 0, angle: Math.PI / 4};
const result = calculateCordicRotation(params, angleLut);

console.log("Generated CORDIC Angle LUT is: ", angleLut);
console.log("CORDIC Gain is: ", gain);
console.log(
    "Coordinates rotated through CORDIC algorithm: ",
    result
);
console.log(
    "Maths functions result: ",
    {x_n: Math.cos(Math.PI / 4), y_n: Math.sin(Math.PI / 4)}
)
