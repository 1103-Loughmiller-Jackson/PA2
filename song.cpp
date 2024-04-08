#include "song.h"

//constructors and destructor
Song::Song(){
    title = "untitled";
    artist = "unknown artist";
    nextSong = nullptr;
}

Song::Song(string t, string a, Song* next){
    title = t;
    artist = a;
    nextSong = next;
}

Song::Song(const Song& rhs){
    title = rhs.title;
    artist = rhs.artist;
    nextSong = rhs.nextSong;
}

Song::~Song(){
}

//setters
void Song::setNextSong(Song* s){
    nextSong = s;
    // Song* temp = new Song;
    // temp = s;
    // if(nextSong != nullptr){
    //     delete nextSong;
    // }
    // nextSong = temp;
}

void Song::setTitle(string t){
    title = t;
}

void Song::setArtist(string a){
    artist = a;
}

//getters
string Song::getTitle() const{
    return title;
}

string Song::getArtist() const{
    return artist;
}

Song* Song::getNextSong() const{
    return nextSong;
}

Song& Song::operator=(const Song& rhs){
    //copy code body from copy constructor
    //have a return *this
    title = rhs.title;
    artist = rhs.artist;
    nextSong = rhs.nextSong;

    return *this;
}

