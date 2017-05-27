pf:		parse_file.o  parser.o  container.o  error.o
		gcc -g -ansi -Wall		parse_file.o  parser.o	container.o  error.o	-o pf



parse_file.o:	parse_file.c  parser.h  container.h  error.h
		gcc -g -c -ansi -Wall	parse_file.c					-o parse_file.o


parser.o:	parser.c  container.h  error.h
		gcc -g -c -ansi -Wall	parser.c					-o parser.o


container.o:	container.c  container.h  error.h
		gcc -g -c -ansi -Wall	container.c					-o container.o


error.o:	error.c  container.h
		gcc -g -c -ansi -Wall	error.c						-o error.o
