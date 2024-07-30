all: bin/generator bin/regex bin/output_parser bin/output_parser

bin/generator: src/generator.c
	cc -o bin/generator src/generator.c

bin/regex: src/regex.c
	cc -o bin/regex src/regex.c

bin/output_parser: src/output_parser.c src/hashmap.c
	cc -o bin/output_parser src/output_parser.c src/hashmap.c

#bin/hashmap: src/hashmap.c
#	cc -o bin/hashmap src/hashmap.c
