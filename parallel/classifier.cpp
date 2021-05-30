#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <cmath>

#include "csv_handler.h"
#include "classifier.h"


Classifier::Classifier(string addr,  vector<vector<double>> data,int price)
{

    csv_handler = new CSV_handler(addr, price);
    dataset = data;

}


float calc_deviation(vector<double> row, float avrg)
{
    double E=0;
    for(int i=0;i<row.size();i++)
    {
        E += (row[i] - avrg)*(row[i] - avrg);
    }

    return sqrt(E/row.size());
}



vector<double> Classifier::classify()
{
    vector<double> result;
    vector<float> avg_expensive, avg_cheap;
    avg_expensive = csv_handler->avrg_calc(dataset, avg_expensive, avg_cheap);
    float std_devt, ave;
    vector<double> row;


    ave = avg_expensive[5];

    for(int i = 0; i < dataset.size(); i++)
    {
        if(dataset[i][8] == 1)
           row.push_back(dataset[i][5]);
    }
    std_devt = calc_deviation(row, ave);

    for(int j = 0; j < dataset.size(); j++)
    {
        double lv_area = dataset[j][5];
        if(lv_area <= (ave-std_devt) || lv_area >=(ave+std_devt))
            result.push_back(0);
        else if ((ave-std_devt) < lv_area < (ave+std_devt))
            result.push_back(1);

    }
    return result;

}


double Classifier::count_correct()
{
    double correct = 0;
    vector<double> result;
    result = classify();

    for(int i = 0; i < result.size(); i++)
    {
        if(result[i] == dataset[i][8])
            correct ++;
    }
    return correct;
}