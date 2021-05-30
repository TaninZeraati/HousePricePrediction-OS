#ifndef classifier_h
#define classifier_h

#include <string>
#include <vector>

#include "csv_handler.h"

class Classifier
{
    private:
    CSV_handler* csv_handler;
    int price;
    vector<vector<double>> dataset;

    public:
    Classifier(string addr,  vector<vector<double>> data,int price);
    vector<double> classify();
    double count_correct();

};

#endif
