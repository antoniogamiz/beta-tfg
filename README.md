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
- I use `C++20` so you need to install an updated version of g++: ([source](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/))

    ~~~bash
    sudo apt install software-properties-common
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt install gcc-9 g++-9
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9
    sudo update-alternatives --config gcc
    ~~~
- In order to debug using my Visual Studio Code configuration, you will need to install `gdb`:

    ~~~bash
    sudo apt install gdb
    ~~~
