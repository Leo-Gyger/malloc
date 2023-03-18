#!/bin/bash
export MALLOC_FORCE_MMAP=1
export LD_LIBRARY_PATH=$PWD
export LD_PRELOAD=$PWD/libft_malloc_x86_64_Linux.so
$@
