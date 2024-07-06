# MusicPsychologyToolbox

The MusicPsychologyToolbox contains tools to measure human vital functions (breathing and heart rate) together with musical performance parameters like audio, midi and video to make music psychological studies possible.  

* The folder "arduino" contains various sketches for recording the measured values with the Arduino Uno.

* The "scripts" folder contains the script for recording data with a Linux based computer, like RaspberryPi.

* The file "Airflow_Nose_Case.FCStd" can be used to print the housing for the nose sensor.

For more information see the [Wiki](https://github.com/MusicPsychologyToolbox/MusicPsychologyToolbox/wiki). 

## mtp-collect.py

mtp-collect.py is the script that collects all the data from the two Vernier Respirations Belts used in the experiment. Details about the usage of the respiration belts can be found at https://www.vernier.com/product/go-direct-respiration-belt/ and https://vernierst.github.io/godirect-examples/python/.

To run the script on Windows for a measurement of five minutes, use the following command:

`python mtp-collect.py --seconds 300`

To show the help type

`python mtp-collect.py --help`
