#!/bin/bash

export LD_LIBRARY_PATH=$PWD
export LD_PRELOAD=$PWD/malloc.so
$@
