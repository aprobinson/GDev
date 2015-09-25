#!/bin/bash
##---------------------------------------------------------------------------##
## CONFIGURE GDev with CMAKE
##---------------------------------------------------------------------------##

EXTRA_ARGS=$@
SDL_PREFIX_PATH=$HOME/
SDL_IMG_PREFIX_PATH=$HOME/
SDL_FONT_PREFIX_PATH=$HOME/
BOOST_PREFIX_PATH=$HOME/
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
    -D GDEV_ENABLE_DBC:BOOL=ON \
    -D SDL_PREFIX:STRING=$SDL_PREFIX_PATH \
    -D SDL_IMG_PREFIX:STRING=$SDL_IMG_PREFIX_PATH \
    -D SDL_FONT_PREFIX:STRING=$SDL_FONT_PREFIX_PATH \
    -D BOOST_PREFIX:STRING=$BOOST_PREFIX_PATH \
    $EXTRA_ARGS \
    $GDEV_SRC
