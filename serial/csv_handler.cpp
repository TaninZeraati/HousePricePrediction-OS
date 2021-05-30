#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "csv_handler.h"

using namespace std;


CSV_handler::CSV_handler(string addr, int price)
{
    address = addr;
    price_threshold = price;

}


vector<vector<double>> CSV_handler::read_csv()
{
	fstream f; 
    f.open(address,ios::in); 
  	vector<vector<double>> rows;
    string line,word;
    getline(f,line);
    while (getline(f,line))
    { 
    	vector<double> row; 
        stringstream s(line); 
  		while (getline(s,word,',')) 
            row.push_back(stod(word)); 
        rows.push_back(row);
    }
    f.close();
    return rows;
}

vector<vector<double> > CSV_handler::labeled(vector<vector<double> > dataset)
{
    vector<double> row;
    vector<double> result_row;
    vector<vector<double> > result;
    
    for(int i = 0; i < dataset.size(); i++)
    {
        if(dataset[i][8] < price_threshold)
            dataset[i][8] = 0;
        else if (dataset[i][8] >= price_threshold)
            dataset[i][8] = 1;
        
        
    }

    return dataset;
}

vector<float> CSV_handler::avrg_calc(vector<vector<double> > dataset, vector<float> & cheap_house, vector<float> &expensive_house)
{

    
    for(int i = 0; i < dataset[0].size(); i++)
    {
        float sum_cheap, sum_expensive = 0;
        int number_cheap, number_expensive = 0;
        for(int j = 0; j < dataset.size(); j++)
        {
            if(dataset[j][8] == 0)
            {
                sum_cheap += dataset[j][i];
                number_cheap ++;
            }
            else if(dataset[j][8] == 1)
            {
                sum_expensive += dataset[j][i];
                number_expensive ++;
            }
        }

        cheap_house.push_back(sum_cheap / number_cheap);
        expensive_house.push_back(sum_expensive / number_expensive);

    }

    return expensive_house;
}