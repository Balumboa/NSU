CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

# Все объектные файлы
OBJS = adjacency_list.o adjacency_matrix.o incidence_matrix.o list_of_edges.o vector.o convert_matrixes.o test_convert.o

# Цель по умолчанию
all: test_convert

# Сборка основной программы
test_convert: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Компиляция отдельных модулей
adjacency_list.o: adjacency_list.c adjacency_list.h vector.h
	$(CC) $(CFLAGS) -c adjacency_list.c

adjacency_matrix.o: adjacency_matrix.c adjacency_matrix.h
	$(CC) $(CFLAGS) -c adjacency_matrix.c

incidence_matrix.o: incidence_matrix.c incidence_matrix.h
	$(CC) $(CFLAGS) -c incidence_matrix.c

list_of_edges.o: list_of_edges.c list_of_edges.h
	$(CC) $(CFLAGS) -c list_of_edges.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

convert_matrixes.o: convert_matrixes.c convert_matrixes.h vector.h
	$(CC) $(CFLAGS) -c convert_matrixes.c

test_convert.o: test_convert.c convert_matrixes.h
	$(CC) $(CFLAGS) -c test_convert.c

# Очистка
clean:
	rm -f *.o test_convert

# Запуск тестов
run: test_convert
	./test_convert

.PHONY: all clean run