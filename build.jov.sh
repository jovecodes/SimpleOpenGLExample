set -xe

g++ ./main.cpp ./window.cpp -o main -lGL -lglfw -lm -g -Wall -Wextra
./main
