# HousePricePrediction-OS

## Serial:
read CSV files.\
labeling the SalePrice row, 0 for cheap and 1 for expensive.\
  (the price threshold is given as a command input.)\
classifying.\
calculate the accuracy.

all above operations are done seauentially.

## Parallel:
read CSV files.\
labeling the SalePrice row, 0 for cheap and 1 for expensive.\
  (the price threshold is given as a command input.)\
classifying.\
calculate the accuracy.

creating 2 series of threads for each file :
1. reading and labeling data/
2. classifying and calculating accuracy.

each series of threads are performed in parallel.


## Running file in linux
1.make
2../HousePricePrediction AddressofData/ PriceThreshold \
  exp : ./HousePricePrediction dataset/ 330000 
