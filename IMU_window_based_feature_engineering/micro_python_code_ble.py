import time
from machine import Pin, I2C
import lsm9ds1

# Initialize I2C and sensor
bus = I2C(1, scl=Pin(15), sda=Pin(14))
lsm = lsm9ds1.LSM9DS1(bus)

# Initialize 9 sensor variable
Ax = 0.0
Ay = 0.0
Az = 0.0
Gx = 0.0
Gy = 0.0
Gz = 0.0
Mx = 0.0
My = 0.0
Mz = 0.0

#Feature 1 Mean
Ax_MEAN = 0.0
Ay_MEAN = 0.0
Az_MEAN = 0.0
Gx_MEAN = 0.0
Gy_MEAN = 0.0
Gz_MEAN = 0.0
Mx_MEAN = 0.0
My_MEAN = 0.0
Mz_MEAN = 0.0

#Feature 2 Min
Ax_MIN = 5.0
Ay_MIN = 5.0
Az_MIN = 5.0
Gx_MIN = 5.0
Gy_MIN = 5.0
Gz_MIN = 5.0
Mx_MIN = 5.0
My_MIN = 5.0
Mz_MIN = 5.0

#Feature 3 Max
Ax_MAX = -5.0
Ay_MAX = -5.0
Az_MAX = -5.0
Gx_MAX = -5.0
Gy_MAX = -5.0
Gz_MAX = -5.0
Mx_MAX = -5.0
My_MAX = -5.0
Mz_MAX = -5.0

#Feature 5 Skewness
Ax_SKEW_T = 0.0
Ay_SKEW_T = 0.0
Az_SKEW_T = 0.0
Gx_SKEW_T = 0.0
Gy_SKEW_T = 0.0
Gz_SKEW_T = 0.0
Mx_SKEW_T = 0.0
My_SKEW_T = 0.0
Mz_SKEW_T = 0.0

#Feature 6 ENERGY
Ax_ENERGY = 0.0
Ay_ENERGY = 0.0
Az_ENERGY = 0.0
Gx_ENERGY = 0.0
Gy_ENERGY = 0.0
Gz_ENERGY = 0.0
Mx_ENERGY = 0.0
My_ENERGY = 0.0
Mz_ENERGY = 0.0

#Feature 7 Average Sum of absolute change of moment 4 for Kurtosis
Ax_SAC = 0.0
Ay_SAC = 0.0
Az_SAC = 0.0
Gx_SAC = 0.0
Gy_SAC = 0.0
Gz_SAC = 0.0
Mx_SAC = 0.0
My_SAC = 0.0
Mz_SAC = 0.0

# Create a buffer with 100 entries
data = [Ax,Ay,Az,Gx,Gy,Gz,Mx,My,Mz]
data_buffer = [data[:] for _ in range(100)]


#Reading sensor
accel = lsm.accel()
gyro = lsm.gyro()
magnet = lsm.magnet()
#First time 100 entries of each sensor
for i in range(100) :

    #Direct data access for better performance
    Ax_MEAN = accel[0]/100 + Ax_MEAN
    Ax_MIN = min(Ax_MIN,accel[0])
    Ax_MAX = max(Ax_MAX,accel[0])
    Ax_ENERGY = Ax_ENERGY + (accel[0] ** 2)

    Ay_MEAN = accel[1]/100 + Ay_MEAN
    Ay_MIN = min(Ay_MIN,accel[1])
    Ay_MAX = max(Ay_MAX,accel[1])
    Ay_ENERGY = Ay_ENERGY + (accel[1] ** 2)

    Az_MEAN = accel[2]/100 + Az_MEAN
    Az_MIN = min(Az_MIN,accel[2])
    Az_MAX = max(Az_MAX,accel[2])
    Az_ENERGY = Az_ENERGY + (accel[2] ** 2)

    Gx_MEAN = gyro[0]/100 + Gx_MEAN
    Gx_MIN = min(Gx_MIN,gyro[0])
    Gx_MAX = max(Gx_MAX,gyro[0])
    Gx_ENERGY = Gx_ENERGY + (gyro[0] ** 2)

    Gy_MEAN = gyro[1]/100 + Gy_MEAN
    Gy_MIN = min(Gy_MIN,gyro[1])
    Gy_MAX = max(Gy_MAX,gyro[1])
    Gy_ENERGY = Gy_ENERGY + (gyro[1] ** 2)

    Gz_MEAN = gyro[2]/100 + Gz_MEAN
    Gz_MIN = min(Gz_MIN,gyro[2])
    Gz_MAX = max(Gz_MAX,gyro[2])
    Gz_ENERGY = Gz_ENERGY + (gyro[2] ** 2)

    Mx_MEAN = magnet[0]/100 + Mx_MEAN
    Mx_MIN = min(Mx_MIN,magnet[0])
    Mx_MAX = max(Mx_MAX,magnet[0])
    Mx_ENERGY = Mx_ENERGY + (magnet[0] ** 2)

    My_MEAN = magnet[1]/100 + My_MEAN
    My_MIN = min(My_MIN,magnet[1])
    My_MAX = max(My_MAX,magnet[1])
    My_ENERGY = My_ENERGY + (magnet[1] ** 2)

    Mz_MEAN = magnet[2]/100 + Mz_MEAN
    Mz_MIN = min(Mz_MIN,magnet[2])
    Mz_MAX = max(Mz_MAX,magnet[2])
    Mz_ENERGY = Mz_ENERGY + (magnet[2] ** 2)

    data_buffer[i][0] = accel[0]
    data_buffer[i][1] = accel[1]
    data_buffer[i][2] = accel[2]
    data_buffer[i][3] = gyro[0]
    data_buffer[i][4] = gyro[1]
    data_buffer[i][5] = gyro[2]
    data_buffer[i][6] = magnet[0]
    data_buffer[i][7] = magnet[1]
    data_buffer[i][8] = magnet[2]

for m in range(100) :
    Ax_SKEW_T = Ax_SKEW_T + ((data_buffer[m][0]-Ax_MEAN)**3 )/ 100
    Ay_SKEW_T = Ay_SKEW_T + ((data_buffer[m][1]-Ay_MEAN)**3 )/ 100
    Az_SKEW_T = Az_SKEW_T + ((data_buffer[m][2]-Az_MEAN)**3 )/ 100
    Gx_SKEW_T = Gx_SKEW_T + ((data_buffer[m][3]-Gx_MEAN)**3 )/ 100
    Gy_SKEW_T = Gy_SKEW_T + ((data_buffer[m][4]-Gy_MEAN)**3 )/ 100
    Gz_SKEW_T = Gz_SKEW_T + ((data_buffer[m][5]-Gz_MEAN)**3 )/ 100
    Mx_SKEW_T = Mx_SKEW_T + ((data_buffer[m][6]-Mx_MEAN)**3 )/ 100
    My_SKEW_T = My_SKEW_T + ((data_buffer[m][7]-My_MEAN)**3 )/ 100
    Mz_SKEW_T = Mz_SKEW_T + ((data_buffer[m][8]-Mz_MEAN)**3 )/ 100
    Ax_SAC = Ax_SAC + (abs(Ax_MEAN-accel[0]))**4/100
    Ay_SAC = Ay_SAC + (abs(Ay_MEAN-accel[1]))**4/100
    Az_SAC = Az_SAC + (abs(Az_MEAN-accel[2]))**4/100
    Gx_SAC = Gx_SAC + (abs(Gx_MEAN-gyro[0]))**4/100
    Gy_SAC = Gy_SAC + (abs(Gy_MEAN-gyro[1]))**4/100
    Gz_SAC = Gz_SAC + (abs(Gz_MEAN-gyro[2]))**4/100
    Mx_SAC = Mx_SAC + (abs(Mx_MEAN-magnet[0]))**4/100
    My_SAC = My_SAC + (abs(My_MEAN-magnet[1]))**4/100
    Mz_SAC = Mz_SAC + (abs(Mz_MEAN-magnet[2]))**4/100
initial_Ax = Ax_MEAN
initial_Ay = Ay_MEAN
initial_Az = Az_MEAN
initial_Gx = Gx_MEAN
initial_Gy = Gy_MEAN
initial_Gz = Gz_MEAN
initial_Mx = Mx_MEAN
initial_My = My_MEAN
initial_Mz = Mz_MEAN
j=0
while True:
    accel = lsm.accel()
    gyro = lsm.gyro()
    magnet = lsm.magnet()
    #Continuous update new sensor data in oldest buffer
    if(j!=100) :
        #Removing old value
        Ax_MEAN = Ax_MEAN - data_buffer[j][0]/100
        Ax_ENERGY = Ax_ENERGY - (data_buffer[j][0] ** 2)
        Ax_SKEW_T = Ax_SKEW_T - ((data_buffer[j][0]-Ax_MEAN)**3 )/ 100
        Ax_SAC = Ax_SAC - (abs(Ax_MEAN-data_buffer[j][0]))**4/100

        #adding new data in calculation
        Ax_MEAN = Ax_MEAN + accel[0]/100
        Ax_MIN = min(Ax_MIN,accel[0])
        Ax_MAX = max(Ax_MAX,accel[0])
        Ax_ENERGY = Ax_ENERGY + (accel[0] ** 2)
        Ax_SKEW_T = Ax_SKEW_T + ((accel[0]-Ax_MEAN)**3 )/ 100
        Ax_SAC = Ax_SAC + (abs(Ax_MEAN-accel[0]))**4/100



        #Removing old value
        Ay_MEAN = Ay_MEAN - data_buffer[j][1]/100
        Ay_ENERGY = Ay_ENERGY - (data_buffer[j][1] ** 2)
        Ay_SKEW_T = Ay_SKEW_T - ((data_buffer[j][1]-Ay_MEAN)**3 )/ 100
        Ay_SAC = Ay_SAC - (abs(Ay_MEAN-data_buffer[j][1]))**4/100
        #adding new data in calculation
        Ay_MEAN = Ay_MEAN + accel[1]/100
        Ay_MIN = min(Ay_MIN,accel[1])
        Ay_MAX = max(Ay_MAX,accel[1])
        Ay_ENERGY = Ay_ENERGY + (accel[1] ** 2)
        Ay_SKEW_T = Ay_SKEW_T + ((accel[1]-Ay_MEAN)**3 )/ 100
        Ay_SAC = Ay_SAC + (abs(Ay_MEAN-accel[1]))**4/100

        #Removing old value
        Az_MEAN = Az_MEAN - data_buffer[j][2]/100
        Az_ENERGY = Az_ENERGY - (data_buffer[j][2] ** 2)
        Az_SKEW_T = Az_SKEW_T - ((data_buffer[j][2]-Az_MEAN)**3 )/ 100
        Az_SAC = Az_SAC - (abs(Az_MEAN-data_buffer[j][2]))**4/100
        #adding new data in calculation
        Az_MEAN = Az_MEAN + accel[2]/100
        Az_MIN = min(Az_MIN,accel[2])
        Az_MAX = max(Az_MAX,accel[2])
        Az_ENERGY = Az_ENERGY + (accel[2] ** 2)
        Az_SKEW_T = Az_SKEW_T + ((accel[2]-Az_MEAN)**3 )/ 100
        Az_SAC = Az_SAC + (abs(Az_MEAN-accel[2]))**4/100

        #Removing old value
        Gx_MEAN = Gx_MEAN - data_buffer[j][3]/100
        Gx_ENERGY = Gx_ENERGY - (data_buffer[j][3] ** 2)
        Gx_SKEW_T = Gx_SKEW_T - ((data_buffer[j][3]-Gx_MEAN)**3 )/ 100
        Gx_SAC = Gx_SAC - (abs(Gx_MEAN-data_buffer[j][3]))**4/100
        #adding new data in calculation
        Gx_MEAN = Gx_MEAN + gyro[0]/100
        Gx_MIN = min(Gx_MIN,gyro[0])
        Gx_MAX = max(Gx_MAX,gyro[0])
        Gx_ENERGY = Gx_ENERGY + (gyro[0] ** 2)
        Gx_SKEW_T = Gx_SKEW_T + ((gyro[0]-Gx_MEAN)**3 )/ 100
        Gx_SAC = Gx_SAC + (abs(Gx_MEAN-gyro[0]))**4/100

        #Removing old value
        Gy_MEAN = Gy_MEAN - data_buffer[j][4]/100
        Gy_ENERGY = Gy_ENERGY - (data_buffer[j][4] ** 2)
        Gy_SKEW_T = Gy_SKEW_T - ((data_buffer[j][4]-Gy_MEAN)**3 )/ 100
        Gy_SAC = Gy_SAC - (abs(Gy_MEAN-data_buffer[j][4]))**4/100
        #adding new data in calculation
        Gy_MEAN = Gy_MEAN + gyro[1]/100
        Gy_MIN = min(Gy_MIN,gyro[1])
        Gy_MAX = max(Gy_MAX,gyro[1])
        Gy_ENERGY = Gy_ENERGY + (gyro[1] ** 2)
        Gy_SKEW_T = Gy_SKEW_T + ((gyro[1]-Gy_MEAN)**3 )/ 100
        Gy_SAC = Gy_SAC + (abs(Gy_MEAN-gyro[1]))**4/100


        #Removing old value
        Gz_MEAN = Gz_MEAN - data_buffer[j][5]/100
        Gz_ENERGY = Gz_ENERGY - (data_buffer[j][5] ** 2)
        Gz_SKEW_T = Gz_SKEW_T - ((data_buffer[j][5]-Gz_MEAN)**3 )/ 100
        Gz_SAC = Gz_SAC - (abs(Gz_MEAN-data_buffer[j][5]))**4/100
        #adding new data in calculation
        Gz_MEAN = Gz_MEAN + gyro[2]/100
        Gz_MIN = min(Gz_MIN,gyro[2])
        Gz_MAX = max(Gz_MAX,gyro[2])
        Gz_ENERGY = Gz_ENERGY + (gyro[2] ** 2)
        Gz_SKEW_T = Gz_SKEW_T + ((gyro[2]-Gz_MEAN)**3 )/ 100
        Gz_SAC = Gz_SAC + (abs(Gz_MEAN-gyro[2]))**4/100

        #Removing old value
        Mx_MEAN = Mx_MEAN - data_buffer[j][6]/100
        Mx_ENERGY = Mx_ENERGY - (data_buffer[j][6] ** 2)
        Mx_SKEW_T = Mx_SKEW_T - ((data_buffer[j][6]-Mx_MEAN)**3 )/ 100
        Mx_SAC = Mx_SAC - (abs(Mx_MEAN-data_buffer[j][6]))**4/100
        #adding new data in calculation
        Mx_MEAN = Mx_MEAN + magnet[0]/100
        Mx_MIN = min(Mx_MIN,magnet[0])
        Mx_MAX = max(Mx_MAX,magnet[0])
        Mx_ENERGY = Mx_ENERGY + (magnet[0] ** 2)
        Mx_SKEW_T = Mx_SKEW_T + ((magnet[0]-Mx_MEAN)**3 )/ 100
        Mx_SAC = Mx_SAC + (abs(Mx_MEAN-magnet[0]))**4/100

        #Removing old value
        My_MEAN = My_MEAN - data_buffer[j][7]/100
        My_ENERGY = My_ENERGY - (data_buffer[j][7] ** 2)
        My_SKEW_T = My_SKEW_T - ((data_buffer[j][7]-My_MEAN)**3 )/ 100
        My_SAC = My_SAC - (abs(My_MEAN-data_buffer[j][7]))**4/100
        #adding new data in calculation
        My_MEAN = My_MEAN + magnet[1]/100
        My_MIN = min(My_MIN,magnet[1])
        My_MAX = max(My_MAX,magnet[1])
        My_ENERGY = My_ENERGY + (magnet[1] ** 2)
        My_SKEW_T = My_SKEW_T + ((magnet[1]-My_MEAN)**3 )/ 100
        My_SAC = My_SAC + (abs(My_MEAN-magnet[1]))**4/100



        #Removing old value
        Mz_MEAN = Mz_MEAN - data_buffer[j][8]/100
        Mz_ENERGY = Mz_ENERGY - (data_buffer[j][8] ** 2)
        Mz_SKEW_T = Mz_SKEW_T - ((data_buffer[j][8]-Mz_MEAN)**3 )/ 100
        Mz_SAC = Mz_SAC - (abs(Mz_MEAN-data_buffer[j][8]))**4/100
        #adding new data in calculation
        Mz_MEAN = Mz_MEAN + magnet[2]/100
        Mz_MIN = min(Mz_MIN,magnet[2])
        Mz_MAX = max(Mz_MAX,magnet[2])
        Mz_ENERGY = Mz_ENERGY + (magnet[2] ** 2)
        Mz_SKEW_T = Mz_SKEW_T + ((magnet[2]-Mz_MEAN)**3 )/ 100
        Mz_SAC = Mz_SAC + (abs(Mz_MEAN-magnet[2]))**4/100

        #Adding new value
        data_buffer[j][0] = accel[0]
        data_buffer[j][1] = accel[1]
        data_buffer[j][2] = accel[2]
        data_buffer[j][3] = gyro[0]
        data_buffer[j][4] = gyro[1]
        data_buffer[j][5] = gyro[2]
        data_buffer[j][6] = magnet[0]
        data_buffer[j][7] = magnet[1]
        data_buffer[j][8] = magnet[2]
    # Iterate over entries and print data :
    time.sleep_ms(4000)
    print("-*-" * 20)# Separator for each entry
    print (f"Seq : {j} N:100")
    print("\n")
    print(f"Ax:{data_buffer[j][0]},MEAN:{Ax_MEAN},MIN:{Ax_MIN},MAX:{Ax_MAX},Kurtosis:{Ax_SAC/((Ax_ENERGY/100 - (Ax_MEAN**2))**2)},Alteration:{initial_Ax-accel[0]},RANGE:{Ax_MAX - Ax_MIN},ENERGY:{Ax_ENERGY},POWER:{Ax_ENERGY/100},RMS:{(Ax_ENERGY/100)**0.5},STD:{(Ax_ENERGY/100 - (Ax_MEAN**2))**0.5},Variance:{(Ax_ENERGY/100 - (Ax_MEAN**2))},SKEW:{Ax_SKEW_T/((Ax_ENERGY/100 - (Ax_MEAN**2))**0.5)},SLOPE:{data_buffer[j][0]-data_buffer[j-1][0]}")
    print("\n")
    print(f"Ay:{data_buffer[j][1]},MEAN:{Ay_MEAN},MIN:{Ay_MIN},MAX:{Ay_MAX},Kurtosis:{Ay_SAC/((Ay_ENERGY/100 - (Ay_MEAN**2))**2)},Alteration:{initial_Ay-accel[1]},RANGE:{Ay_MAX - Ay_MIN},ENERGY:{Ay_ENERGY},POWER:{Ay_ENERGY/100},RMS:{(Ay_ENERGY/100)**0.5},STD:{(Ay_ENERGY/100 - (Ay_MEAN**2))**0.5},Variance:{(Ay_ENERGY/100 - (Ay_MEAN**2))},SKEW:{Ay_SKEW_T/((Ay_ENERGY/100 - (Ay_MEAN**2))**0.5)},SLOPE:{data_buffer[j][1]-data_buffer[j-1][1]}")
    print("\n")
    print(f"Az:{data_buffer[j][2]},MEAN:{Az_MEAN},MIN:{Az_MIN},MAX:{Az_MAX},Kurtosis:{Az_SAC/((Az_ENERGY/100 - (Az_MEAN**2))**2)},Alteration:{initial_Az-accel[2]},RANGE:{Az_MAX - Az_MIN},ENERGY:{Az_ENERGY},POWER:{Az_ENERGY/100},RMS:{(Az_ENERGY/100)**0.5},STD:{(Az_ENERGY/100 - (Az_MEAN**2))**0.5},Variance:{(Az_ENERGY/100 - (Az_MEAN**2))},SKEW:{Az_SKEW_T/((Az_ENERGY/100 - (Az_MEAN**2))**0.5)},SLOPE : {data_buffer[j][2]-data_buffer[j-1][2]}")
    print("\n")
    print(f"Gx:{data_buffer[j][3]},MEAN:{Gx_MEAN},MIN:{Gx_MIN},MAX:{Gx_MAX},Kurtosis:{Gx_SAC/((Gx_ENERGY/100 - (Gx_MEAN**2))**2)},Alteration:{initial_Gx-gyro[0]},RANGE:{Gx_MAX - Gx_MIN},ENERGY:{Gx_ENERGY},POWER:{Gx_ENERGY/100},RMS:{(Gx_ENERGY/100)**0.5},STD:{(Gx_ENERGY/100 - (Gx_MEAN**2))**0.5},Variance:{(Gx_ENERGY/100 - (Gx_MEAN**2))},SKEW:{Gx_SKEW_T/((Gx_ENERGY/100 - (Gx_MEAN**2))**0.5)},SLOPE : {data_buffer[j][3]-data_buffer[j-1][3]}")
    print("\n")
    print(f"Gy:{data_buffer[j][4]},MEAN:{Gy_MEAN},MIN:{Gy_MIN},MAX:{Gy_MAX},Kurtosis:{Gy_SAC/((Gy_ENERGY/100 - (Gy_MEAN**2))**2)},Alteration:{initial_Gy-gyro[1]},RANGE:{Gy_MAX - Gy_MIN},ENERGY:{Gy_ENERGY},POWER:{Gy_ENERGY/100},RMS:{(Gy_ENERGY/100)**0.5},STD:{(Gy_ENERGY/100 - (Gy_MEAN**2))**0.5},Variance:{(Gy_ENERGY/100 - (Gy_MEAN**2))},SKEW:{Gy_SKEW_T/((Gy_ENERGY/100 - (Gy_MEAN**2))**0.5)},SLOPE : {data_buffer[j][4]-data_buffer[j-1][4]}")
    print("\n")
    print(f"Gz:{data_buffer[j][5]},MEAN:{Gz_MEAN},MIN:{Gz_MIN},MAX:{Gz_MAX},Kurtosis:{Gz_SAC/((Gz_ENERGY/100 - (Gz_MEAN**2))**2)},Alteration:{initial_Gz-gyro[2]},RANGE:{Gz_MAX - Gz_MIN},ENERGY:{Gz_ENERGY},POWER:{Gz_ENERGY/100},RMS:{(Gz_ENERGY/100)**0.5},STD:{(Gz_ENERGY/100 - (Gz_MEAN**2))**0.5},Variance:{(Gz_ENERGY/100 - (Gz_MEAN**2))},SKEW:{Gz_SKEW_T/((Gz_ENERGY/100 - (Gz_MEAN**2))**0.5)},SLOPE : {data_buffer[j][5]-data_buffer[j-1][5]}")
    print("\n")
    print(f"Mx:{data_buffer[j][6]},MEAN:{Mx_MEAN},MIN:{Mx_MIN},MAX:{Mx_MAX},Kurtosis:{Mx_SAC/((Mx_ENERGY/100 - (Mx_MEAN**2))**2)},Alteration:{initial_Mx-magnet[0]},RANGE:{Mx_MAX - Mx_MIN},ENERGY:{Mx_ENERGY},POWER:{Mx_ENERGY/100},RMS:{(Mx_ENERGY/100)**0.5},STD:{(Mx_ENERGY/100 - (Mx_MEAN**2))**0.5},Variance:{(Mx_ENERGY/100 - (Mx_MEAN**2))},SKEW:{Mx_SKEW_T/((Mx_ENERGY/100 - (Mx_MEAN**2))**0.5)},SLOPE : {data_buffer[j][6]-data_buffer[j-1][6]}")
    print("\n")
    print(f"My:{data_buffer[j][7]},MEAN:{My_MEAN},MIN:{My_MIN},MAX:{My_MAX},Kurtosis:{My_SAC/((My_ENERGY/100 - (My_MEAN**2))**2)},Alteration:{initial_My-magnet[1]},RANGE:{My_MAX - My_MIN},ENERGY:{My_ENERGY},POWER:{My_ENERGY/100},RMS:{(My_ENERGY/100)**0.5},STD:{(My_ENERGY/100 - (My_MEAN**2))**0.5},Variance:{(My_ENERGY/100 - (My_MEAN**2))},SKEW:{My_SKEW_T/((My_ENERGY/100 - (My_MEAN**2))**0.5)},SLOPE : {data_buffer[j][7]-data_buffer[j-1][7]}")
    print("\n")
    print(f"Mz:{data_buffer[j][8]},MEAN:{Mz_MEAN},MIN:{Mz_MIN},MAX:{Mz_MAX},Kurtosis:{Mz_SAC/((Mz_ENERGY/100 - (Mz_MEAN**2))**2)},Alteration:{initial_My-magnet[1]},RANGE:{Mz_MAX - Mz_MIN},ENERGY:{Mz_ENERGY},POWER:{Mz_ENERGY/100},RMS:{(Mz_ENERGY/100)**0.5},STD:{(Mz_ENERGY/100 - (Mz_MEAN**2))**0.5},Variance:{(Mz_ENERGY/100 - (Mz_MEAN**2))},SKEW:{Mz_SKEW_T/((Mz_ENERGY/100 - (Mz_MEAN**2))**0.5)},SLOPE : {data_buffer[j][8]-data_buffer[j-1][8]}")
    print("\n")
    j=j+1
    if j==100 :
        j=0


