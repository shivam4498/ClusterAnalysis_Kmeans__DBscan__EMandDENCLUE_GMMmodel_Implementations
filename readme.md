# Clustering Analysis Algorithms
## Implementations
* ```K-Means``` Algorithm
* ```DB-Scan``` Density based apatial clustering of applications with Noise
* ```EM-Algo``` Expection Maximization Algorithm
* ```Denclue``` Density based clustering

## Dataset Links
* [Iris Dataset](https://archive.ics.uci.edu/ml/datasets/iris)
* [Spiral Dataset](https://github.com/milaan9/Clustering-Datasets)

## RUN Commands
```K-Means_DBscan.cpp```
## Input
------------
* Step-1. keep The input datasetfile within the same folder and set the file
name in takeinputdataset() function (on the top of the code).
* step-2. choose the value of the number of cluster and set on the top of the code
#define k 
* step-3. set maxDBesp (range for the density based clustering) value on the top(#define maxDBeps).
* Run the ```K-Means_DBscan.cpp``` file in c++ compiler.

## output
-----------------------
* you will get Final Expectations(mean) with the total number of clusters .
* It will also generate one output.txt file in the same
directory having all the clusters with their corresponding datapoints.

```EM-Algo_Denclue.py```
* Note Please use the ```jupyter notebook``` for better visualisation of the 
graph and to support all the matplotlib module in the code.
## Input:
--------------------
* Step1.  keep The input datasetfile within the same folder and set the file
name in file1 = open("irisdataset.txt") (on the top of the code).
* step2. set the Dimension as you want (by default dim = 2 on the top of the code)
Run file EM-Algo_Denclue.py
## Output:
---------------------------
* you will get Dataset Estimated parameters **Mean** , **Covariance Matrices** and **Probability** for each cluster in your console.
* Than it will ask you to show the graph.
for EM-Algo press-1
for Denclue Press-2
press-1/2 (correspondingly)
you will get the graph in your console(for that use ```jupyter notebook``` )

Refer ```DetailedReport.txt``` for the detailed analysis and comparison of the algorithms over particular shape distribution dataset.



