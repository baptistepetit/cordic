// Inspired from this article:
// https://css-tricks.com/value-bubbles-for-range-inputs/
export function displaySliderValue(slider, output) {
    const sliderPosition = Number(
        ((slider.value - slider.min) * 100) / (slider.max - slider.min)
    );
    if (slider.value === slider.min || slider.value === slider.max) {
        output.innerHTML = '';
    } else {
        output.innerHTML = slider.value;
        output.style.left = 'calc('
            + sliderPosition + '% + '
            + (8 - sliderPosition * 0.14) + 'px)';
    }
}
