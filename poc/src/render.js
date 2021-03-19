const canvas = document.getElementById("visualizer");
const container = document.getElementById("visualizerContainer");
var ctx = canvas.getContext("2d");

let xCenter = 128;
let yCenter = 128;
let radius = 120;

export function resizeCanvas() {
    const box = container.getBoundingClientRect();
    canvas.height = box.height;
    canvas.width = box.width;

    xCenter = box.width / 2;
    yCenter = box.height / 2;
    radius = box.width * 0.95 / 2;
}

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
