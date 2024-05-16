#!/bin/bash
g++ -o run driver.cpp \
              collision.h \
              collision.cpp \
              particles.h   \
              particles.cpp \
              -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

# run if compiled
if [ -f run ]
then
{
  echo "compiled sucessfully, starting Sand-Demo"
  chmod +x run
         ./run

}
else
  echo "ERROR: coudnt  compile"
fi

