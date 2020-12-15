# CORDIC Cos/Sin Web Demo

This quick proof of concept in JavaScript implements the CORDIC algorithm to calculate cosine and sine functions.

The code related to the algorithm is located in the `src/cordic.js` file, the `src/render.js` file contains functions drawing shapes to the html canvas of the website, and the `src/app.js` file serves as an entrypoint for the website.

Webpack is used to bundle the code for easy use in the static `index.html` page.


## Prerequisistes

The only requirement is to have [Node.js](https://nodejs.org/) installed on your computer.

It allows bundling of the code and running the unit tests.


## How to use

### Opening the website

To get ready simply run from this folder:

```bash
npm install
npm run build
```

After this you can open the `index.html` file with your browser to play with the algorithm parameters and see their impact.


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
