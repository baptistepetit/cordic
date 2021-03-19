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
