// Copy named file to file.tmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	while (fgets(line,BUFSIZ,inf) != NULL) {
		fputs(line, outf);
	}
	// close file handles
	fclose(inf);
	fclose(outf);
	exit(0);
}
