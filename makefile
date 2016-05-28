FLAGS = -Wall

all: pianoDP

pianoDP: pianoDP.o tables.o song.o note.o
	gcc $(FLAGS) -g pianoDP.o tables.o song.o note.o -o pianoDP

pianoDP.o: pianoDP.c tables.h song.h note.h
	gcc $(FLAGS) -c -g pianoDP.c -o pianoDP.o

tables.o: tables.c tables.h
	gcc $(FLAGS) -c -g tables.c -o tables.o

song.o: song.c song.h note.h
	gcc $(FLAGS) -c -g song.c -o song.o

note.o: note.c note.h
	gcc $(FLAGS) -c -g note.c -o note.o

clean:
	rm -f *.o pianoDP

