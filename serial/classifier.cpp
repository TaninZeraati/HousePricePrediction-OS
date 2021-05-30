#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <time.h>
#include <cmath>

#include "csv_handler.h"
#include "classifier.h"


Classifier::Classifier(string addr, int price)
{

    csv_handler = new CSV_handler(addr, price);
    
    // clock_t t1=clock();
    dataset = csv_handler->read_csv();
    // cout<<"T readfile: "<<clock()-t1<<endl;

    // t1=clock();
    dataset = csv_handler->labeled(dataset);
    // cout<<"T labeling: "<<clock()-t1<<endl;

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


float Classifier::calc_accuracy()
{
    double correct = 0;
    vector<double> result;

    // clock_t t1=clock();

    result = classify();
    // cout<<"T classifing: "<<clock()-t1<<endl;

    // t1 = clock();

    for(int i = 0; i < result.size(); i++)
    {
        if(result[i] == dataset[i][8])
            correct ++;
    }
    // cout<<"T calc accuracy: "<<clock()-t1<<endl;
    return (correct/result.size())*100;
}