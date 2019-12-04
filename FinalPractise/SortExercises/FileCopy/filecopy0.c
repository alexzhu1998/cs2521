// Copy named file to file.tmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// check command line args
	if (argc < 2) {
		fprintf(stderr, "Usage: %s File\n",argv[0]);
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
	char outFileName[BUFSIZ];
	strcpy(outFileName,argv[1]);
	strcat(outFileName,".tmp");
	if ((outf = fopen(outFileName,"w")) == NULL) {
		fprintf(stderr, "Can't write %s\n",outFileName);
		exit(3);
	}
	// copy contents of inf to outf
	int ch;
	while ((ch = getc(inf)) != EOF) {
		putc(ch, outf);
	}
	// close file handles
	fclose(inf);
	fclose(outf);
	exit(0);
}
