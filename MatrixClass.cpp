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

MatrixClass& MatrixClass::activationFunction(const double& T) {
    for (unsigned int i = 0; i < this->sizeX * this->sizeY; i ++) {
        this->matrix[i] = atan(this->matrix[i] - T);
    }
    return *this;
}

void MatrixClass::resize(unsigned int sizeX, unsigned int sizeY) {
    if (sizeX < 1 || sizeY < 1 ||
            sizeX < this->sizeX ||
            sizeY < this->sizeY) {
        throw std::logic_error("Negative matrix sizes");
    }
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->matrix.resize(sizeX * sizeY);
}

void MatrixClass::insert(const double& value) {
    this->sizeY += 1;
    this->matrix.resize(this->sizeX * this->sizeY);
    this->matrix.insert(this->matrix.begin(), value);
}