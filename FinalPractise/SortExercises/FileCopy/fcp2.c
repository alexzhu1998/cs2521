// Copy file argv[1] to file argv[2], line-by-line
// written by John Shepherd, August 2015

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// check command line args
	if (argc < 3) {
		fprintf(stderr, "Usage: %s InFile OutFile\n",argv[0]);
		exit(1);
	}
	// set up input file
	FILE *inf;
	if ((inf = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't read %s\n",argv[1]);
		exit(2);
	}
	// set up output file
	FILE *outf;
	if ((outf = fopen(argv[2],"w")) == NULL) {
		fprintf(stderr, "Can't write %s\n",argv[2]);
		exit(3);
	}
	// copy contents of inf to outf
	char line[BUFSIZ];
	while (fgets(line,BUFSIZ,inf) != NULL)
		fputs(line,outf);
	// close file handles
	fclose(inf);
	fclose(outf);
	return 0;
}
