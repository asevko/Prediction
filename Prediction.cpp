#include "Prediction.h"

Prediction::Prediction(const char *path) {
    this->path = path;
    //predictionBuilder();
    //teaching();
}

void Prediction::initVariables() {
    std::cout << "Enter number of neuron for first layer (n):" << std::endl;
    std::cin >> n;
    if (n < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of neuron for second layer (m):" << std::endl;
    std::cin >> m;
    if (m < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter error degree (e):" << std::endl;
    std::cin >> e;
    if (e < 0 || e > 0.1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter learning step (alpha):" << std::endl;
    std::cin >> alpha;
    if (alpha < 0 || alpha > 0.1 || alpha > e) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of cols in learning matrix (p):" << std::endl;
    std::cin >> p;
    if (p < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
//    std::cout << "Enter number of rows in learning matrix (L):" << std::endl;
//    std::cin >> L;
//    if (L < 1) {
//        throw std::logic_error(WRONG_INPUT);
//    }
    std::cout << "Enter number of rows in learning matrix (x):" << std::endl;
    std::cin >> x;
    if (x < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of learning steps (N):" << std::endl;
    std::cin >> N;
    if (N < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of numbers to predict (r):" << std::endl;
    std::cin >> r;
    if (r < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
}

void Prediction::loadSeaquenceFromFile() {
    std::ifstream inputFile(this->path);
    if (!inputFile.is_open()) {
        throw std::logic_error(FILE_DOES_NOT_EXIST);
    } else {
        double number;
        while (inputFile >> number) {
            this->seaquence.push_back(number);
        }
        inputFile.close();
    }
    k = static_cast<unsigned int>(seaquence.size());
    q = k - 1;
    if (k < p + L) {
        throw std::logic_error(WRONG_INPUT);
    }
}

void Prediction::fillTemplates() {
    L = q - p;
//    for (int index = 0; index < L; index++){ ///was k-p
//        LearningTemplate aTemplate;
//        for (int shift = 0; shift < p; shift++) {
//            aTemplate.addNumberToSeaquence(seaquence[index + shift]);
//        }
//        aTemplate.matrixFromSeaquence();
//        aTemplate.setCorrectMember(seaquence[index + p ]);
//        templates.push_back(aTemplate);
//    }
    for (int index = 0; index < x; index++){ ///was k-p
        LearningTemplate aTemplate;
        aTemplate.addNumberToSeaquence(1);
        for (int shift = 0; shift < p; shift++) {
            aTemplate.addNumberToSeaquence(seaquence[index + shift]);
        }
        aTemplate.matrixFromSeaquence();
        aTemplate.setCorrectMember(seaquence[index + p]);
        templates.push_back(aTemplate);
    }
    //L = static_cast<unsigned int>(templates.size()) - p;
}

void Prediction::teaching() {
    double error;
    unsigned int iteration = 0;
    context = MatrixClass(m, 1);
    generateWeightMatrix();
    do {
        error = 0;
        for (LearningTemplate aTemplate : templates) {
            MatrixClass X = aTemplate.getX() ^ context;
            MatrixClass Y = (X * W).activationFunction(T);
            context = Y;
            Y.insert(1); ///добавляем контект для активации нейрона
            MatrixClass X_ = (Y * W_).activationFunction(T);
            double correctMember = aTemplate.getCorrectMember();
            double delta = X_(0,0) - correctMember;
            MatrixClass deltaX = X_ - X;/// not like this

            W =  W - (X.transpose() * alpha * deltaX * W_.transpose());
            W_ = W_ - (Y.transpose() * alpha * deltaX);
        }
        for (LearningTemplate aTemplate : templates) {
            MatrixClass X = aTemplate.getX();
            MatrixClass Y = X * W + context * W_;
            context = Y;
            MatrixClass X_ = Y * W_;
            MatrixClass deltaX = X_ - X;
            error += errorDegree(deltaX);
        }
        iteration++;
    } while (error > e && N > iteration);
}

void Prediction::predictionBuilder() {
    initVariables();
    loadSeaquenceFromFile();
    fillTemplates();
    generateWeightMatrix();
}

void Prediction::generateWeightMatrix() {
    srand(static_cast<unsigned int>(time(nullptr)));
    W = MatrixClass(p + m + 1, m);
    for (unsigned int i = 0; i < p + m + 1; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if (i == 0) {
                W(i, j) = 1;
            } else {
                W(i, j) = (((double) rand() / (RAND_MAX + 1.) * 2 - 1)) * 0.1;
            }
        }
    }
    W_ = MatrixClass(m + 1, n);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (i == 0) {
                W_(i, j) = 1;
            } else {
                W_(i, j) = (((double) rand() / (RAND_MAX + 1.) * 2 - 1)) * 0.1;
            }
        }
    }
}

double Prediction::errorDegree(MatrixClass deltaX) {
    double e = 0;
    for (unsigned int i = 0; i < L; i++) {
        e += (deltaX(0, i) * deltaX(0, i));
    }
    return e;
}

void Prediction::test() {
    //predictionBuilder();
    n = 3; m = 4; e = 0.01; alpha = 0.001; p = 4; x = 3; N = 10; r = 5;
    loadSeaquenceFromFile();
    fillTemplates();
    generateWeightMatrix();
    double error;
    unsigned int iteration = 0;
    context = MatrixClass(1, m);
    do {
        error = 0;
    //LearningTemplate learningTemplate = templates[0];
    for (LearningTemplate learningTemplate : templates) {
        MatrixClass X = (learningTemplate.getX() ^ context).activationFunction(T);
        MatrixClass Y = (X * W).activationFunction(T);
        context = Y;
        Y.insert(1);
        MatrixClass X_ = (Y * W_).activationFunction(T);
//        std::cout << "U: " << std::endl;
//        X_.show();
        MatrixClass deltaX = X_ - X;

        W =  W - (X.transpose() * alpha * deltaX * W_.transpose());
        W_ = W_ - (Y.transpose() * alpha * deltaX);
        }
        for (LearningTemplate learningTemplate : templates) {
            MatrixClass X = (learningTemplate.getX() ^ context).activationFunction(T);
            MatrixClass Y = (X * W).activationFunction(T);
            context = Y;
            Y.insert(1);
            MatrixClass X_ = (Y * W_).activationFunction(T);
            MatrixClass deltaX = X_ - X;
            error += errorDegree(deltaX);
        }
        iteration++;
        std::cout << "Iteration: " << iteration << " error: " << error << std::endl;
    } while (error > e && N > iteration);
}