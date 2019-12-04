1: graph-ArrayofEdges.o graphtester.o
	gcc -Wall -Werror -o test graph-ArrayofEdges.o graphtester.o

2: Graph.o graphtester.o
	gcc -Wall -Werror -o test Graph.o graphtester.o

3: graph-ListofEdges.o list.o graphtester.o
	gcc -Wall -Werror -o test graph-ListofEdges.o list.o graphtester.o

graphtester.o: graphtester.c Graph.h
	gcc -Wall -Werror -c graphtester.c

graph-ArrayofEdges.o: graph-ArrayofEdges.c Graph.h
	gcc -Wall -Werror -c graph-ArrayofEdges.c

Graph.o: Graph.c Graph.h
	gcc -Wall -Werror -c Graph.c

graph-ListofEdges.o: graph-ListofEdges.c Graph.h list.h
	gcc -Wall -Werror -c graph-ListofEdges.c

list.o: list.c list.h
	gcc -Wall -Werror -c list.c

clean:
	rm -f test graphtester.o graph-ArrayofEdges.o Graph.o graph-ListofEdges.o list.o
