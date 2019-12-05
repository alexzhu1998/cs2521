// Copy file argv[1] to file argv[2], chunk-by-chunk
// written by John Shepherd, August 2015

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	// check command line args
	if (argc < 3) {
		fprintf(stderr, "Usage: %s InFile OutFile [BufSiz]\n",argv[0]);
		exit(1);
	}
	int BufSize; // #bytes in i/o buffer
	BufSize = (argc == 4) ? atoi(argv[3]) : 8192;
	if (BufSize < 1024) BufSize = 1024;
	// set up i/o buffer
	char *buffer; // memory for i/o buffer
	buffer = malloc(BufSize*sizeof(char));
	if (buffer == NULL) {
		fprintf(stderr, "Can't allocate buffer (%d bytes)\n",BufSize);
		exit(4);
	}
	// set up input file descriptor
	int infd;
	if ((infd = open(argv[1],O_RDONLY)) < 0) {
		fprintf(stderr, "Can't read %s\n",argv[1]);
		exit(2);
	}
	// set up output file descriptor
	int outfd;
	if ((outfd = open(argv[2],O_WRONLY|O_CREAT,0644)) < 0) {
		fprintf(stderr, "Can't write %s\n",argv[2]);
		exit(3);
	}
	// copy contents of inf to outf
	int nbytes;
	while ((nbytes = read(infd, buffer, BufSize)) > 0) {
		write(outfd, buffer, nbytes);
	}
	// close file handles
	if (close(infd) < 0)
		fprintf(stderr, "Problem closing input\n");
	if (close(outfd) < 0)
		fprintf(stderr, "Problem closing output\n");
	return 0;
}
