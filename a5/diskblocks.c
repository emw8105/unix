#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIBLOCKS 2048L
#define DIBLOCKS (2048L*2048L)
#define TIBLOCKS (2048L*2048L*2048L)

long computeOverheadBlocks(long diskblocks) {
	/*long long maxBlocks = 2048*2048;
	maxBlocks *= 2048;
	maxBlocks += 2048*2048;
	maxBlocks += 2048;

	if (diskblocks > maxBlocks) {
		return -1;
	}*/
	/*
	long numDirect = (diskblocks-12)/2048;
	if ((diskblocks-12)%2048)
		numDirect++;
	long numIndToDirect = (numDirect-1)/12;
	if ((numIndToDirect-12)%12)
		numIndToDirect++;
	int numIndToInd;
	if (numIndToDirect <= 1)
		numIndToInd = 0;
	else
		numIndToInd = 1;
	*/

	long numDirect = ceil((diskblocks-12.0)/2048);
	long numIndToDirect = ceil((numDirect - 1.0)/2048);
	int numIndToInd;
	if (numIndToDirect <= 1)
		numIndToInd = 0;
	else
		numIndToInd = 1;

	return numDirect + numIndToDirect + numIndToInd;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: diskblocks <file size in KBs>\n");
		return -1;
	}
	long filesize = atol(argv[1]);
	long diskblocks = filesize / 8;
	if (filesize % 8) 
		diskblocks++;

	printf("%ld %d\n", diskblocks, computeOverheadBlocks(diskblocks));
}
