#include "Prediction.h"

Prediction::Prediction(const char *path) {
    this->path = path;

    n = 5; m = 5; e = 0.00001; alpha = 0.01; N = 1000000; r = 5;
    predictionBuilder();
    teaching();
}

void Prediction::initVariables() {
    std::cout << "Enter number receptors (n):" << std::endl;
    std::cin >> n;
    if (n < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of neuron for hidden layer (m):" << std::endl;
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
    std::cout << "Enter number of learning steps (N):" << std::endl;
    std::cin >> N;
    if (N < 1) {
        throw std::logic_error(WRONG_INPUT);
    }
    std::cout << "Enter number of numbers to prediction (r):" << std::endl;
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
    L = static_cast<unsigned int>(seaquence.size() - n - 1) ;
}

void Prediction::fillTemplates() {
    for (int index = 0; index < L; index++){
        LearningTemplate aTemplate;
        aTemplate.addNumberToSeaquence(T);
        for (int shift = 0; shift < n; shift++) {
            aTemplate.addNumberToSeaquence(seaquence[index + shift]);
        }
        aTemplate.matrixFromSeaquence();
        aTemplate.setCorrectMember(seaquence[index + n]);
        templates.push_back(aTemplate);
    }
}

void Prediction::predictionBuilder() {
    loadSeaquenceFromFile();
    fillTemplates();
    generateWeightMatrix();
}

void Prediction::generateWeightMatrix() {
    srand(static_cast<unsigned int>(time(nullptr)));
    W = MatrixClass(n + m + 1, m);
    for (unsigned int i = 0; i < n + m + 1; i++) {
        for (unsigned int j = 0; j < m; j++) {
            W(i, j) =(((double) rand() / (RAND_MAX + 1.) * 2 - 1)) * 0.01;
        }
    }
    V = MatrixClass(m + 1, 1);
    for (unsigned int i = 0; i < m + 1; i++) {
        V(i, 0) = (((double) rand() / (RAND_MAX + 1.) * 2 - 1)) * 0.01;
    }
}

double Prediction::errorDegree(const double& delta) {
    return 1./2 * (delta * delta);
}
void Prediction::teaching() {

    double error;
    unsigned int iteration = 0;
    do {
        error = 0;
        context = MatrixClass(1, m);
        for (LearningTemplate learningTemplate : templates) {
            MatrixClass X = learningTemplate.getX() || context;
            MatrixClass inHidden = X * W;
            inHidden.activationFunction();
            context = inHidden;
            inHidden.insert(T);
            MatrixClass inY = inHidden * V;
            double answer = atan(inY(0,0));
            double delta = learningTemplate.getCorrectMember() - answer;
            double sigmaY = delta * f_(inY(0, 0));
            double alpha_sigmaY = alpha * sigmaY;

            for (unsigned int j = 0; j < m; j ++) {
                double sigma_Hidden_In  =  V(j, 0) * sigmaY;
                double sigma_Hidden = sigma_Hidden_In * f_(inHidden(0, j));
                for (unsigned int i = 0; i < n + m + 1; i ++) {
                    W(i, j) += (sigma_Hidden * alpha * X(0, i));
                }
            }

            for (unsigned int i = 0; i < m + 1; i++) {
                V(i, 0) += alpha_sigmaY * inHidden(0,i);
            }
        }
        context = MatrixClass(1, m);
        for (LearningTemplate learningTemplate : templates) {
            MatrixClass X = learningTemplate.getX() || context;
            MatrixClass inHidden = X * W;
            inHidden.activationFunction();
            context = inHidden;
            inHidden.insert(T);
            MatrixClass inY = inHidden * V;
            double answer = atan(inY(0,0));
            double delta = learningTemplate.getCorrectMember() - answer;
            error += errorDegree(delta);
            //std::cout << "Element: " << inY(0,0) << " delta: " << delta << std::endl;
        }
        iteration++;
        std::cout << "Iteration: " << iteration << " error: " << error << std::endl;
    } while (error > e && N > iteration);
    prediction();
}

void Prediction::prediction() {
    for (LearningTemplate learningTemplate : templates) {
        MatrixClass X = learningTemplate.getX() || context;
        MatrixClass inHidden = X * W;
        inHidden.activationFunction();
        context = inHidden;
        inHidden.insert(T);
        MatrixClass inY = inHidden * V;
    }
    for (unsigned int i = 0; i < r; i++ ){
        LearningTemplate aTemplate;
        aTemplate.addNumberToSeaquence(T);
        for (unsigned int j = n ; j > 0; j--){
            aTemplate.addNumberToSeaquence(seaquence[seaquence.size() - n + r - 1]);
        }
        aTemplate.matrixFromSeaquence();
        aTemplate.setCorrectMember(seaquence[seaquence.size() + r - 1]);
        templates.push_back(aTemplate);
        MatrixClass X = templates[templates.size() - 1].getX() || context;
        MatrixClass inHidden = X * W;
        inHidden.activationFunction();
        context = inHidden;
        inHidden.insert(T);
        MatrixClass inY = inHidden * V;
        double answer = atan(inY(0,0));
        std::cout << "Predicted: " << answer << std::endl;
        seaquence.push_back(answer);
    }
}

double Prediction::f_(const double &value) {
    return 1 / (1 + (value) * (value));
}
