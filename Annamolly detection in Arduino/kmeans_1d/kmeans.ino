#include <Arduino.h>
#include "kmeans.h"

// Define the number of clusters (k)
const int k = 10;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Generate some sample data for clustering
  int data[] = {397, 867, 214, 512, 693, 146, 245, 916, 326, 714,
    930, 186, 790, 638, 73, 625, 842, 481, 534, 345,
    978, 104, 59, 779, 267, 425, 835, 957, 392, 658,
    920, 263, 539, 123, 795, 372, 668, 167, 873, 421,
    569, 909, 181, 750, 673, 288, 828, 61, 945, 212,
    436, 798, 204, 961, 585, 675, 399, 193, 873, 498,
    125, 739, 290, 847, 540, 687, 82, 934, 396, 281,
    606, 731, 195, 872, 689, 365, 741, 937, 629, 183,
    482, 917, 375, 84, 545, 725, 918, 306, 653, 888,
    281, 643, 189, 929, 277, 489, 791, 347, 699, 47};
  int data_size = sizeof(data) / sizeof(data[0]);



  // Print results if 'y' is received from serial monitor
        while (true) {
                if (Serial.available() > 0) {
                        char receivedChar = Serial.read(); // Read the incoming byte
                        if (receivedChar == 'y') {
                                Serial.println("Received 'y'. Proceeding with setup...");
                                break; // Break the loop to continue with the rest of setup
                        }
                }
        }
  
  // Insert data points into the linked list
  for (int i = 0; i < data_size; i++) {
    insert_seg(data[i]);
  }

  int random_centroid[k];
  for(int i = 0; i < k ; i++)
  {
    random_centroid[i]= getRandomOutput();
    Serial.println("X-X-X-X-X-X");
    Serial.print("Random centroid Points:");
    Serial.println(random_centroid[i]);
  }

  // Perform clustering
  int* labels = findClusters(random_centroid, k);

Serial.println("X-X-X-X-X-X");
      Serial.print("Data Points:");
      for (int i = 0; i < data_size; i++) {
        Serial.print(data[i]);
        Serial.print("\tCluster: ");
        Serial.println(labels[i]);}
      

      // Find centroids
      int * centroids;
      centroids = findCentroid(labels, k);


  for(int i = 0; i < k ; i++)
  {
    Serial.println("X-X-X-X-X-X------------------->>>>>>>>>>>>>");
    Serial.print("New centroid Points:");
    Serial.println(centroids[i]);
  }

      // Perform clustering
      int* k_means_labels = findClusters(centroids, k);

      Serial.println("After Mean clustering --------------->:");
      // Print results
      Serial.println("Data Points:");
      for (int i = 0; i < data_size; i++) {
        Serial.print(data[i]);
        Serial.print("\tCluster: ");
        Serial.println(k_means_labels[i]);
      }


int* best_centroids = findBetterCentroid(100,k);
int receivedInt=0;
      
while(1) {
      Serial.println("\Please enter your data to check : ");
      // Detect anomalies
      while(1){
        if (Serial.available() > 0) {
            receivedInt = Serial.parseInt(); // Read the incoming integer
        }
        if(receivedInt != 0)
        break;
      }   
      int out = findanomaly(best_centroids, k, receivedInt);
      if (out == 0) {
        Serial.println("\Anomaly detected.");
      } else {
        Serial.print("\nNo Anomaly detected It is in cluster: ");
        Serial.println(out);
      }}
    
}

void loop() {
  // Nothing to do in the loop for this example
}
