LC_ALL=C 
LANG=C

all : spitest scroll spi

clean :
	rm spitest spi scroll

spitest : spitest.c
	c99 -o spitest spitest.c -lwiringPi

spi : spi.c
	c99 -o spi spi.c -lwiringPi

scroll : spiscroll.c
	c99 -o scroll spiscroll.c -lwiringPi

