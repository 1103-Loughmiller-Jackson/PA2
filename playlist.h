#ifndef LOADEDSONGS_H
#define LOADEDSONGS_H

#include "song.h"

class Playlist{
    Song *firstSong, *lastSong;
    int numberSongsLoaded;
    string name;

    //have a private method to check if song is already in playlist
    bool inPlaylist(Song*);
    //have a private method to add a new song to end of playlist (this gets called from the + operator overload)
    void addSongToEnd(Song*);
    //have a private method to delete song from end of list (this gets called from - operator overload)
    void deleteSongFromEnd();

    public:
        //constructors and destructor
        Playlist();
        Playlist(Song* f, Song* l, int n, string nm);
        Playlist(const Playlist& rhs);
        ~Playlist();

        //getters
        Song* getFirstSong() const;
        Song* getLastSong() const;
        int getNumSongsLoaded() const;
        string getName() const;
    
        //setters
        void setName(string);

        //adder for new song at specified index location
        void addSongFromIndex(int, Playlist);
        void addSongAtIndex(int, int, Playlist);

        //delete song from specific index location
        void deleteSongFromIndex(int);

        //method for getting a song at index
        Song* getSongAtIndex(int) const;

        void displayLoadedSongs(bool=true)const;
        Playlist& operator=(const Playlist&);

        friend ostream & operator << (ostream &out, const Playlist &p);
        
        void operator+(Song a);
        void operator-(int);
};
#endif