// ssort.c ... demo on how to use C's qsort()
// Written by John Shepherd, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define USAGE "Usage: %s zid|name|prog|magic DataFile\n"

typedef struct {
	int  zid;
	char name[10];
	char prog[5];
	int  magic;
} Student;

// input/output functions
int getStudent(FILE *, Student *);
void putStudent(FILE *, Student *);
//comparison function
int cmp1(Student *, Student *);
int cmp2(Student *, Student *);

int main(int argc, char **argv)
{
	Student s, students[100];
	int nstudents = 0;
	FILE *input;
	int (*comparison)();

	// which field are we sorting on
	if (argc < 3) {
		fprintf(stderr, USAGE, argv[0]);
		exit(EXIT_FAILURE);
	}

	// open the input file
	if ((input = fopen(argv[2],"r")) == NULL) {
		fprintf(stderr, "Can't open input file\n");
		exit(EXIT_FAILURE);
	}

	// read input into students[] array
	while (getStudent(input, &s))
		students[nstudents++] = s;

	if (strcmp(argv[1],"zid") == 0)
		comparison = cmp1;
	else if (strcmp(argv[1],"name") == 0)
		comparison = cmp2;
	else {
		fprintf(stderr, USAGE, argv[0]);
		exit(EXIT_FAILURE);
	}
	qsort(students, nstudents, sizeof(Student), comparison);

	// write sorted array
	for (int i = 0; i < nstudents; i++)
		putStudent(stdout, &students[i]);
	return EXIT_SUCCESS;
}

int getStudent(FILE *inf, Student *stu)
{
	char line[BUFSIZ];
	int n;
	if (fgets(line,BUFSIZ,inf) == NULL)
		return 0;
	n = sscanf(line, "%d %s %s %d",
	           &(stu->zid), stu->name, stu->prog, &(stu->magic));
	return (n == 4);
}

void putStudent(FILE *outf, Student *stu)
{
	fprintf(outf, "%d\t%s\t%s\t%d\n",
	              stu->zid, stu->name, stu->prog, stu->magic);
}

int cmp1(Student *a, Student *b)
{
#if 1
	return (a->zid - b->zid);
#else
	if (a->zid < b->zid)
		return -1;
	else if (a->zid > b->zid)
		return 1;
	else
		return 0;
#endif
}

int cmp2(Student *a, Student *b)
{
	return strcmp(a->name, b->name);
}
