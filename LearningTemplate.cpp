#include "LearningTemplate.h"

void LearningTemplate::matrixFromSeaquence() {
    this->X = MatrixClass(seaquence);///was seaquence
}

void LearningTemplate::addNumberToSeaquence(double number) {
    this->seaquence.push_back(number);
}

void LearningTemplate::setCorrectMember(double correctMember) {
    this->correctMember = correctMember;
}
