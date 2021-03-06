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

function preRotateIntoRange(cordicParams) {
    let rotatedParams;

    if (cordicParams.angle >= 0 && cordicParams.angle <= Math.PI/4) {
        rotatedParams = cordicParams;
    } else if (cordicParams.angle >= Math.PI/4 && cordicParams.angle <= 3*Math.PI/4) {
        rotatedParams = {
            x_zero: -cordicParams.y_zero,
            y_zero: cordicParams.x_zero,
            angle: cordicParams.angle - Math.PI/2
        }
    } else if (cordicParams.angle >= 3*Math.PI/4 && cordicParams.angle <= 5*Math.PI/4) {
        rotatedParams = {
            x_zero: -cordicParams.x_zero,
            y_zero: -cordicParams.y_zero,
            angle: cordicParams.angle - Math.PI
        }
    } else if (cordicParams.angle >= 5*Math.PI/4 && cordicParams.angle <= 7*Math.PI/4) {
        rotatedParams = {
            x_zero: cordicParams.y_zero,
            y_zero: -cordicParams.x_zero,
            angle: cordicParams.angle - 3*Math.PI/2
        }
    } else {  // cordicParams.angle >= 7*Math.PI/4 && cordicParams.angle <= 2*Math.PI
        rotatedParams = {
            x_zero: cordicParams.x_zero,
            y_zero: cordicParams.y_zero,
            angle: cordicParams.angle - 2*Math.PI
        }
    }

    return rotatedParams;
}

let angleLut = [];
let gain;

export function setupCordicConstants(iterations) {
    angleLut = generateAngleLUT(iterations);
    gain = calculateGainFromAngleLUT(angleLut);
}

export function calculateCordicCosine(angle) {
    const params = {x_zero: gain, y_zero: 0, angle: angle};
    const result = calculateCordicRotation(preRotateIntoRange(params), angleLut);

    return {cos: result.x_n, sin: result.y_n};
}
