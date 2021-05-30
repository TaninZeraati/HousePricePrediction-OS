#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include <time.h>
#include "csv_handler.h"
#include "classifier.h"

using namespace std;


int main(int argc, char* argv[])
{
    // clock_t t1 = clock();

    string datasets;
    datasets = argv[1];
	datasets = datasets + "dataset.csv";
    int price;
    price = atoi(argv[2]);


    Classifier cl(datasets, price);

    cout<<"Accuracy: "<<std::fixed<<std::setprecision(2)<<cl.calc_accuracy()<<"%"<<endl;

    // cout <<"Time taken: %.2fs\n"<< (double)(clock() - t1)<<endl;
    // cout <<" clk per sec"<<CLOCKS_PER_SEC<<endl;
    return 0;
}