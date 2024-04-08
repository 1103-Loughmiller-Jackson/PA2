#ifndef SONG_H
#define SONG_H
#include <iostream>
using namespace std;
class Song{
    string title, artist;
    Song* nextSong;

    public:
        //constructors and destructors
        Song();
        Song(string t, string a, Song* next);
        Song(const Song& rhs);
        ~Song();

        //setters
        void setNextSong(Song* s);
        void setTitle(string t);
        void setArtist(string a);

        //getters
        string getTitle() const;
        string getArtist() const;
        Song* getNextSong() const;

        Song& operator=(const Song&);

        friend ostream & operator << (ostream &out, const Song &s);

        
};

#endif