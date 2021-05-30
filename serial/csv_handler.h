#ifndef csv_handler_h
#define csv_handler_h

#include <string>
#include <vector>

using namespace std;

class CSV_handler
{
    private:
    
    string address;
    int price_threshold;

    public:
    CSV_handler(string addr, int price);
    vector<vector<double> > read_csv();
    vector<vector<double> > labeled(vector<vector<double> > dataset);
    vector<float> avrg_calc(vector<vector<double> > dataset, vector<float> & cheap_house, vector<float> &expensive_house);
};



#endif