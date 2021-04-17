const canvas = document.getElementById("visualizer");

function getAngularPosition(event) {
    const box = canvas.getBoundingClientRect();

    const xPointer = event.clientX - box.width/2 - box.left;
    const yPointer = event.clientY - box.height/2 - box.top;

    let angularPosition = Math.atan2(yPointer, -xPointer);
    angularPosition += Math.PI;

    return angularPosition;
}

let isDragging = null;
let previousAngle = null;

export function startDragging(e) {
    isDragging = true;
    previousAngle = getAngularPosition(e);
}

export function stopDragging(e) {
    isDragging = false;
}

export function dragRotate(e) {
    if (!isDragging) {
        return null;
    }

    const currentAngle = getAngularPosition(e);
    const rotationDelta = currentAngle - previousAngle;

    previousAngle = currentAngle;
    return rotationDelta;
}
