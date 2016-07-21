#!/bin/bash
rm bin/*
for f in *.cpp
do g++ "$f" -o bin/"$f".run
done
