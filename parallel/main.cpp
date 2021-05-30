#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include <time.h>
#include <pthread.h>

#include "csv_handler.h"
#include "classifier.h"

using namespace std;

typedef struct 
{
	double corrects;
	double _all;
} Res;

typedef struct 
{
	vector<vector<double>> dataset;
	// vector<double> exp;
	// vector<double> chp;
} Calc_Data;

typedef struct 
{
    int price_th;
	char* train_dir;
} Pre_Calc_Data;

#define NUMBER_OF_THREADS 1
Res result; 
Pre_Calc_Data TD;
Calc_Data cTD[NUMBER_OF_THREADS];
pthread_t threads[NUMBER_OF_THREADS];
pthread_mutex_t mutex_sum;
vector<double> expensive;
vector<double> cheap;


void itos(long a,char s[20])
{
	int i=0;
	char _s;
	while (a>9)
	{
		s[i]=a%10+'0';
		a/=10;
		i++;
	}
	s[i]=a+'0';
	for (int j=0;j<=i/2;j++)
	{
		_s=s[i-j];
		s[i-j]=s[j];
		s[j]=_s;
	}
	s[i+1]=0;
}



void* pre_calc(void* arg)
{
	long i=(long)arg;
	char _train_dir[100];
	strcpy(_train_dir,TD.train_dir);
	char _i[100];
	itos(i,_i);
	strcat(_train_dir,_i);
	strcat(_train_dir,".csv");
    

    CSV_handler csv(_train_dir, TD.price_th);
    cTD[i].dataset = csv.read_csv();
    cTD[i].dataset = csv.labeled(cTD[i].dataset);
    pthread_exit((void*)0);
}


void* calc(void* arg)
{
	long i=(long)arg;
	char _train_dir[100];
	strcpy(_train_dir,TD.train_dir);
	char _i[100];
	itos(i,_i);
	strcat(_train_dir,_i);
	strcat(_train_dir,".csv");

	Classifier cls(_train_dir,cTD[i].dataset ,TD.price_th);

	
	double _res=cls.count_correct();
	

	pthread_mutex_lock (&mutex_sum);

	result.corrects+=_res;
	result._all+=cTD[i].dataset.size();

	pthread_mutex_unlock (&mutex_sum);

	pthread_exit((void*)0);
}

int main(int argc, char* argv[])
{
	// clock_t t1 = clock();

    void *status;
	result.corrects=0;
	result._all=0;
    char _train_dir[100];
	strcpy(_train_dir,argv[1]);
	strcat(_train_dir,"dataset_");
	TD.train_dir=_train_dir;
    TD.price_th = atoi(argv[2]);
    
    pthread_mutex_init(&mutex_sum, NULL);

	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i],NULL,pre_calc,(void*)i); 

	for(int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], &status);

    for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i],NULL,calc,(void*)i); 

	for(int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], &status);

    // cout <<"Time taken: %.2fs  "<< (double)(clock() - t1)<<endl;
    // cout <<" clk per sec"<<CLOCKS_PER_SEC<<endl;
	
	cout<<"Accuracy: ";
	cout<<std::fixed<<std::setprecision(2)<<100*result.corrects/result._all<<"%"<<endl;

	pthread_mutex_destroy(&mutex_sum);
	pthread_exit(NULL);
 
}


