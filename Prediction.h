#ifndef PREDICTION_PREDICTION_H
#include "MatrixClass.h"
#include "LearningTemplate.h"
#include <fstream>
#include <cmath>
#define WRONG_INPUT "Wrong variable input"
#define FILE_DOES_NOT_EXIST "File does not exist"
#define PREDICTION_PREDICTION_H


class Prediction {
    const double T = 1; ///пороговое значение

    double e; ///допустимая ошибка 0 < e <= 0.1
    double alpha; ///шаг обучения 0 < alpha <= 0.1; alpha <= e
    unsigned int N; ///количество шагов обучения N >= 1, recommendation N = 1_000_000
    unsigned int p; ///количество рядов в матрице обучения p >= 1
    unsigned int L; ///(количество строк в матрице обучения L >= 1; L = q - p)
                    ///upd L - длина обучающей выборки
    unsigned int x; ///количество строк в матрице обучения x >= 1
    unsigned int n; ///количество нейронов на первом слое
    unsigned int m; ///количество нейронов на втором слое
    unsigned int q; ///размерность последовательности X; q >= 0
    unsigned int k; ///размерность последовательности Х; k = q + 1; k >= (p + L)
    unsigned int r; ///количество чисел последовательности, необходимые предсказать
    std::vector<LearningTemplate> templates;
    MatrixClass W;
    MatrixClass W_;
    std::vector<double> seaquence;
    const char *path;

    MatrixClass context;

    void generateWeightMatrix();
    void teaching();
    void predictionBuilder();
    void initVariables();
    void loadSeaquenceFromFile();
    void fillTemplates();
    double errorDegree(const double& delta);
    double f_(const double& value);
public:
    explicit Prediction(const char *path);
    std::vector<LearningTemplate> getTemplates() {return this->templates; };
    void test();
};


#endif //PREDICTION_PREDICTION_H
