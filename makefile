jukebox: main.o helpers.o playlist.o song.o
	g++ -o jukebox main.o helpers.o playlist.o song.o -g

main.o: helpers.h playlist.h song.h main.cpp
	g++ -c main.cpp -g

helpers.o: helpers.h helpers.cpp playlist.h song.h
	g++ -c helpers.cpp -g

playlist.o: playlist.h playlist.cpp song.h
	g++ -c playlist.cpp -g

song.o: song.cpp song.h
	g++ -c song.cpp -g

clean:
	rm *.o jukebox