# Final Degree Project

This repository hosts my final degree project of my double bachelor degree in Mathematics and Computer Science at [ETSIIT](https://etsiit.ugr.es/).

The whole implementation of the ray tracer is based on a [Ray Tracing](https://raytracing.github.io/) book series.

### Using Digital Ocean

First you need to install [doctl](). You can check [this tutorial](https://www.digitalocean.com/community/tutorials/how-to-use-doctl-the-official-digitalocean-command-line-client) to learn the basics commands.

### External libraries

- [Image library](https://github.com/nothings/stb). To avoid problems with warnings and formatting I have the following configuration in Visual Studio Code:
    ~~~json
    "files.associations": {
        "stb_image.h": "plaintext"
    },
    ~~~
    And the following pragmas added to the header file:
    ~~~c++
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    #pragma GCC diagnostic ignored "-Wsign-compare"

    ...

    #pragma GCC diagnostic pop
    ~~~

