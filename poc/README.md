# CORDIC Cos/Sin Web Demo

This quick proof of concept in JavaScript implements the CORDIC algorithm to calculate cosine and sine functions.

The code related to the algorithm is located in the `src/cordic.js` file.
The `src/visualizer.js` file contains functions drawing shapes to the html canvas of the website.
The `src/knob.js` and `src/slider.js` add html input customization for easier touch navigation.
Finally the `src/app.js` file serves as an entrypoint for the website.

Webpack is used to bundle the code for easy use in the static `index.html` page. GitHub Pages is used to host a live version of the demo website.


## Prerequisistes

The only requirement is to have [Node.js](https://nodejs.org/) installed on your computer.

It allows bundling of the code and running the unit tests.


## How to use

### Live demo

The website is live at the following address: [https://baptistepetit.github.io/cordic/](https://baptistepetit.github.io/cordic/)


### Building the website locally

To get ready simply run from this folder:

```bash
npm install
npm run build
```

After this you can open the `dist/index.html` file with your browser to play with the algorithm parameters and see their impact.


### Running the unit tests

If you did not already start with running:
```bash
npm install
```
Then you can run the unit tests with the command:
```bash
npm test
```

**Note:** Tests here are provided as a proof of correctness of the implementation but do not seek to cover the whole application.
