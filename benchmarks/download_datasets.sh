#!/bin/bash

remove_empty_lines () {
    awk 'NF' ${1} > ${1}.tmp && mv ${1}.tmp ${1} 
}

# iris dataset
wget https://archive.ics.uci.edu/ml/machine-learning-databases/iris/bezdekIris.data -O iris/bezdekIris.data
remove_empty_lines iris/bezdekIris.data

# adult dataset
wget https://archive.ics.uci.edu/ml/machine-learning-databases/adult/adult.data -O adult/adult.data
remove_empty_lines adult/adult.data

# wine dataset
#wget https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data -O wine/wine.data
#remove_empty_lines wine/wine.data

# car dataset
#wget https://archive.ics.uci.edu/ml/machine-learning-databases/car/car.data -O car/car.data
#remove_empty_lines car/car.data

# forest fires dataset
#wget https://archive.ics.uci.edu/ml/machine-learning-databases/forest-fires/forestfires.csv -O forestfires/forestfires.csv
#remove_empty_lines forestfires/forestfires.csv

# breast cancer wisconsin data set
#wget https://archive.ics.uci.edu/ml/machine-learning-databases/breast-cancer-wisconsin/wdbc.data -O breast-cancer-wisconsin/wbdc.data
#remove_empty_lines breast-cancer-wisconsin/wbdc.data
