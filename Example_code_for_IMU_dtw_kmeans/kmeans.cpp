#include <Arduino.h>


//////////////////////////////////////////////////////////////////////////////////
// University: Indian Institute of science 
// Course: Edge AI
// 
// Create Date: 16.04.2024 07:17:59
// Design Name: Anomaly detection using kmeans
// Module Name: kmeans.h
// Project Name: Anomaly detection liabrary
// Target Devices: Arduino uno, ble, edge, devices
// Description: 
// This liabrary do 1 D clustering using kmeans.
// Edge devices can be trained to detect anomalous data by using this liabrary.
//
// Dependencies: Arduino liabrary (However seprate c++ code is also provided in github)
// 
// Revision:
// Please provide suggestions or modifications as necessary, whether made by yourself or anyone else using the library
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

int data_no_kmeans = 0;
int threshold_anomaly = 0;


typedef struct list_kmeans {
    int node;
    struct list_kmeans *next;
} list_kmeans;


list_kmeans *data_head_seg = NULL;
list_kmeans *label_head = NULL;

// Function to insert_seg a new input in the sorted linked list_kmeans--------------------------------------------------------------------------------------------------------------------------
void insert_seg(int in) {
    data_no_kmeans ++;
    list_kmeans *temp = data_head_seg;
    list_kmeans *nt = (list_kmeans*)malloc(sizeof(list_kmeans)); // Use of malloc in C++
    nt->node = in;
    
    // If the list_kmeans is empty or the new element is smaller than the head
    if (data_head_seg == NULL || in < data_head_seg->node) {
        nt->next = data_head_seg;
        data_head_seg = nt;
        
    } else {
        list_kmeans *dumy;
        dumy = temp->next;
        // Traverse the list_kmeans to find the correct position to insert_seg
        while (temp->next != NULL && in > dumy->node) {
            temp = temp->next;
            dumy = temp->next;
        }
        nt->next = temp->next;
        temp->next = nt;
    }
    
    
}





// Function to generate a random number within a specified range--------------------------------------------------------------------------------------------------------------------------
int randomRange(int min, int max) {
  return min + rand() % (max - min + 1);
}

// Function to generate a random output from the linked list_kmeans-------------------------------------------------------------------------------------------------------------------
int getRandomOutput() {

  // Generate a random index within the range of the list_kmeans
  int randomIndex = randomRange(1, data_no_kmeans - 1);
  
  // Traverse the list_kmeans to the randomly selected node
  list_kmeans *current = data_head_seg;
  for (int i = 0; i < randomIndex; i++) {
    current = current->next;
  }
  
  // Return the data of the randomly selected node
  return current->node;
}


// Function to find the clusters according to minimum distance from centroid array input to a given point--------------------------------------------------------------------------------------------------
int* findClusters(int points[], int k) {
    int minDistance = 50000;
    int minPoint;
    int* labels = new int[data_no_kmeans]; // Allocate memory for the array

    list_kmeans* current = data_head_seg;
    for (int i = 0; i < data_no_kmeans; i++) {
        minDistance = 50000; // Reset minDistance for each iteration
            for (int j = 0; j < k; j++) { // Changed loop variable to 'j'
                int distance = abs(points[j] - current->node); // Compute distance
               
                if (distance < minDistance) {
                    minDistance = distance;
                    minPoint = points[j];
                }
            }
            
        labels[i] = minPoint; // Assign minPoint to labels array
        threshold_anomaly = max(minDistance,threshold_anomaly); 
        current = current->next;
    }
    return labels;
}

// Function to find the clusters centroid according to mean-------------------------------------------------------------------------------------------------------------------------------------
int* findCentroid(int labels[], int k) {
    list_kmeans* current = data_head_seg;
    int current_label = labels[0];
    int* new_centroids = new int[k]; // Dynamically allocate memory for new centroids
    memset(new_centroids, 0, sizeof(int) * k); // Initialize new_centroids array to 0
    int l = 0;
    int cnt_avg = 0;
    for (int i = 0; i < data_no_kmeans; i++) { // Declare loop variable i
        if (current_label == labels[i]) {
            new_centroids[l] += current->node;
            cnt_avg++;
        } else {
            new_centroids[l] /= cnt_avg; // Calculate average for the centroid
            l++;
            current_label = labels[i];
            cnt_avg = 1;
        }
        current = current->next;
    }
    new_centroids[l] /= cnt_avg; // Calculate average for the last centroid
    return new_centroids;
}





// Function to find the better clusters centroid according to random centroid selection and minimum variance -------------------------------------------------------------------------------------------------------------------------------------
int* findBetterCentroid(int itterate, int k) {

int* best_centroids = new int[k]; // Dynamically allocate memory for variance calculation.
memset(best_centroids, 0, sizeof(int) * k); // Initialize new_centroids array to 0
  
for (int n =0 ; n< itterate ; n++)
{
  int random_centroid[k];
  for(int i = 0; i < k ; i++)
  {
    random_centroid[i]= getRandomOutput();
  }


    // Perform clustering
  int* labels = findClusters(random_centroid, k);

      

  // Find centroids
  int * centroids;
  centroids = findCentroid(labels, k);

  // Perform clustering
  int* k_means_labels = findClusters(centroids, k);

      
  
    list_kmeans* current = data_head_seg;
    int current_label = k_means_labels[0];
    int cluster_variance;
    int min_cluster_variance = 50000;
    int cnt_avg = 0;
    for (int i = 0; i < data_no_kmeans; i++) { // Declare loop variable i
        if (current_label == k_means_labels[i]) {
            cluster_variance = cluster_variance + (current->node - k_means_labels[i])*(current->node - k_means_labels[i]);
            cnt_avg++;
        } else {
            cluster_variance /= cnt_avg; 
            current_label = k_means_labels[i];
            cnt_avg = 1;
        }
        current = current->next;
    }
    cluster_variance /= cnt_avg; // Calculate average for the last centroid
    
    if(cluster_variance < min_cluster_variance)
    {
      for(int i =0; i<k; i++)
      {
        best_centroids[i] = centroids[i]; 
      }
    }

        delete[] centroids;
        delete[] labels;
        delete[] k_means_labels;

}
    return best_centroids;
}


// Function to find the minimum distance from cluster centroids to a given point-------------------------------------------------------------------------------------------------------------------
int findanomaly(int points[], int k, int x) {
    int minDistance = 50000;
    int minPoint;
    
        for (int j = 0; j < k; j++) { // Changed loop variable to 'j'
            int distance = abs(points[j] - x); // Compute distance
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = points[j];
            }
        }
        if(minDistance > 50) 
        return 0;
        else 
        return minPoint;
}
