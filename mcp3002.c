#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPiSPI.h>

#define CHANNEL 0

uint8_t buf[2];

unsigned int sample(int channel) {
	buf[0] = 0x60 + channel;
	buf[1] = 0x00;
	wiringPiSPIDataRW(CHANNEL, buf, 2);
	return buf[1] + (buf[0] & 0x03) << 8;
}

void main(int argc, char** argv) {
	if (wiringPiSPISetup(CHANNEL, 4000000) < 0) {
		fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
		exit(errno);
	}

	printf("sample=%04x\n", sample(0));
}
