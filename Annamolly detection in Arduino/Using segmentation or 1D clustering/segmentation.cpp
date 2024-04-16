#include <Arduino.h>
#include <iostream>
#include <cstdlib>

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

int data_no = 0;
int tree_num =0;

int slope_threshold;

typedef struct list {
    int node;
    struct list *next;
} list;
typedef struct tree_list {
    int max;
    int min;
    struct tree_list *next;
} tree_list;


list *data_head_seg = NULL;
list *slope_head = NULL;
tree_list *list_head = NULL;

// Function to insert_seg a new input in the sorted linked list
void insert_seg(int in) {
    list *temp = data_head_seg;
    list *nt = (list*)malloc(sizeof(list)); // Use of malloc in C++
    nt->node = in;
    
    // If the list is empty or the new element is smaller than the head
    if (data_head_seg == NULL || in < data_head_seg->node) {
        nt->next = data_head_seg;
        data_head_seg = nt;
        
    } else {
        list *dumy;
        dumy = temp->next;
        // Traverse the list to find the correct position to insert_seg
        while (temp->next != NULL && in > dumy->node) {
            temp = temp->next;
            dumy = temp->next;
        }
        nt->next = temp->next;
        temp->next = nt;
    }
    
    
}

// Function to insert_seg a new input in the sorted linked list
void insert_seg_slope(int in) {
    list *temp = slope_head;
    list *nt = (list*)malloc(sizeof(list)); // Use of malloc in C++
    nt->node = in;
    
    // If the list is empty or the new element is smaller than the head
    if (slope_head == NULL || in < slope_head->node) {
        nt->next = slope_head;
        slope_head = nt;
        
    } else {
        list *dumy;
        dumy = temp->next;
        // Traverse the list to find the correct position to insert_seg
        while (temp->next != NULL && in > dumy->node) {
            temp = temp->next;
            dumy = temp->next;
        }
        nt->next = temp->next;
        temp->next = nt;
    }
    
    
}

// Function to delete all nodes and free dynamically allocated memory
void delete_all() {
    list *current = data_head_seg;
    list *next;
    while (current != NULL) {
        next = current->next;
        free(current); // Free the current node
        current = next;
    }
    data_head_seg = NULL; // Set the head pointer to NULL after deletion
}

void diff_calc (){ //mean median mode all can be calculated
    list *temp = data_head_seg;
    while (temp->next != NULL){
            insert_seg_slope ((temp->next->node - temp->node) );
            temp=temp->next;
    }
}

int find_diff (int data_num , float compression) {
    list *temp =slope_head;
    slope_threshold;
    float data_compression_float = (compression/100.0)*(data_num-1);
	int data_compression = ( int )data_compression_float;
    while (temp != NULL ){

            
            if(data_compression > 0)
            slope_threshold = temp->node;
            data_compression--;
            
            
        slope_head=temp->next;
        free(temp);
        temp = slope_head;
    }
    return (slope_threshold);
}

void merge (){
    list *data = data_head_seg;
    list *data_next = data_head_seg->next;
    tree_list *tree_node = (tree_list*)malloc(sizeof(tree_list));
    list_head=tree_node;
    tree_node->min=data_head_seg->node;
    tree_node->max=data_head_seg->node;
    while(data_next != NULL){
    if((data_next -> node - data -> node) < slope_threshold)
    {tree_node->max = data_next->node;
    }
    else
    {
    tree_list *tree_node_next = (tree_list*)malloc(sizeof(tree_list));
    tree_node->next=tree_node_next;
        tree_node =tree_node->next;
        tree_node->min =data_next->node; 
        tree_node->max=data_next->node;
    }
    data = data -> next;
    data_next = data_next->next;
    }
    
    
}
// Function to print all elements of the linked list
void print_all() {
    Serial.println("Linked list is: ");
    list *temp = data_head_seg;
    tree_list *tp = list_head;
        while (true) {
                if (Serial.available() > 0) {
                        char receivedChar = Serial.read(); // Read the incoming byte
                        if (receivedChar == 'y') {
                                Serial.println("Received 'y'. Proceeding with setup...");
                                break; // Break the loop to continue with the rest of setup
                        }
                }
        }
	Serial.println("Linked list is: ");
    while (temp != NULL) {
        Serial.print("Node: ");Serial.println(temp->node);
	delay(100);
        temp = temp->next;
    }
    Serial.print("Upto this difference is ignored :");Serial.println(slope_threshold);
	
        while (tp->next != NULL) {
        Serial.print(tree_num);Serial.print(" : Tree Node min: ");Serial.print(tp->min);Serial.print("Tree Node max: ");Serial.println(tp->max); 
	delay(100);
        tp = tp->next;
	tree_num++;
    }
  // Print the time series graph
  Serial.println("Welcome to segmentation.h library");
  Serial.println("");
  Serial.println("Time");
  Serial.println(" ^");
  Serial.println(" |       *                                            ");
  Serial.println(" |          *                                         ");
  Serial.println(" |       *                                            ");
  Serial.println(" |                              *                     ");
  Serial.println(" |       *                                            ");
  Serial.println(" |                            *                       ");
  Serial.println(" |                                *                   ");
  Serial.println(" |                              *                     ");
  Serial.println(" |                                  *                 ");
  Serial.println(" | *                                                  ");
  Serial.println(" |                  * <----------Anomalous data Found ");
  Serial.println(" |  *                                                 ");
  Serial.println(" |    *                                               ");
  Serial.println(" |*                                                   ");
  Serial.println(" +----------------------------------------------->Data");
  Serial.println("Write your new data, this liabrary will find out of cluster datas from trained data");

}

int check_anomaly (int new_data){
tree_list *tp = list_head;
int count_tree = tree_num;
        while (tp->next != NULL) {
	
	if((tp->min - slope_threshold )< new_data && ( tp->max + slope_threshold ) > new_data){
	Serial.print(new_data);Serial.print(" : is in near RANGE OF Tree Node min: ");Serial.print(tp->min);Serial.print("Tree Node max: ");Serial.println(tp->max); 
	return(1);
	}
        tp = tp->next;
	count_tree--;
    }
if(count_tree < 1)
{
Serial.print("ALERT THIS DATA IS ANOMALY :");Serial.print(new_data);Serial.print("sending to server");
return 0;
}
else return 1;
}


