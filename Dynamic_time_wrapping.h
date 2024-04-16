#ifndef DTW_FUNCTIONS_H
#define DTW_FUNCTIONS_H

//////////////////////////////////////////////////////////////////////////////////
// University: Indian Institute of science 
// Course: Edge AI
// 
// Create Date: 16.04.2024 07:17:59
// Design Name: Anomaly detection using dynamic time wrapping
// Module Name: Dynamic_time_wrapping.h
// Project Name: Anomaly detection liabrary
// Target Devices: Arduino uno, ble, edge, devices
// Description: 
// This liabrary do 1 D time series data similiarity calculation.
// Edge devices can be trained to detect anomalous time series data by using this liabrary.
//
// Dependencies: Arduino liabrary (However seprate c++ code is also provided in github)
// 
// Revision:
// Please provide suggestions or modifications as necessary, whether made by yourself or anyone else using the library
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


#include "Infinite_input.h"

extern list* data_head;

int* list_to_array(list* head, int size);
int* dynamic_time_wrapping(int* input, int* pattern);


#endif // DTW_FUNCTIONS_H
