#include "Infinite_input.h"
#include "dynamic_time_wrapping.h"



// Example : Function to get distance from ultrasonic sensor
int getDistance() {
                        int received_input = Serial.parseInt(); 
                        return (received_input);
}

int DATA_NO =0;

void setup() {
int (*ptr)() = &getDistance;
DATA_NO =  collection_data(ptr, 0, 0, 50);
Serial.print("Number of input");
Serial.println(DATA_NO);
}

void loop() {

int *pattern = list_to_array(data_head,DATA_NO);

for(int i =0; i<DATA_NO; i++)
{
   Serial.print( i );Serial.print( " : " );Serial.println( pattern[i] );
}
Serial.println(" ");

  Serial.println("Please enter the time series data that you want to compare.");


    Serial.println("Write size of time series");
    while (!Serial.available()) {} // Wait until data is available
    int Size_of_comparing_data = Serial.parseInt(); // Read integer from Serial
    Serial.println(Size_of_comparing_data);
    

int myArray[Size_of_comparing_data];
    for (int i = 0; i < Size_of_comparing_data; i++) {
    while (!Serial.available()) {} // Wait until data is available
    myArray[i] = Serial.parseInt(); // Read integer from Serial
    Serial.println(myArray[i]);
    while (Serial.read() != '\n') {} // Clear remaining data in Serial buffer
  }

int * out = dynamic_time_wrapping(myArray,pattern);
    

    Serial.print( " Value of DTW : ");Serial.print( i); Serial.print(" : "); Serial.println( out[0]);
    Serial.print( " Mean of DTW MATRIX : ");Serial.print( i); Serial.print(" : "); Serial.println( out[1]);

int threshold_anomaly = 100;
    if(out[0] > threshold_anomaly)
    Serial.print( " ANOMALY DETECTED __________________>>>>>>>>>");
    else
    Serial.print( " ANOMALY NOT DETECTED __________________>>>>>>>>>");

}
