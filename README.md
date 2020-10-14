# Final Degree Project

This repository hosts my final degree project of my double bachelor degree in Mathematics and Computer Science at [ETSIIT](https://etsiit.ugr.es/).

The whole implementation of the ray tracer is based on a [Ray Tracing](https://raytracing.github.io/) book series.

### Using Digital Ocean

First you need to install [doctl](). You can check [this tutorial](https://www.digitalocean.com/community/tutorials/how-to-use-doctl-the-official-digitalocean-command-line-client) to learn the basics commands.

### External libraries

- [Image library](https://github.com/nothings/stb)

### Compile LaTex source

To compile the latex code you need to run:

~~~shell
cd doc/latex # always compile from this directory
pdflatex -synctex=1 -interaction=nonstopmode --shell-escape --output-directory=build master.tex
~~~

This project contains a lot of Tikz figures so they are cached the first time they are generated. To edit or add new figures, see [figures directory](doc/latex/figures). This has been done following the instructions on [this question](https://tex.stackexchange.com/questions/482557/how-to-externalize-tikz-pictures).

To compile the bibliography you need to setup TexMaker: see [this answer](https://tex.stackexchange.com/a/193610/161499) and change the Bixtex command to
`bibtex build/%`. Remember enabling `Use a "build" subdirectory for output files.`

To setup minted, I followed [this article](https://blog.wotw.pro/syntax-highlighting-in-latex-with-minted/).

### References

- Some latex code have been based on [this source](https://github.com/VictorMorenoJimenez/tfg2020/tree/master/doc/latex).