#!/bin/bash

g++ main1.cpp pacmanrobot.cpp pacmanmap.cpp -o pacman -lsfml-graphics -lsfml-window -lsfml-system
if [ $? -eq 0 ]; then
    ./pacman 
fi


