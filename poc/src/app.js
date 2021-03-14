import { calculateCordicCosine, setupCordicConstants } from './cordic.js'
import * as renderer from './render.js'

function degToRad(x){
    return x * Math.PI / 180;
}

const iterationsInput = document.getElementById("iterationsInput");
const angleInput = document.getElementById("angle-input");

export function setup() {
    const cordicIterations = iterationsInput.value;
    setupCordicConstants(cordicIterations);
}

export function run() {
    const targetAngle = degToRad(angleInput.value);
    const res = calculateCordicCosine(targetAngle);

    renderer.clear();
    renderer.drawUnitCircle();
    renderer.drawVector(Math.cos(targetAngle), Math.sin(targetAngle), "#FF0000", 5);
    renderer.drawVector(res.cos, res.sin, "#000000", 2);
}

setup();
run();
