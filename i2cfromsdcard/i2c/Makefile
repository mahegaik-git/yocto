
TOOLS_CFLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
		   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
		   -W -Wundef -Wmissing-prototypes 

TOOLS_TARGETS	:= my2cset

#
# Programs
#
all:	myi2cget myi2cset

myi2cset:  myi2cset.o
	$(CC) $(LDFLAGS) -o $@ $^

myi2cget:   myi2cget.o 
	$(CC) $(LDFLAGS) -o $@ $^
#
# Objects
#

%.o: %.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

clean:
	rm myi2cset myi2cset.o myi2cget myi2cget.o
