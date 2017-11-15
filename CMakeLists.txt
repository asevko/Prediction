cmake_minimum_required(VERSION 3.8)
project(Prediction)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MatrixClass.cpp MatrixClass.h Prediction.cpp Prediction.h LearningTemplate.cpp LearningTemplate.h)
add_executable(Prediction ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS_RELEASE  "-O3")