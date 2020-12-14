import { calculateCordicCosine } from './cordic.js'

export function run() {
    console.log(
        "Coordinates rotated through CORDIC algorithm: ",
        calculateCordicCosine(Math.PI / 4, 20)
    );

    console.log(
        "Maths functions result: ",
        {x_n: Math.cos(Math.PI / 4), y_n: Math.sin(Math.PI / 4)}
    );

}

run();
