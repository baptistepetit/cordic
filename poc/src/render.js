const canvas = document.getElementById("cordic-app-canvas");
var ctx = canvas.getContext("2d");

const xCenter = 400;
const yCenter = 400;
const radius = 200;

export function drawUnitCircle() {
    ctx.beginPath();
    ctx.arc(xCenter, yCenter, radius, 0, 2 * Math.PI);
    ctx.stroke();
}
