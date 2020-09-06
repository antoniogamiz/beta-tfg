# Final Degree Project

This repository hosts my final degree project of my double bachelor degree in Mathematics and Computer Science at [ETSIIT](https://etsiit.ugr.es/).

### Compile LaTex source

To compile the latex code you need to run:

~~~shell
pdflatex -synctex=1 -interaction=nonstopmode --shell-escape --output-directory=build %.tex
~~~

This project contains a lot of Tikz figures so they are cached the first time they are generated. To edit or add new figures, see [figures directory](doc/latex/figures). This has been done following the instructions on [this question](https://tex.stackexchange.com/questions/482557/how-to-externalize-tikz-pictures).