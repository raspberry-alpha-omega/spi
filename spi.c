#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPiSPI.h>

#define CHANNEL 0

uint8_t buf[2];

void spi(uint8_t reg, uint8_t val) {
	buf[0] = reg;
	buf[1] = val;
	wiringPiSPIDataRW(CHANNEL, buf, 2);
//	usleep(10);
}

void main(int argc, char** argv) {
	if (wiringPiSPISetup(CHANNEL, 1000000) < 0) {
		fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
		exit(errno);
	}

	if (argc < 3) {
		puts("usage spi <reg> <value>");
		exit(1);
	}

	const char* regs = argv[1];
	int reg = atoi(regs);
	const char* vals = argv[2];
	int val = atoi(vals);

	printf("argc=%d reg=%d val=%d\n", argc, reg, val);

	spi(reg, val);
}
