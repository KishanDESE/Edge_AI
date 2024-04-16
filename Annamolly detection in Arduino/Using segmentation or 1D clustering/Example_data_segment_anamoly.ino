
#include "segmentation.h"

int sourceValues[] = {    
    397, 867, 214, 512, 693, 146, 245, 916, 326, 714,
    930, 186, 790, 638, 73, 625, 842, 481, 534, 345,
    978, 104, 59, 779, 267, 425, 835, 957, 392, 658,
    920, 263, 539, 123, 795, 372, 668, 167, 873, 421,
    569, 909, 181, 750, 673, 288, 828, 61, 945, 212,
    436, 798, 204, 961, 585, 675, 399, 193, 873, 498,
    125, 739, 290, 847, 540, 687, 82, 934, 396, 281,
    606, 731, 195, 872, 689, 365, 741, 937, 629, 183,
    482, 917, 375, 84, 545, 725, 918, 306, 653, 888,
    281, 643, 189, 929, 277, 489, 791, 347, 699, 47}
;


void setup() {
  Serial.begin(9600);
      for (int i = 0; i < 100; i++) {
        insert_seg(sourceValues[i]);
    }
    diff_calc ();
    find_diff(100 , 90);
    merge();
    // Print the linked list
    print_all();
    delete_all();

}

void loop() {
    
    while (!Serial.available()) {} // Wait until data is available
    int new_data = Serial.parseInt(); // Read integer from Serial
    
int do_led_ON;
if(new_data > 0){
  Serial.println("New data :");Serial.println(new_data);
  do_led_ON = check_anomaly (new_data);}
if(do_led_ON)
Serial.println("NO ANOMALIES FOUND ");

}
