#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE GDev with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
SDL_PREFIX_PATH=$HOME/
GDEV_INSTALL=$HOME/
GDEV_SRC=../src

##---------------------------------------------------------------------------##
source ~/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$GDEV_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=DEBUG \
    -D CMAKE_VERBOSE_CONFIGURE:BOOL=ON \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    -D SDL_PREFIX:STRING=$SDL_PREFIX_PATH \
    $EXTRA_ARGS \
    $GDEV_SRC