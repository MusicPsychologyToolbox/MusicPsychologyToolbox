# Music Psychology Toolbox (MPT)
#
# Copyright (c) 2016-2018 Christopher Fust
# Copyright (c) 2016-2018 Alexander Fust
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# This program is free software: you can redistribute it and/or modify
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#!/bin/bash

if [[ $# -ne 1 ]] ; then
    echo "Usage:"
    echo "record.sh sec_to_run"
    exit 0
fi

DATE=$(date +%Y-%m-%d-%H-%M-%S)

# record video via RPI cam
# -t ms
#TIME=$(($1 * 1000))
#echo $TIME
#raspivid -o video_$DATE.h264 -t $(($1 * 1000)) -n -fl  &

# record audio via Zoom H2
# -d sec
#
# This approach does not work:
#   o arecord will not stop after the given time
#   o arecord will flood the current folder with 1k files (due to SIGUSR1?)
#arecord -D plughw:H2,0 -N -c 2 -f cd -t wav -d 10 audio_$DATE.wav &

# recording midi from digital piano
arecordmidi -p 20:0 midi_$DATE.mid &

# record airflow data via arduino
#
# For testing minicom has been use.
#   minicom -C data_$DATE.csv -b 115200 -D /dev/ttyACM0
# But to do time based tty logging ttylog in now used.
# Please mind that a modifed version has been used wich
# can be found at https://github.com/MrMontag
ttylog -b 115200 -d /dev/ttyACM0 -t $1 -f | tee data_$DATE.csv
# Prepend header to data_$DATE.csv
echo -e "time,sync,air1,air2,air3\n$(cat data_$DATE.csv)" > data_$DATE.csv

# stop midi recording
MIDI_PID=$(pgrep arecordmidi)
kill -SIGINT $MIDI_PID

