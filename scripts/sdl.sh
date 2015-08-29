#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE SDK with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
SDL_INSTALL=$HOME/
SDL_SRC=../src

##---------------------------------------------------------------------------##
source ~/.bashrc

cmake --version

cmake \
    -D CMAKE_INSTALL_PREFIX:PATH=$SDL_INSTALL \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
    $EXTRA_ARGS \
    $SDL_SRC 
