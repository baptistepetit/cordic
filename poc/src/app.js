import { calculateCordicCosine } from './cordic.js'
import * as renderer from './render.js'

export function run() {
    const targetAngle = Math.PI/4;
    const cordicIterations = 20;

    const res = calculateCordicCosine(targetAngle, cordicIterations);

    console.log(
        "Coordinates rotated through CORDIC algorithm: ",
        res
    );

    console.log(
        "Maths functions result: ",
        {x_n: Math.cos(targetAngle), y_n: Math.sin(targetAngle)}
    );

    renderer.drawUnitCircle();
    renderer.drawVector(Math.cos(targetAngle), Math.sin(targetAngle), "#FF0000", 5);
    renderer.drawVector(res.cos, res.sin, "#000000", 2);
}

run();
