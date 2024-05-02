
#ifndef KMEANS_H
#define KMEANS_H


//////////////////////////////////////////////////////////////////////////////////
// University: Indian Institute of science 
// Course: Edge AI
// 
// Create Date: 16.04.2024 07:17:59
// Design Name: Anomaly detection using segmentation
// Module Name: segmentation.h
// Project Name: Anomaly detection liabrary
// Target Devices: Arduino uno, ble, edge, devices
// Description: 
// This liabrary do 1 D clustering using segmentation.
// Edge devices can be trained to detect anomalous data by using this liabrary.
//
// Dependencies: Arduino liabrary (However seprate c++ code is also provided in github)
// 
// Revision:
// Please provide suggestions or modifications as necessary, whether made by yourself or anyone else using the library
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////



#include <Arduino.h>

// Define constants
extern int data_no_kmeans;
extern int threshold_anomaly;


// Define structures
typedef struct list_kmeans  {
    int node;
    struct list_kmeans *next;
} list_kmeans ;

// Function declarations
void insert_seg(int in);
int randomRange(int min, int max);
int getRandomOutput();
int* findClusters(int points[], int k);
int* findCentroid(int labels[], int k);
int* findBetterCentroid(int itterate, int k);
int findanomaly(int points[], int k, int x);

#endif // KMEANS_H
