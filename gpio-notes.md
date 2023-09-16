Do "ls /sys/bus/i2c/drivers/mcp230xx/1-0027/gpio"
> ls /sys/bus/i2c/drivers/mcp230xx/1-0027/gpio
>gpiochip496  
Above message shows starting pin pin number, so 496 is pin 1
# Since we have 16 pins we can export pins from 496 to 511
>echo 496 > /sys/class/gpio/export
# Once we do this we should get gpio46 as below
> cd /sys/class/gpio/gpio496
>root@beaglebone-yocto:/sys/class/gpio/gpio496# ls
active_low  device  direction  power  subsystem  uevent  value
# Above ls what we see
## By default all pins are configured as INPUT
### To Read pin perform, be inside that gpio (eg. gpio496) and read value
> cat value
### To configure pin as output
> echo out > direction
### To Drive value on that pin be inside that path
> echo 1 > value

