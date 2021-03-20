import { calculateCordicCosine, setupCordicConstants } from './cordic.js'
import { displaySliderValue } from './slider.js'
import * as visualizer from './visualizer.js'

function degToRad(x){
    return x * Math.PI / 180;
}

const iterationsInput = document.getElementById("iterationsInput");
const iterationsOutput = document.getElementById("iterationsOutput");
const angleInput = document.getElementById("angleInput");

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

    visualizer.clear();
    visualizer.drawUnitCircle();
    visualizer.drawVector(Math.cos(targetAngle), Math.sin(targetAngle), "#FF0000", 5);

    if (res) {
        visualizer.drawVector(res.cos, res.sin, "#000000", 2);
    } else {
        visualizer.drawVector(1.0, 0.0, "#000000", 2);
    }
}

function init() {
    visualizer.resizeCanvas();
    setup();
    run();
}

function resize() {
    visualizer.resizeCanvas();
    run();
}

window.addEventListener('load', init)
window.addEventListener('resize', resize)
