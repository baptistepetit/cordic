import { calculateCordicCosine } from './cordic.js'
import * as renderer from './render.js'

function degToRad(x){
    return x * Math.PI / 180;
}

const iterationsInput = document.getElementById("iterations-input");
const angleInput = document.getElementById("angle-input");

export function run() {
    const targetAngle = degToRad(angleInput.value);
    const cordicIterations = iterationsInput.value;

    const res = calculateCordicCosine(targetAngle, cordicIterations);

    console.log(
        "Coordinates rotated through CORDIC algorithm: ",
        res
    );

    console.log(
        "Maths functions result: ",
        {x_n: Math.cos(targetAngle), y_n: Math.sin(targetAngle)}
    );

    renderer.clear();
    renderer.drawUnitCircle();
    renderer.drawVector(Math.cos(targetAngle), Math.sin(targetAngle), "#FF0000", 5);
    renderer.drawVector(res.cos, res.sin, "#000000", 2);
}

run();
