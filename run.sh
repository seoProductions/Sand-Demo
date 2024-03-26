#!/bin/bash
g++ -o run driver.cpp \
              collision.h \
              collision.cpp \
              particles.h   \
              particles.cpp \
              -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
chmod +x run
       ./run