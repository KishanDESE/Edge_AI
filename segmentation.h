#ifndef INFINITE_INPUT_H
#define INFINITE_INPUT_H


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
typedef struct list {
    int node;
    struct list *next;
} list;
typedef struct tree_list {
    int max;
    int min;
    struct tree_list *next;
} tree_list;

extern list *data_head_seg;
extern list *slope_head;
extern tree_list *list_head;
extern int slope_threshold;

void insert_seg(int in);
void insert_seg_slope(int in);
void delete_all();
void diff_calc();
int find_diff(int data_num , float compression);
void merge();
void print_all();
int check_anomaly (int new_data);

#endif /* INFINITE_INPUT_H */
