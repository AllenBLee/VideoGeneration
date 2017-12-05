#!/bin/bash

./clean.sh

g++ *.cpp
./a.out
open output.mp4
