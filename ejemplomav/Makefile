CC=gcc
CFLAGS=-I../libs/mavlink/include/mavlink/v1.0/common

mavlink_udp: mavlink_udp.o
	$(CC) -o mavlink_udp mavlink_udp.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f mavlink_udp mavlink_udp.o
