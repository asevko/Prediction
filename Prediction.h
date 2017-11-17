#ifndef PREDICTION_PREDICTION_H
#include "MatrixClass.h"
#include "LearningTemplate.h"
#include <fstream>
#include <cmath>
#define WRONG_INPUT "Wrong variable input"
#define FILE_DOES_NOT_EXIST "File does not exist"
#define PREDICTION_PREDICTION_H


class Prediction {
    const double T = -1; ///пороговое значение

    double e; ///допустимая ошибка 0 < e <= 0.1
    double alpha; ///шаг обучения 0 < alpha <= 0.1; alpha <= e
    unsigned int N; ///количество шагов обучения N >= 1, recommendation N = 1_000_000
    unsigned int n; ///окно обучения
    unsigned int m; ///количество нейронов на скрытом слое
    unsigned int r; ///количество чисел последовательности, необходимые предсказать
    unsigned  int L; ///количество обучающих выборок
    std::vector<LearningTemplate> templates;
    MatrixClass W;
    MatrixClass V;
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
    void prediction();
public:
    explicit Prediction(const char *path);
};


#endif //PREDICTION_PREDICTION_H
