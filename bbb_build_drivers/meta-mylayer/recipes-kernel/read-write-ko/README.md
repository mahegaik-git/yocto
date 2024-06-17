post insmod auto_dev_nr.c
check if we see entry at /dev/dummydriver
change permission as -> chmod 666 /dev/dummydriver
To write to driver run command console -> echo "This is a test" > /dev/dummydriver
To read from driver run command console -> head -n 1 /dev/dummdriver
To read and write from c code check test.c


