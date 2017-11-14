#include "LearningTemplate.h"

void LearningTemplate::matrixFromSeaquence() {
    std::vector<double> numbers(seaquence);
    numbers.push_back(0);
    this->X = MatrixClass(numbers);///was seaquence
}

void LearningTemplate::setContextNeuron(double neuron) {
    this->X(0, static_cast<unsigned int>(seaquence.size())) = neuron;
}

void LearningTemplate::addNumberToSeaquence(double number) {
    this->seaquence.push_back(number);
}

void LearningTemplate::setCorrectMember(double correctMember) {
    this->correctMember = correctMember;
}
