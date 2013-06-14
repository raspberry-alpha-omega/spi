#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

extern int usleep(int usecs);

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

uint8_t display[8];

void push(uint8_t col) {
	for (int i = 0; i < 7; ++i) {
		display[i] = display[i+1];
		display[7] = col;
	}
}

void show() {
	for (int i = 0; i < 8; ++i) {
		spi(i+1,display[i]);
	}
}

void clear() {
	for (int i = 0; i < 8; ++i) {
		push(0);
	}
	show();
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
	for (int i = 0; i < 8; ++i) {
		push(bits[i]);
		show();
		usleep(100000);
	}
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
		spichar(' ');
	}
}
