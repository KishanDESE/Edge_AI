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

//Data storing 
typedef struct list 
{
        data_type_input node;
        struct list * next;
}
list;

list * data_head = NULL;

void insert(data_type_input in , list * & head) 
{
        list * temp = head;
        list * nt = (list * ) malloc(sizeof(list)); // Use of malloc in C++
        nt -> node = in;
        nt -> next = NULL;

        //calculating all features can not be done here as data number is unknown

        if (head == NULL) {
                head = nt;
        } else {
                while (temp -> next != NULL)
                        temp = temp -> next;

                temp -> next = nt;
        }
}

data_type_input getFreeMemory() 
{
        data_type_input dummy;
        data_type_input free_memory;

        data_type_input * heap_start = (data_type_input * ) malloc(sizeof(data_type_input));
        data_type_input * heap_end = & dummy;

        free_memory = (data_type_input)( & dummy - heap_start);

        free(heap_start);

        return free_memory;
}

int collection_data(data_type_input( * input)(), int diff, int min_allowed , int max_allowed) 
{

        int data_no = 0;
        int prev = -49999;
        Serial.begin(9600);

        while (!Serial) {
                Serial.println("Please type 'y' to proceed with setup.");
        }

        Serial.println("Please type 'y' to proceed with setup.");

        // Wait for 'y' to be received
        while (true) {
                if (Serial.available() > 0) {
                        char receivedChar = Serial.read(); // Read the incoming byte
                        if (receivedChar == 'y') {
                                Serial.println("Received 'y'. Proceeding with setup...");
                                break; // Break the loop to continue with the rest of setup
                        }
                }
        }
        Serial.println("At max number of data can be stored = ");
        data_type_input space_left = abs(getFreeMemory());
        Serial.println(space_left);
        Serial.println("Type 'Y' to collect data data");

  Serial.println("Welcome to Dynamic_time_wraping.h library");
  Serial.println("");
  Serial.println("Time");
  Serial.println(" ^");
  Serial.println(" |       *                      *             *             ");
  Serial.println(" |          *                    *              *           ");
  Serial.println(" |       *                      *             *             ");
  Serial.println(" |                                                          ");
  Serial.println(" |       *                    *               *             ");
  Serial.println(" |       *  <---Similiar--->   *                     *      ");
  Serial.println(" |                                                          ");
  Serial.println(" |     *                    *                       *       ");
  Serial.println(" |                                                          ");
  Serial.println(" | *        <-----Dis-similiar data Anomaly------>          ");
  Serial.println(" |                      *                                   ");
  Serial.println(" |  *                     *                          *      ");
  Serial.println(" |    *                     *                          *    ");
  Serial.println(" |*                      *                             *    ");
  Serial.println(" +----------------------------------------------->Data");
  Serial.println("Write your new time series data, this liabrary will find out similiarity with initial data");
        
        // Wait for 'Y' to be received
        while (true) {
                if (Serial.available() > 0) {
                        char receivedChar = Serial.read(); // Read the incoming byte
                        if (receivedChar == 'Y') {
                                Serial.println("Received 'Y'. Proceeding with input...");
                                break;
                        }
                }
        }
        Serial.println("Press '99999'. To stop input...***********************");
        Serial.println(" ");
        while (true) {

//               if (Serial.available() > 0)
//                   {
//                     char receivedChar = Serial.read();  // Read the incoming byte
//                     if (receivedChar == 's')
//                     {
//                       Serial.println("Received 's'. Starting training with input...");
//                       break; 
//                     }
//                   }
                   
                int in = input();
//                Serial.print("\nData received == ");
//                Serial.println(in);
                if(in == 99999)
                break;
                else if (in > min_allowed && max_allowed > in) {
                 if (abs(prev-in) >= diff){
                 insert(in, data_head);
                 prev = in;
                 Serial.println("New data no : ");
                         Serial.print(data_no);
                         Serial.print(" : ");
                         Serial.print("Data inserted == ");
                         Serial.print(in);
                 Serial.println("\n<------------------*******************---------------->");
                 data_no++;
                 }}
        }
        return (data_no);
}
