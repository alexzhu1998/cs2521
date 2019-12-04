// msort.c ... merge-based disk sort
// Written by John Shepherd, Sep 2008
// Last modified, Aug 2014

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// max length allowed for input lines
#define MAXLINE 128 
// number if items in initial sorted runs
#define INIT_RUN_SIZE 512

char *mergeSort(char *fileName);
void mergePass(char *inFile, char *outFile,
                  int runLength, int nLines);
int sortInitRuns(char *inFile, char *outFile, int runLength);
int copyFile(char *inFile, char *outFile);
FILE *openFile(char *fileName, char *accessMode);
int cmp(const void *a, const void *b);

// main: sort contents of a named file
// * writes sorted result to standard output
int main(int argc, char ** argv)
{
	FILE *resf; // result file handle
	char *resFile; // name of sorted tmp file
	char line[MAXLINE]; // line buffer

	// check that we have a file to sort
	if (argc < 2) {
		fprintf(stderr,"Usage: %s File\n",argv[0]);
		exit(1);
	}

	// computation: sort "tmp1" via merging
	resFile = mergeSort(argv[1]);

	// finalisation: copy sorted data to stdout
	resf = openFile(resFile,"reading");
	while (fgets(line,MAXLINE,resf) != NULL)
		fputs(line, stdout);
	fclose(resf);
	unlink(resFile);

	return 0;
}

// mergeSort: sort a collection of data via merging
char *mergeSort(char *originalFile)
{
	char *inFile, *outFile; // file names
	int  nLines; // how many lines in file
	int  runLength; // how many lines in each sorted run
	char *tmp;

	// make a first pass, doing in-memory sort of 256-line runs
	nLines = sortInitRuns(originalFile,"tmp1",INIT_RUN_SIZE);
	runLength = INIT_RUN_SIZE;

	// multiple merging passes to achieve sort
	inFile = "tmp1"; outFile = "tmp2";
	while (runLength < nLines) {
		// one merging pass
		mergePass(inFile, outFile, runLength, nLines);
		// after each pass, sorted runs are twice as long
		runLength *= 2;
		// swap file names
		tmp = inFile; inFile = outFile; outFile = tmp;
	}

	// copy sorted file to result file
	nLines = copyFile(inFile, "tmpRes");
	return "tmpRes";
}

// mergePass: make one pass through file
// * input sorted runs are length runLength
// * output sorted runs are length 2*runLength
void mergePass(char *inFile, char *outFile, int runLength, int nLines)
{
	FILE *inf1, *inf2, *outf;
	int  n = 0; // current set of runs
	int  inLine1 = 0, inLine2 = 0; // current line within runs
	int  startRun1, startRun2, endRun1, endRun2; // file "indexes"
	char line1[MAXLINE], line2[MAXLINE]; //line buffers

	// initialise file handles
	inf1 = openFile(inFile, "reading");
	inf2 = openFile(inFile, "reading");
	outf = openFile(outFile, "writing");

	// until all input is consumed
	for (;;) {
		// compute line #'s for start/end of next runs
		startRun1 = 2*n*runLength + 1;
		if (startRun1 > nLines) break;
		endRun1 = startRun1 + runLength - 1;
		startRun2 = endRun1 + 1;
		endRun2 = startRun2 + runLength - 1;
		if (endRun2 > nLines) endRun2 = nLines;
		// align file handles at start of next two runs
		while (inLine1 < startRun1) {
			fgets(line1, MAXLINE, inf1);
			inLine1++;
		}
		while (inLine2 < startRun2) {
			fgets(line2, MAXLINE, inf2);
			inLine2++;
		}
		// perform merging
		while (inLine1 <= endRun1 && inLine2 <= endRun2) {
			if (strcmp(line1,line2) < 0) {
				fputs(line1, outf);
				fgets(line1, MAXLINE, inf1);
				inLine1++;
			}
			else {
				fputs(line2, outf);
				fgets(line2, MAXLINE, inf2);
				inLine2++;
			}
		}
		while (inLine1 <= endRun1) {
			fputs(line1, outf);
			fgets(line1, MAXLINE, inf1);
			inLine1++;
		}
		while (inLine2 <= endRun2) {
			fputs(line2, outf);
			fgets(line2, MAXLINE, inf2);
			inLine2++;
		}
		n++;
	}
	// close files
	fclose(inf1); fclose(inf2); fclose(outf);
}

// sortInitRuns: make first pass over file to sort runs in-memory
int sortInitRuns(char *inFile, char *outFile, int runLength)
{
	int  i, n; // # lines in current run
	int  nlines; // total #lines
	char **lines; // buffers for lines in run
	FILE *inf, *outf; // file handles

	// create line buffers; assume malloc OK
	lines = malloc(runLength*sizeof(char *));
	for (i = 0; i < runLength; i++)
		lines[i] = malloc(MAXLINE*sizeof(char));

	// read input, sort runs, write to output
	inf = openFile(inFile,"reading");
	outf = openFile(outFile,"writing");
	n = 0;  nlines = 0;
	while (fgets(lines[n],MAXLINE,inf) != NULL) {
		n++;  nlines++;
		if (n == runLength) {
			// filled one initial run
			// sort it, write it, reset for next run
			qsort(lines, n, sizeof(char *), cmp);
			for (i = 0; i < n; i++)
				fputs(lines[i], outf);
			n = 0;
		}
	}

	// deal with final run whose size < runLength
	if (n > 0) {
		qsort(lines, n, sizeof(char *), cmp);
		for (i = 0; i < n; i++)
			fputs(lines[i], outf);
		n = 0;
	}	

	// free line buffers
	for (i = 0; i < runLength; i++) free(lines[i]);
	free(lines);

	// close files
	fclose(inf); fclose(outf);

	// return line count
	return nlines;
}

// cmp: compare two strings from line buffer
// * wrapper for strcmp() for use with qsort()
// * the supplied pointers are pointers into lines[]
// * each entry in lines[] is a pointer to a string
int cmp(const void *a, const void *b)
{
	char **aa = (char **)a;
	char **bb = (char **)b;
	return strcmp(*aa, *bb);
}

// copyFile: make a copy of F1 into F2
// * returns count of lines in F1
int copyFile(char *inFile, char *outFile)
{
	FILE *inf, *outf; // file handles
	char line[MAXLINE]; // line buffer
	int nlines; // count of lines

	inf = openFile(inFile,"reading");
	outf = openFile(outFile,"writing");
	nlines = 0;
	while (fgets(line,MAXLINE,inf) != NULL) {
		nlines++;
		fputs(line,outf);
	}
	fclose(inf); fclose(outf);
	return nlines;
}

// openFile: wrapper for fopen()
// * either it successfully opens file in requested mode
// * or it fails, produces an error message, and exits
FILE *openFile(char *fileName, char *accessMode)
{
	FILE *fp;
	char *mode;

	switch (accessMode[0]) {
	case 'r': mode = "r"; break;
	case 'w': mode = "w"; break;
	default:  printf("Unknown file access mode\n");
		  exit(1);
	}
	if ((fp = fopen(fileName, mode)) == NULL) {
		fprintf(stderr,"Can't open %s for %s\n", fileName, accessMode);
		exit(1);
	}
	return fp;
}
