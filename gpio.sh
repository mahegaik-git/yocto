#!/bin/bash

echo 496 > /sys/class/gpio/export
echo 497 > /sys/class/gpio/export
echo 498 > /sys/class/gpio/export
echo 499 > /sys/class/gpio/export
echo 500 > /sys/class/gpio/export
echo 501 > /sys/class/gpio/export
echo 504 > /sys/class/gpio/export
echo 511 > /sys/class/gpio/export
#echo out > /sys/class/gpio$1/direction

while [ true ]; 
do 
    echo -n gpio 496 :
    cat /sys/class/gpio/gpio496/value
    echo -n gpio 497 :
    cat /sys/class/gpio/gpio497/value
    echo -n gpio 498 :
    cat /sys/class/gpio/gpio498/value
    echo -n gpio 499 :
    cat /sys/class/gpio/gpio499/value
    echo -n gpio 500 :
    cat /sys/class/gpio/gpio500/value
    echo -n gpio 501 :
    cat /sys/class/gpio/gpio501/value
    echo -n gpio 504 :
    cat /sys/class/gpio/gpio504/value
    echo -n gpio 511 :
    cat /sys/class/gpio/gpio511/value
    sleep 1

#echo 0 > /sys/class/gpio$1/value
#sleep(1)
done
