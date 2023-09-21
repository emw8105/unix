#include <stdio.h>     
#include <stdlib.h>   
#include <stdint.h>  
#include <inttypes.h>  
#include <errno.h>     // for EINTR
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/stat.h>

// Print out the usage of the program and exit.
void usage(char*);
uint32_t jenkins_one_at_a_time_hash(const uint8_t* , uint64_t );

// block size
#define BSIZE 4096

int main(int argc, char** argv) 
{
  int32_t fd;
  uint32_t nblocks;

  // usage: htree <filename> <# of threads>
  // input checking 
  if (argc != 3)
    usage(argv[0]);


  // open input file
  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }

  // use fstat to get file size
  struct stat fileInfo;
  if (fstat(fd, &fileInfo)) {
		perror("file not found.");
		exit(EXIT_FAILURE);
	}
  // calculate nblocks 
  uint64_t fileSize = fileInfo.st_size;

  nblocks = fileSize / BSIZE;
  if (fileSize % BSIZE)
  	nblocks++;
  printf("no. of blocks = %u \n", nblocks);

  char *buffer = (char *) malloc (fileSize);
  if (buffer == NULL) {
		perror("Memory allocation failure.");
		exit(EXIT_FAILURE);
  }
  uint64_t nread = 0;
  ssize_t n = 0;
  //as long as there is more data to read, keep reading!
  while ((nread < fileSize) && ((n = read(fd, &buffer[nread], fileSize-nread)) > 0)) {
  	nread += n;
	//n = read(fd, &buffer[nread], fileSize-nread);
  }
  	
  if (n < 0) {
		perror("File read error.");
		exit(EXIT_FAILURE);
  	}

  clock_t start = clock();
  // calculate hash value of the input file
  uint32_t hash = jenkins_one_at_a_time_hash(buffer, fileSize);
  // split the work when multiple threads are involved
  // uint64_t sizeForEachThread = fileSize / numThreads; 
  // Starting address of data for specific thread: &buffer[n * sizeForEachThread]
  // jenkins_one_at_a_time_hash(&buffer[n * sizeForEachThread], sizeForEachThread);:
  clock_t end = clock();
  printf("hash value = %u \n", hash);
  printf("time taken = %f \n", (end - start) * 1.0 / CLOCKS_PER_SEC);
  close(fd);
  return EXIT_SUCCESS;
}


uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, uint64_t length) 
{
  uint64_t i = 0;
  uint32_t hash = 0;

  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}


void usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename num_threads \n", s);
  exit(EXIT_FAILURE);
}
