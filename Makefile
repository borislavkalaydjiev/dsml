
CC=gcc
CFLAGS= -c -g -I../../ -I. -fPIC -fprofile-arcs -ftest-coverage -DDSML_DEBUG #-Wall
LDFLAGS= -fprofile-arcs
SOURCES = core.c mem_file_iface.c posix_file_iface.c tools.c sfes.c debug.c main_unix.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE = dsml_test

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

reinit_test_files:
	mkdir -p node0
	truncate -s 100 node0/0.txt
	truncate -s 200 node0/1.txt
	mkdir -p node1
	truncate -s 100 node1/0.txt
	truncate -s 200 node1/1.txt

cov: $(EXECUTABLE)
	lcov -d . -z
	make reinit_test_files
	./$(EXECUTABLE)
	make reinit_test_files
	lcov -d . -c -o $(EXECUTABLE).info
	genhtml $(EXECUTABLE).info --output-directory cov

callgrind: $(EXECUTABLE)
	make reinit_test_files
	valgrind --tool=callgrind --collect-jumps=yes ./$(EXECUTABLE)
	make reinit_test_files

all: $(SOURCES) $(EXECUTABLE)

clean:
	lcov -d . -z ; \
	rm *.gcno $(EXECUTABLE).info ; \
	rm *~ *.o $(EXECUTABLE)
