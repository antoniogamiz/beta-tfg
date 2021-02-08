# Main Report

This repository hosts the main report of my final project of my double bachelor degree in Mathematics and Computer Science at [ETSIIT](https://etsiit.ugr.es/).

### Compilation

To compile the latex code you need to run:

~~~shell
pdflatex -synctex=1 -interaction=nonstopmode --shell-escape --output-directory=build master.tex
~~~

This project contains a lot of Tikz figures so they are cached the first time they are generated. To edit or add new figures, see [figures directory](figures). This has been done following the instructions on [this question](https://tex.stackexchange.com/questions/482557/how-to-externalize-tikz-pictures).

In order to compile the bibliography you need to setup TexMaker: see [this answer](https://tex.stackexchange.com/a/193610/161499) and change the Bixtex command to `bibtex build/%`. Remember enabling `Use a "build" subdirectory for output files.`

To setup minted, I followed [this article](https://blog.wotw.pro/syntax-highlighting-in-latex-with-minted/).

### References

- Some latex code have been based on [this source](https://github.com/VictorMorenoJimenez/tfg2020/tree/master/doc/latex).