LC_ALL=C 
LANG=C

spi : spi.c
	c99 -o spi spi.c -lwiringPi

all : spitest scroll

spitest : spitest.c
	c99 -o spitest spitest.c -lwiringPi

scroll : spiscroll.c
	c99 -o scroll spiscroll.c -lwiringPi

