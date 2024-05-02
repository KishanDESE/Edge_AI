


//////////////////////////////////////////////////////////////////////////////////
// University: Indian Institute of science 
// Course: Edge AI
// 
// Create Date: 02.05.2024 05:17:59
// Design Name: Anomaly detection using dynamic time wrapping and 1D kmeans
// Module Name: Example_code_for_IMU_dtw_kmeans
// Project Name: Anomaly detection liabrary
// Target Devices: Arduino uno, ble, edge, devices
// Description: 
// This liabrary do 1 D time series data similiarity calculation.
// Edge devices can be trained to detect anomalous time series data by help of this example.
//
// Dependencies: Arduino liabrary (However seprate c++ code is also provided in github)
// 
// Revision:
// Please provide suggestions or modifications as necessary, whether made by yourself or anyone else using the library
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////



#include "Infinite_input.h"
//For unknown number of time series data
#include "Dynamic_time_wrapping.h"
//For time series data similiarity
#include "kmeans.h"
//For performing kmeans in 1D
#include <Arduino_LSM9DS1.h>
//For IMU data


extern int data_no;

// Example : Function to get data from IMU sensor
int Example_data_input() { 
  float x,y,z;
    if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x,y,z);   
    int output;
    if(x)
      output = x*100;
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    return output;
    }
    else return 0;
}



int DATA_NO =0;
int* best_centroids;
int k =3; //Number of clusters in kmeans


void setup() {
  Serial.begin(9600);
            if (!IMU.begin()) {
              Serial.println("Failed to initialize IMU!");
              while (1);
            }
          
            Serial.print("Accelerometer sample rate = ");
            Serial.print(IMU.accelerationSampleRate());
            Serial.println(" Hz");
            Serial.println();
            Serial.println("Acceleration in g's");
            Serial.println("X\tY\tZ");
int (*ptr)() = &Example_data_input;

//Collection of data
//               function pointer, min -max allowed, number of data points

DATA_NO =  collection_data(ptr, 0, -50000, 50000, 100);


// Can be modified with any digital pin for enabling data collection for unknown number of inputs



// Training with 100 out of order data

for (int i = 0; i < 30;){

  
  float progress = i/30.0*100.0;
  Serial.print("k-MEANS data collection : ");Serial.print(progress);Serial.println("###########################################################");

//Dynamic time wrapping-----------------------------------------------------------------------------------------------------------------------------------------------------------
          int *pattern = list_to_array(data_head,DATA_NO);
          int (*ptr)() = &Example_data_input;
          for(int i =0; i<data_no; i++)
          {
             Serial.print( i );Serial.print( " : " );Serial.println( pattern[i] );
          }
          Serial.println(" ");
          
          int* newArray = new_input(ptr);
          
          int * out = dynamic_time_wrapping(newArray,pattern);
              
          
              Serial.print( " Value of DTW : ");Serial.print(" : "); Serial.println( out[0]);
              Serial.print( " Mean of DTW MATRIX : ");Serial.print(" : "); Serial.println( out[1]);
          
          int threshold_anomaly = 20;
              if(out[0] > threshold_anomaly){


//DTW detected anomalies passed to kmeans--------------------------------------------------------------------------------------------------------------------------------------


              Serial.println( " ANOMALY DETECTED LEVEL1__________________>>>>>>>>>>>>>>>>>>>>>>>");
              insert_seg(out[0]);
              i++;
              }
              else
              Serial.println( " ANOMALY NOT DETECTED ______________XXXXXXXXXXXXXXXXXXXXXXX");
          
            // Free memory allocated for the newArray and pattern
            delete[] newArray;
            delete[] pattern;
    
}


//kmeans calculations --------------------------------------------------------------------------------------------------------------------------------------------------

  int random_centroid[k];
  for(int i = 0; i < k ; i++)
  {
    random_centroid[i]= getRandomOutput();
    Serial.println("X-X-X-X-X-X");
    Serial.print("Random centroid Points:");
    Serial.println(random_centroid[i]);
  }


// Perform clustering based on random centroid -------------------------------------------------------------------------------------------------------------------------
  int* labels = findClusters(random_centroid, k);

// Find centroids according to mean of clusters -------------------------------------------------------------------------------------------------------------------------
  int * centroids;
  centroids = findCentroid(labels, k);


  for(int i = 0; i < k ; i++)
  {
    Serial.println("X-X-X-X-X-X------------------->>>>>>>>>>>>>");
    Serial.print("New centroid Points:");
    Serial.println(centroids[i]);
  }

// Perform clustering using new calculated centroid --------------------------------------------------------------------------------------------------------------------
      int* k_means_labels = findClusters(centroids, k);

      
//Perform error correction using itterative clustering according to better variance--------------------------------------------------------------------------------------
      best_centroids = findBetterCentroid(100,k);

Serial.println("k-MEANS WAS SUCCESSFULL NOW YOU CAN TEST DEVICE ###################################");
}

void loop() {
delay(700);

          int *pattern = list_to_array(data_head,DATA_NO);
          int (*ptr)() = &Example_data_input;
          for(int i =0; i<data_no; i++)
          {
             Serial.print( i );Serial.print( " : " );Serial.println( pattern[i] );
          }
          Serial.println(" ");
          
          int* newArray = new_input(ptr);
          
          int * out = dynamic_time_wrapping(newArray,pattern);
              
          
              Serial.print( " Value of DTW : ");Serial.print(" : "); Serial.println( out[0]);
              Serial.print( " Mean of DTW MATRIX : ");Serial.print(" : "); Serial.println( out[1]);
          
          int threshold_anomaly = 20;
              if(out[0] > threshold_anomaly){
              Serial.println( " ANOMALY DETECTED LEVEL1__________________>>>>>>>>>>>>>>>>>>>>>>>");
                            Serial.println("\Your new data to check : "); 
                            int output_k_mean = findanomaly(best_centroids, k, out[0]);
                            if (output_k_mean == 0) {
                              Serial.println("\Anomaly detected @ LEVEL 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                            } else {
                              Serial.print("\nNo Anomaly detected It is in cluster: ");
                              Serial.println(output_k_mean);
                            }
              }
              else
              Serial.println( " ANOMALY NOT DETECTED ______________XXXXXXXXXXXXXXXXXXXXXXX");
          
            // Free memory allocated for the newArray and pattern
            delete[] newArray;
            delete[] pattern;
            
  


}
