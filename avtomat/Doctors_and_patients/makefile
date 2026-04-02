CC = gcc
CFLAGS = -Wall -Wextra -g

all: medical_db

medical_db: main.o patient.o doctor.o database.o
	$(CC) $(CFLAGS) -o medical_db main.o patient.o doctor.o database.o

main.o: main.c patient.h doctor.h database.h
	$(CC) $(CFLAGS) -c main.c

patient.o: patient.c patient.h
	$(CC) $(CFLAGS) -c patient.c

doctor.o: doctor.c doctor.h
	$(CC) $(CFLAGS) -c doctor.c

database.o: database.c database.h patient.h doctor.h
	$(CC) $(CFLAGS) -c database.c

clean:
	rm -f *.o medical_db *.bin *.txt

run: all
	./medical_db

.PHONY: all clean run