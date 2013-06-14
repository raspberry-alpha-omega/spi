#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPiSPI.h>

#define CHANNEL 0

void main(int argc, char** argv) {
	uint8_t on[] = { 0xFF, 0xFF };
	uint8_t off[] = { 0xFF, 0x00 };
	uint8_t buf[2];

	if (wiringPiSPISetup(CHANNEL, 1000000) < 0) {
		fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
		exit(errno);
	}

	for (;;) {
		memcpy(buf, on, 2);
		wiringPiSPIDataRW(CHANNEL, buf, 2);
		sleep(1);
		memcpy(buf, off, 2);
		wiringPiSPIDataRW(CHANNEL, buf, 2);
		sleep(1);
	}
}
