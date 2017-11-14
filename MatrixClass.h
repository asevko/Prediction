/***
 * @author Aleksey Sevko
 */
#ifndef IMAGECOMPRESSION_MATRIXCLASS_H

#include <vector>
#include <math.h>
#include <iostream>
#define IMAGECOMPRESSION_MATRIXCLASS_H

/// sizeX = n, sizeY = m
class MatrixClass {
    std::vector<double> matrix;
    unsigned int sizeX, sizeY;
public:
    MatrixClass() : sizeX(0), sizeY(0){}

    MatrixClass (unsigned int x, unsigned int y)
            : sizeX(x), sizeY(y) {
        matrix.resize(sizeX * sizeY);
    }

    explicit MatrixClass (std::vector<double> vector)
            : sizeX(1), sizeY(static_cast<unsigned int>(vector.size())) {
        matrix.resize(sizeX * sizeY);
        std::copy(vector.begin(), vector.end(), matrix.begin());
    }

    ~MatrixClass() {
        std::vector<double>().swap(matrix);
    }

    double& operator()(unsigned int x, unsigned int y) {
        if (x >= sizeX || y >= sizeY) {
            throw std::out_of_range("Bad access");
        }
        return matrix[sizeX * y + x];
    }

    const double& operator()(unsigned int x, unsigned int y) const {
        if (x >= sizeX || y >= sizeY) {
            throw std::out_of_range("Bad access");
        }
        return matrix[sizeX * y + x];
    }

    MatrixClass& operator*(const double value) {
        std::transform(this->matrix.begin(), this->matrix.end(), this->matrix.begin(),
                       std::bind1st(std::multiplies<double>(),value));
        return *this;
    }

    friend MatrixClass operator-(const MatrixClass &l, const MatrixClass &r) {
        if (l.sizeX != r.sizeX
                || l.sizeY != r.sizeY) {
            throw std::logic_error("Different matrix sizes");
        }
        MatrixClass result(l.sizeX, l.sizeY);
        auto n = static_cast<unsigned int>(l.matrix.size());
        for (unsigned int i = 0; i < n; i ++) {
            result.matrix[i] = l.matrix[i] - r.matrix[i];
        }
        return result;
    }

    friend MatrixClass operator+(const MatrixClass &l, const MatrixClass &r) {
        if (l.sizeX != r.sizeX
            || l.sizeY != r.sizeY) {
            throw std::logic_error("Different matrix sizes");
        }
        MatrixClass result(l.sizeX, l.sizeY);
        auto n = static_cast<unsigned int>(l.matrix.size());
        for (unsigned int i = 0; i < n; i ++) {
            result.matrix[i] = l.matrix[i] + r.matrix[i];
        }
        return result;
    }

    MatrixClass& operator=(const MatrixClass& other) {
        if (this != &other) {
            std::vector<double>().swap(this->matrix);
            if (this->matrix.size() != other.matrix.size()) {
                this->matrix.resize(other.sizeX * other.sizeY);
            }
            this->sizeX = other.sizeX;
            this->sizeY = other.sizeY;
            std::copy(other.matrix.begin(), other.matrix.end(), this->matrix.begin());
        }
        return *this;
    }

    friend MatrixClass operator *(const MatrixClass &l, const MatrixClass &r) {
        if (l.sizeY != r.sizeX) {
            throw std::logic_error("Wrong sizes");
        }
        MatrixClass result(l.sizeX, r.sizeY);
        for (unsigned int i = 0; i < result.sizeX; i++) {
            for (unsigned int j = 0; j < result.sizeY; j++){
                double sum = 0;
                for (unsigned int k = 0; k < r.sizeX; k++){
                    sum += l(i,k) * r(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    friend MatrixClass operator ^(const MatrixClass &l, const MatrixClass &r) {
        if (l.sizeX != r.sizeX) {
            throw std::logic_error("Different matrix sizes");
        }
        MatrixClass result = l;
        result.resize(1, l.sizeY + r.sizeY);
        for (unsigned int i = l.sizeY, j = 0; j < r.sizeY; i++, j++) {
            result.matrix[i] = r.matrix[j];
        }
        return result;
    }

    void show();
    MatrixClass transpose();
    MatrixClass& activationFunction(const double& T);
    void insert(const double& value);
    void resize(unsigned int sizeX, unsigned int sizeY);
    virtual int getX() const { return this->sizeX; };
    virtual int getY() const { return this->sizeY; };
};


#endif //IMAGECOMPRESSION_MATRIXCLASS_H
