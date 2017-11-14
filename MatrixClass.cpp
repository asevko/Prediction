//
// Created by Alexei Sevko on 11/2/17.
//

#include "MatrixClass.h"


void MatrixClass::show() {
    for (unsigned int i = 0; i < sizeX; i++) {
        for (unsigned int j = 0; j < sizeY; ++j) {
            std::cout << matrix[sizeX * j + i] << " ";
            if (j == sizeY - 1)
                std::cout << std::endl;
        }
    }
}

MatrixClass MatrixClass::transpose() {
    MatrixClass result(sizeY, sizeX);
    for (unsigned int i = 0; i < result.sizeX; i++) {
        for (unsigned int j = 0; j < result.sizeY; j++) {
            result(i, j) = matrix[sizeX * i + j];
        }
    }
    return result;
}

MatrixClass& MatrixClass::activationFunction() {
    for (double value : matrix) {
        value = atan(value);
    }
    return *this;
}
