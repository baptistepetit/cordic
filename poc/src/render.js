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

export function drawVector(x, y, style, lineWidth) {
    ctx.beginPath();
    ctx.moveTo(xCenter + x * radius, yCenter - y * radius);
    ctx.lineTo(xCenter, yCenter);
    ctx.strokeStyle = style;
    ctx.lineWidth = lineWidth;
    ctx.stroke();
}
