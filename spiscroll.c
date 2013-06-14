#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPiSPI.h>

#define CHANNEL 0

#include "font-8x8l.inc"
uint8_t buf[2];

void spi(uint8_t reg, uint8_t val) {
	buf[0] = reg;
	buf[1] = val;
	wiringPiSPIDataRW(CHANNEL, buf, 2);
	usleep(20);
}

void setupLEDMatrix(int channel) {
	if (wiringPiSPISetup(CHANNEL, 1000000) < 0) {
		fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
		exit(errno);
	}

	spi(0x09,0x00);
	spi(0x0B,0x07);
	spi(0x0A,0xFF);
	spi(0x0C,0x01);
}

void spichar(char c) {
	const uint8_t* bits = &font[c * 8];
	printf("spichar: sending char %c (%d)\n", c, c);
	for (int i = 0; i < 8; ++i) {
		printf("spichar: sending col %d, value %x\n", i, bits[i]);
		spi(i+1, bits[i]);
	}
	sleep(1);
}

void scroll(const char* text) {
	int len = strlen(text);
	for (int i = 0; i < len; ++i) {
		spichar(text[i]);
	}
}

void main(int argc, char** argv) {
	char* text = argv[0];

	if (argc > 1) {
		text = argv[1];
  }

	setupLEDMatrix(CHANNEL);
	for (;;) {
		scroll(text);
	}
}
