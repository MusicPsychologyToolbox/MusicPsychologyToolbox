import csv
import os
import argparse

from datetime import datetime
from gdx import gdx 
gdx = gdx.gdx()

parser = argparse.ArgumentParser(description="Collect data from Vernier Respiration Belts")
parser.add_argument('--period', default=100, help='Measurement period in ms')
parser.add_argument('--seconds', default=10, help='Measurement duration in seconds')
args = parser.parse_args()
p = int(args.period)
secs = int(args.seconds)

gdx.open(connection='usb')   # Use connection='ble' for a Bluetooth connection
gdx.select_sensors() # You will be asked to select the sensors to be used. You can select up to three.

startDt = datetime.now()
startDtStr = startDt.strftime("%d-%m-%Y_%H-%M-%S")
fn = f"data_{startDtStr}.csv"

with open(fn, 'w', newline='') as my_data_file:  
    csv_writer = csv.writer(my_data_file)

    ms = 0
    gdx.start(period=p) 
    column_headers = gdx.enabled_sensor_info()
    csv_writer.writerow(["time", "thorax", "abdomen"])

    count = int((1000 / p) * secs)
    for i in range(0,count):
        measurements = gdx.read() 
        if measurements == None: 
            break
        data = [ms] + measurements
        csv_writer.writerow(data)
        print(data)
        ms += p

gdx.stop()
gdx.close()

stopDt = datetime.now()
stopDtStr = stopDt.strftime("%d-%m-%Y_%H-%M-%S")
print()
print("Data file: "+fn)
print("Data points: "+str(count))
print("Start: "+startDtStr)
print("Stop :"+stopDtStr)

# If you did not hard-code in an absolute path, this is where the file should be found.
print("location of current working directory = ", os.getcwd()) 