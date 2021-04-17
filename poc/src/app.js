import { calculateCordicCosine, setupCordicConstants } from './cordic.js'
import { displaySliderValue } from './slider.js'
import * as visualizer from './visualizer.js'
import * as knob from './knob.js'

function degToRad(x){
    return x * Math.PI / 180;
}

function radToDeg(x){
    return x * 180 / Math.PI;
}

const angleInput = document.getElementById("angleInput");
const canvas = document.getElementById("visualizer");
const iterationsInput = document.getElementById("iterationsInput");
const iterationsOutput = document.getElementById("iterationsOutput");

export function updateIterationsOutput() {
    displaySliderValue(iterationsInput, iterationsOutput);
}

export function updateAngleInput(e) {
    const rotation = knob.dragRotate(e);

    if (rotation !== null) {
        let angle = parseInt(angleInput.value);
        angle += radToDeg(rotation);

        if (angle < 0) {
            angle += 360;
        }
        if (angle > 360) {
            angle -= 360;
        }

        angleInput.value = Math.floor(angle);
        run();
    }
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

window.addEventListener('load', init);
window.addEventListener('resize', resize);

canvas.addEventListener('pointerdown', knob.startDragging);
canvas.addEventListener('pointerup', knob.stopDragging);
canvas.addEventListener('pointermove', updateAngleInput);
