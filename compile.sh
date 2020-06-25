#!/bin/bash

echo "Begining build.."
g++ -c main.cpp
g++ main.o -o app -lsfml-system -lsfml-window -lsfml-graphics
if [ "$1" = "run" ];
then
	echo "Running app"
	./app
else
	echo "Build attempt finished"
fi


