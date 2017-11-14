#include <iostream>
#include "Prediction.h"

int main() {
    Prediction prediction("/Users/alexeisevko/CLionProjects/Prediction/seaquence.txt");
//    std::vector<LearningTemplate> templates = prediction.getTemplates();
//    for (auto aTemplate : templates) {
//        aTemplate.getX().show();
//    }
    prediction.test();
    return 0;
}