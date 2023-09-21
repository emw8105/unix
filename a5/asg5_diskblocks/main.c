#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define SIBLOCKS 2048L
#define DIBLOCKS (2048L*2048L)
#define TIBLOCKS (2048L*2048L*2048L)

long computeOverheadBlocks(long diskblocks) {

   /*long long int maxBlocks = 2048*2048;
    maxBlocks *= 2048;

    //printf("%lld", maxBlocks);

    long long int maxBlocks2 = 68753047648;
    if (diskblocks > maxBlocks2) {
        return 4198403;
    }*/

    long numDirect = ceil((diskblocks - 12.0)/2048);
    long numIndToDirect = ceil((numDirect - 1.0)/2048);
    int numIndToInd;
    if (numIndToDirect <= 1)
        numIndToInd = 0;
    else
        numIndToInd = 1;

    return numDirect + numIndToDirect + numIndToInd;
}

int main(int argc, char *argv[]) {
    /*if (argc != 2) {
            printf("Usage: diskblocks <file size in KBs>\n");
    return -1;
    } */
    long filesize;
    scanf("%ld", &filesize);
    //long filesize = atol(argv[1]);
    long diskblocks = filesize / 8;
    if (filesize % 8)
        diskblocks++;

    printf("%ld %ld\n", diskblocks, computeOverheadBlocks(diskblocks));
}
