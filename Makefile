# Makefile
CC = g++
OBJ = fixed_len_size_exp write_fixed_len_pages read_fixed_len_pages

all: $(OBJ)

fixed_len_size_exp: record.cpp fixed_len_size_exp.cpp
	$(CC) -o $@ $^

write_fixed_len_pages: write_fixed_len_pages.cpp page.cpp record.cpp
	$(CC) -o $@ $^

read_fixed_len_pages: read_fixed_len_page.cpp page.cpp record.cpp
	$(CC) -o $@ $^

clean:
	rm $(OBJ)