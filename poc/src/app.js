import { calculateCordicCosine, setupCordicConstants } from './cordic.js'
import { displaySliderValue } from './slider.js'
import * as renderer from './render.js'

function degToRad(x){
    return x * Math.PI / 180;
}

const iterationsInput = document.getElementById("iterationsInput");
const iterationsOutput = document.getElementById("iterationsOutput");
const angleInput = document.getElementById("angle-input");

export function updateIterationsOutput() {
    displaySliderValue(iterationsInput, iterationsOutput);
}

export function setup() {
    const cordicIterations = iterationsInput.value;
    if (cordicIterations > 0) {
        setupCordicConstants(cordicIterations);
    }
}

export function run() {
    const targetAngle = degToRad(angleInput.value);
    let res = null;

    if (iterationsInput.value > 0) {
        res = calculateCordicCosine(targetAngle);
    }

    renderer.clear();
    renderer.drawUnitCircle();
    renderer.drawVector(Math.cos(targetAngle), Math.sin(targetAngle), "#FF0000", 5);

    if (res) {
        renderer.drawVector(res.cos, res.sin, "#000000", 2);
    } else {
        renderer.drawVector(1.0, 0.0, "#000000", 2);
    }
}

function init() {
    renderer.resizeCanvas();
    setup();
    run();
}

function resize() {
    renderer.resizeCanvas();
    run();
}

window.addEventListener('load', init)
window.addEventListener('resize', resize)
