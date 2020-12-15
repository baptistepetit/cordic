const canvas = document.getElementById("cordic-app-canvas");
var ctx = canvas.getContext("2d");

const xCenter = 205;
const yCenter = 205;
const radius = 200;

export function clear() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = "#000000";
    ctx.lineWidth = 1;
}

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
