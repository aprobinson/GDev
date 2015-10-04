Installation {#installation}
=====

## Dependencies
1. [GNU Compiler 4.7.3+](https://gcc.gnu.org/)
2. [CMake 3.0.1+](http://www.cmake.org/)
3. [Doxygen 1.8.8](http://www.stack.nl/~dimitri/doxygen/index.html)
3. [Boost 1.59.0+](http://www.boost.org/)
4. [SDL 2.0.3+](https://www.libsdl.org/download-2.0.php)
5. [SDL_image 2.0.0+](https://www.libsdl.org/projects/SDL_image/)
6. [SDL_ttf 2.0.12+](https://www.libsdl.org/projects/SDL_ttf/)

## Building Dependent Software Libraries
When building software libraries and executables the following directory structure should be adopted: software/package/package.xx.xx.xx, software/package/build, software/package/src. "package" will be the name of the particular software package of interest (see dependencies). "package.xx.xx.xx" comes from unpacking the compressed source files (e.g. package.tar.gz). The src directory is created by making a softlink to the package.xx.xx.xx directory. This is done to make the build a bit easier/faster.

Note that currently, depencies 1 and 2 should be built first.

### Checking out GDev
1. create a working directory where GDev will be built (e.g. software/gdev)
2. move to the gdev directory
3. run `git clone git@github.com:aprobinson/GDev.git`
4. run `ln -s FRENSIE src`

When you run `ls` from your working directory you should see the following: `GDev src`. We will return to building GDev after we have build the dependencies.

### Building CMake
1. download the [CMake 3.0.1 source](http://www.cmake.org/cmake/resources/software.html)
2. move the cmake-3.0.1.tar.gz file to the cmake working directory (e.g. software/cmake)
3. move to the cmake directory
4. run `tar -xvf cmake-3.0.1.tar.gz`
5. run `ln -s cmake-3.0.1 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/cmake/build)
8. run `../src/configure --prefix=absolute-path-to_software/cmake`
9. run `make -j n`, where n is the number of threads to use while building
10. run `make test`
11. run `make install`
12. add the following line to the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:$PATH`
13. run `exec bash`
14. run `cmake --version` and verify that the output is 3.0.1

### Building Doxygen
1. download the [Doxygen 1.8.8 source](http://sourceforge.net/projects/doxygen/files/)
2. move the `doxygen-1.8.8.src.tar.gz` file to the doxygen working directory (e.g. software/gsl)
3. move to the doxygen directory
4. run `tar -xvf doxygen-1.8.8.src.tar.gz`
5. move to the doxygen-1.8.8 directory
6. run `./configure --prefix=absolute-path-to_software/doxygen`
7. run `make -j n`
8. run `make test`
9. run `make install`
10. update the `export PATH` line in the .bashrc file: `export PATH=absolute-path-to_software/cmake/bin:absolute-path-to_software/doxygen/bin:$PATH`
11. run `exec bash`

### Building SDL
1. download the [SDL 2.0.3 source](https://www.libsdl.org/release/SDL2-2.0.3.tar.gz)
2. move the SDL2-2.0.3.tar.gz file to the sdl working directory (e.g. software/sdl)
3. move to the sdl directory
4. run `tar -xvf SDL2-2.0.3.tar.gz`
5. run `ln -s SDL2-2.0.3 src`
6. run `mkdir build`
7. move to the build directory (e.g. software/sdl/build)
8. copy `GDev/scripts/sdl.sh` into the build directory
9. change the variables in the script to reflect the desired system paths
10. run `sudo apt-get build-dep libsdl2`
11. run `./sdl.sh` to configure SDL
12. run `make -j n`
13. run `make install`
14. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_Software/sdl/lib:$PATH`
15. run `exec bash`

### Building SDL image
1. download the [SDL_image 2.0.0](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz)
2. move the SDL2_image-2.0.0.tar.gz file to the sdl working directory (e.g. software/sdl-image)
3. move to the sdl-image directory
4. run `tar -xvf SDL2_image-2.0.0.tar.gz`
5. run `ln -s SDL2_image-2.0.0 src`
6. move to the build directory (e.g. software/sdl-image/build)
7. run `sudo apt-get build-dep libSDL2-image`
8. run `../src/configure --prefix=../.`
9. run `make -j n`
10. run `make install`
11. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_Software/sdl-image/lib:$PATH`
12. run `exec bash`

### Build SDL text
1. download the [SDL_ttf 2.0.12](https://www.libsdl.org/projects/SDL_ttf/)
2. move the SDL2_ttf-2.0.12.tar.gz file to the sdl working directory (e.g. software/sdl-text)
3. move to the sdl-text directory
4. run `tar -xvf SDL2_tff-2.0.12.tar.gz`
5. run `ln -s SDL2_tff-2.0.12 src`
6. move to the build directory (e.g. software/sdl-text/build)
7. run `sudo apt-get build-dep libsdl2-ttf-dev`
8. run `../src/configure --prefix=../.`
9. run `make -j n`
10. run `make install`
11. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_Software/sdl-text/lib:$PATH`
12. run `exec bash`

### Building Boost
1. download the [Boost 1.59.0 source](http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz/download)
2. move the boost_1_59_0.tar.gz file to the boost directory (e.g. software/boost)
3. move to the boost directory
4. run `tar -xvf boost_1_59_0.tar.gz`
5. move to the boost_1_59_0 directory (e.g. software/boost/boost_1_59_0)
6. run `./bootstrap.sh --prefix=absolute-path-to_software/boost`
7. run `./b2`
8. run `./b2 install`
9. update the `export LD_LIBRARY_PATH` line in the .bashrc file: `export LD_LIBRARY_PATH=absolute-path-to_Software/sdl/lib:absolute-path-to_software/boost/lib:$LD_LIBRARY_PATH`
10. run `exec bash`

## Building GDev
At this point all of the dependent software libraries should have been built. If any errors were encountered do not try to proceed to building GDev. If no errors were encountered, follow the instructions below.

1. move to the gdev working directory - not the repo itself (e.g. software/gdev, not software/gdev/GDev)
2. run `mkdir build`
3. move to the build directory (e.g. software/gdev/build)
4. copy the `GDev/scripts/gdev.sh` script into the build directory
5. change the variables in the script to reflect the desired system paths
6. run `./gdev.sh` to configure GDev
7. run `make -j n`
8. run `make test`
9. run `make install`
