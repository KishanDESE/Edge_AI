#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <Arduino.h>

#ifndef data_type_input
#define data_type_input int
#endif

//////////////////////////////////////////////////////////////////////////////////
// University: Indian Institute of science 
// Course: Edge AI
// 
// Create Date: 16.04.2024 07:17:59
// Design Name: infinite_input.h
// Module Name: Anamoly detection using Dynamic time wrapping
// Project Name: Anomaly detection liabrary
// Target Devices: Arduino uno, ble, edge, devices
// Description: 
// This liabrary take any number of (allowed to store) inputs.
// Edge devices use this liabrary for collecting unknown number of time series data.
//
// Dependencies: Arduino liabrary (However seprate c++ code is also provided in github)
// 
// Revision:
// Please provide suggestions or modifications as necessary, whether made by yourself or anyone else using the library
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


// Define the structure for the linked list node
typedef struct list {
    data_type_input node;
    struct list* next;
} list;

// Declare the global head pointer for the linked list
extern list* data_head;

// Function to insert a new node into the linked list
void insert(data_type_input in, list* &head);

// Function to get the free memory
data_type_input getFreeMemory();

// Function to collect data from serial input and store it in the linked list
int collection_data(data_type_input (* input)(), int diff, int min_allowed , int max_allowed, int max_inputs);

#endif
