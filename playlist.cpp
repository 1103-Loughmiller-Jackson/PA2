#include "playlist.h"

Playlist::Playlist(){
    firstSong = lastSong = nullptr; //if using default, nothing in queue
    numberSongsLoaded = 0;
    name = "Playlist";
}
Playlist::Playlist(Song* f, Song* l, int n, string nm){
    //left in to showcase moving through a queue
    //this WILL NOT compile until the underlined methods are implemented
    numberSongsLoaded =n;
    name = nm;
    if(f == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    Song* temp = f;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}

//write a copy constructor
//this will look very similar to the parameretized constructor
Playlist::Playlist(const Playlist& rhs){
    //left in to showcase moving through a queue
    //this WILL NOT compile until the underlined methods are implemented
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
        return;
    }
    Song* temp = rhs.firstSong;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
}

//write a desctructor
//this will iterate through playlist and delete all items

//POSSIBLE ERRORS HERE
Playlist::~Playlist(){

    while(firstSong != nullptr){
        Song* next = new Song;
        next = firstSong->getNextSong();
        delete firstSong;
        firstSong = next;
        delete next;
    }
}

//getters
Song* Playlist::getFirstSong() const{
    return firstSong;
}

Song* Playlist::getLastSong() const{
    return lastSong;
}

int Playlist::getNumSongsLoaded() const{
    return numberSongsLoaded;
}

string Playlist::getName() const{
    return name;
}

//setters
void Playlist::setName(string n){
    name = n;
}

//write a method to check if song is already in playlist
//will iterate through queue and check a passed song against songs already in playlist
bool Playlist::inPlaylist(Song* check){
    Song* temp = new Song;
    temp = firstSong;
    bool inPlaylist = false;
    while(temp != nullptr){
        if(temp->getTitle() == check->getTitle()){
            inPlaylist = true;
        }
        temp = temp->getNextSong();
    }
    
    return inPlaylist;
}

//POSSIBLE ERRORS HERE
void Playlist::addSongToEnd(Song* song){
    // if (numberSongsLoaded > 0){
    //     Song* temp = new Song;
    //     temp = firstSong;
    //     while(temp->getNextSong() != nullptr){
    //         temp = temp->getNextSong();
    //     }
    //     temp->setNextSong(song);
    //     song->setNextSong(nullptr);
    //     numberSongsLoaded++;
    // }

    // else{
    //     firstSong = lastSong = song;
    //     numberSongsLoaded++;
    // }
    if (numberSongsLoaded > 0) {
        lastSong->setNextSong(song);
        lastSong = song;
    } 
    else {
        firstSong = lastSong = song;
    }
    song->setNextSong(nullptr);
    numberSongsLoaded++;
}

//create the public adder method
//this should add a song at the beginning of the playlist
void Playlist::addSongFromIndex(int index, Playlist library){
    Song* songToAdd = new Song;
    songToAdd = library.getSongAtIndex(index);
    songToAdd->setNextSong(firstSong);
    firstSong = songToAdd;
}

void Playlist::addSongAtIndex(int index, int libraryIndex, Playlist library){
    Song* songToAdd = library.getSongAtIndex(libraryIndex);
    if (inPlaylist(songToAdd) == false){
        Song* temp = new Song;
        Song* temp1 = new Song;
        temp = firstSong;
        temp1 = firstSong->getNextSong();
        int currentSong = 0;
        while (currentSong <= index){
            temp = temp->getNextSong();
            temp1 = temp1->getNextSong();
            currentSong++;
        }
        temp->setNextSong(songToAdd);
        songToAdd->setNextSong(temp1);
    }
}
//create the private delete method
//this should delete the song at the end of the playlist
//check if there are no songs left in the playlist
void Playlist::deleteSongFromEnd(){
    Song* temp = new Song;
    temp = firstSong;
    while(temp->getNextSong() != lastSong){
        temp = temp->getNextSong();
    }
    delete lastSong;
    lastSong = temp;
    lastSong->setNextSong(nullptr);
    
}

//create the public delete method
//delete song at specific index position
void Playlist::deleteSongFromIndex(int index){
    Song* temp = new Song;
    temp = firstSong;
    Song* songToDelete = getSongAtIndex(index);
    while(temp->getNextSong() != songToDelete){
        temp = temp->getNextSong();
    }
    temp->setNextSong(songToDelete->getNextSong());
    delete songToDelete;
}

//create a method that gets a song at a specific index position
//this will be used in the delete and adder methods
Song* Playlist::getSongAtIndex(int index) const{
    Song* temp = new Song;
    temp = firstSong;
    int currentIndex = 0;
    while(currentIndex != index){
        temp = temp->getNextSong();
        currentIndex++;
    }
    return temp;
}

void Playlist::displayLoadedSongs(bool displayNumbers) const{
    if(firstSong == nullptr){
        cout << "No songs are currently loaded for play." <<endl;
    }
    Song *temp = firstSong;
    int numDisp = 0;
    while(temp){
        if(displayNumbers){
            cout << numDisp + 1 << ". ";
            if(numDisp+1 < 10){
                cout << "  ";
            }
            else if(numDisp+1 < 100){
                cout << " ";
            }
        }
        cout  << temp->getTitle() << endl;
        temp = temp->getNextSong();
        numDisp+=1;
    }
}

Playlist& Playlist::operator=(const Playlist& rhs){
    //copy code body from copy constructor
    //include a return *this
    numberSongsLoaded = rhs.numberSongsLoaded;
    name = rhs.name;
    if(rhs.firstSong == nullptr){
        firstSong = lastSong = nullptr;
        return *this;
    }
    Song* temp = rhs.firstSong;
    firstSong = lastSong = new Song;
    firstSong->setArtist(temp->getArtist());
    firstSong->setTitle(temp->getTitle());
    firstSong->setNextSong(nullptr);

    temp = temp->getNextSong();
    while(temp != nullptr){
        lastSong->setNextSong(new Song);
        lastSong = lastSong->getNextSong();
        lastSong->setArtist(temp->getArtist());
        lastSong->setTitle(temp->getTitle());
        lastSong->setNextSong(nullptr);
        temp = temp->getNextSong();
    }
    return *this;
}
void Playlist::operator+(Song newSong){
    //this should add a song directly to the end of the playlist
    addSongToEnd(&newSong);
}
void Playlist::operator-(int songInd){
    //call private deleter method
    deleteSongFromEnd();
}