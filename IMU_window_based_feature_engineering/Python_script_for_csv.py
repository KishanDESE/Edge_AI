import serial
import csv
from time import sleep


ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
sleep(2)

with open('data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)

    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                if line:
                    data = line.split(',')
                    writer.writerow(data)
                    print(f"Data written to CSV: {data}")
    except KeyboardInterrupt:
        print("Program terminated by user")
    finally:
        ser.close()


