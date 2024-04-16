#include "Infinite_input.h"


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



list * mean = NULL;

int data_no=21;



int* list_to_array (list *head,int size){
    int* arr = new int[size];
    list * temp = head;
    int i =0;
    while(temp != NULL)
    {
       arr[i] = temp -> node;
       i++;
       temp = temp ->next;
    }
    return arr;
}

int * dynamic_time_wrapping (int *input, int *pattern) {
    
    int *out = new int[2];
    out[1] =0;
        //     Create data_no*data_no matrix
        int matrix[data_no][data_no];
        //First row and column is max to be putted
        for (int i =0 ; i<data_no ;i++)
        matrix[i][0] = 5000;
        
        
        
        for(int i =0 ; i<(data_no)  ;i++)
        matrix[0][i] = 5000;
        
        matrix[0][0] = 0;
        
        for(int i = 1 ; i <data_no ; i++)
        {
            for(int j = 1; j < data_no  ; j++ )
            {
                
                matrix[i][j] = abs(pattern[i] - input[j]) + min(min(matrix[i-1][j],matrix[i][j-1]),matrix[i-1][j-1]);
                out[1] = out[1] + matrix[i][j];
            }
            
        }
        out[0] = matrix[data_no-1][data_no -1];
    
        
        return out;
    
}
