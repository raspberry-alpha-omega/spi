LC_ALL=C 
LANG=C

all : spitest scroll spi mcp3002

clean :
	rm spitest spi scroll

spitest : spitest.c
	c99 -o spitest spitest.c -lwiringPi

spi : spi.c
	c99 -o spi spi.c -lwiringPi

scroll : spiscroll.c
	c99 -o scroll spiscroll.c -lwiringPi

mcp3002 : mcp3002.c
	c99 -o mcp3002 mcp3002.c -lwiringPi

