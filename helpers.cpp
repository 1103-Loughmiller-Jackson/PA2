#include "helpers.h"

//should always use all songs when prompting to add to playlist
void promptSongSelection(Playlist allSongs){
    cout << allSongs;
    cout << allSongs.getNumSongsLoaded() +1 << ". Exit Program" <<endl;
    cout << "Please enter the number of the song to be added to your playlist: ";
}

//read data is given this time around
void readData(ifstream& inFile, Playlist& allSongs){
    string temp;
    int numSongsTotal = 0;
    while(!inFile.eof()){
        Song newSong;
        getline(inFile, temp, '-');
        newSong.setTitle(temp);
        getline(inFile, temp);
        newSong.setArtist(temp);
        //this uses the + operator overload to directly add a song to the end of a list
        allSongs + newSong;
        numSongsTotal ++;
    }
    
}

void displayMainMenu(){
    cout <<endl<< "Welcome to SongStoreSupreme!" <<endl;
    cout << "1. Load an existing playlist."<<endl;
    cout << "2. Create a new playlist." <<endl;
    cout << "3. Exit SongStoreSupreme." <<endl;
}

bool createNewPlaylist(const Playlist& allSongs, Playlist& newPlaylist){
    //check if a playlist already exists
    //if not, create a new playlist object
    string playlistName;
    int userSelection = 0, numSongs = 0;
    bool exit = false;

    while (playlistExists(playlistName)){
        cout << "Playlist name: ";
        cin >> playlistName;
        if (playlistExists(playlistName)){
            cout << "Another playlist already exists with that name." << endl;
        }
    }
    
    //display available songs from allSongs so user knows what they can add
    //have an option to finalize the list after user has selected all their songs
    //have an option to exit from program directly
    numSongs = allSongs.getNumSongsLoaded();
    cout << "Displaying Available Songs:" << endl;
    cout << allSongs;
    cout << numSongs+1 << "Finalize List." << endl << numSongs+2 << "Exit Program." << endl;

    while (userSelection < numSongs+1){
        cout << "Make a selection: ";
        cin >> userSelection;
        if (userSelection == numSongs+1){
            exit = false;
            return exit;
        }

        else if (userSelection == numSongs+2){
            exit = true;
            return exit;
        }

        else{
            newPlaylist + *allSongs.getSongAtIndex(userSelection);
        }
        
    }
    //user can select songs from list that then gets added to the playlist
    //add order is order of selection

    //write the playlist to a file
    fstream file(playlistName);
    
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << playlistName << endl;
        return exit;
    }

    int i = 0;
    while (i < newPlaylist.getNumSongsLoaded()){
        file << newPlaylist.getSongAtIndex(i) << endl;
        i++;
    }
    file.close();
    return exit;
}

void writePlaylistToFile(Playlist& playlist){
    //will need to open an output file stream
    //then iterate through your playlist and all it's songs to write to a file
    //close the filestream
    ofstream file(playlist.getName());
    Song* temp = new Song;

    temp = playlist.getFirstSong();

    while (temp != nullptr){
        file << temp->getTitle() << endl;
        temp = temp->getNextSong();
    }
    delete temp;
    file.close();
}

bool playlistExists(string newPlaylist){
    DIR *directoryPtr = opendir(".");
    struct dirent *directoryEntry;
    bool returnValue = false;
    newPlaylist = newPlaylist + ".txt";

    if (directoryPtr) {
        while ((directoryEntry = readdir(directoryPtr)) != NULL) {
            string filename = directoryEntry->d_name;
            if(filename == newPlaylist){
                returnValue = true;
            }
        }
            
    closedir(directoryPtr); //close all directory
    }
    return returnValue;
}
void promptPlaylistSelection(string* existingPlaylists, int numPlaylists){
    cout << endl;
    cout << "The following playlists are currently available:" <<endl;
    for(int i =0; i< numPlaylists; i++){
        cout << i+1 << ". " << existingPlaylists[i] << endl;
    }
}

void promptModificationsToExistingPlaylist(){
    cout << "1. Modify Playlist." <<endl;
    cout << "2. Delete Playlist." << endl;
    cout << "3. Return to Main Menu." <<endl;
    cout << "4. Exit Program." <<endl;
}

void promptTypesModificationSelection(){
    cout << "1. Remove Song(s)." <<endl;
    cout << "2. Add Song(s)." <<endl;
    cout << "3. Return to Playlist Options Menu." <<endl;
    cout << "4. Exit." <<endl;
}

//POSSIBLE ERROS HERE
bool deleteSongFromPlaylist(Playlist& playlist){
    //provide user a menu that shows all songs that can be deleted from playlist
    //need an option to return to menu
    //need an option to exit program directly
    int playlistLen = playlist.getNumSongsLoaded();
    int userSelection = 0, songsToDelete[playlistLen], deleteIndex = 0;
    bool exit = false;

    cout << "========" << playlist.getName() << "========" << endl;
    cout << playlist;
    cout << playlistLen+1 << "Return to Playlist Options Menu." << endl;
    cout << playlistLen+2 << "Exit Program." << endl;

    while (userSelection <= playlistLen && deleteIndex <= playlistLen){
        cout << "Select a song: " << endl;
        cin >> userSelection;

        if (userSelection == playlistLen+1){
            exit = false;
        }

        else if (userSelection == playlistLen+2){
            exit = true;
        }

        else{
            songsToDelete[deleteIndex] = userSelection;
            deleteIndex++;
        }
    }

    if (deleteIndex == playlistLen){
        exit = deletePlaylist(playlist);
    }

    else{
        for (int i = 0; i < deleteIndex; i++){
            playlist.deleteSongFromIndex(songsToDelete[i]);
        }
    }
    //when user selects song DO NOT update playlist until all songs have been selected, then delete all at once

    //if user deletes all song in playlist, delete the .txt file from directory

    //if only some songs were deleted, once exiting this function, write updated playlist to file
    return exit;
}

bool addSongToPlaylist(Playlist& playlist, const Playlist& all){
    //provide user a menu shows all songs that can be added to a playlist
    int libraryLen = all.getNumSongsLoaded();
    int userSelection = 0, insertionPoint;
    bool exit;
    char addEnd;

    cout << all;
    cout << libraryLen+1 << "Return to Playlist Options Menu." << endl;
    cout << libraryLen+2 << "Exit Program." << endl;
    //when a user selects a song to add, prompt user to add to end or not
    //if yes, then add directly to end using + operator overload
    //if no, then add to index location prompted by user
    while (userSelection <= libraryLen){
        cout << "Select a song to add: " << endl;
        cin >> userSelection;

        if (userSelection == libraryLen+1){
            exit = false;
        }

        else if (userSelection == libraryLen+2){
            exit = true;
        }

        else{
            cout << "Add song to end of playlist (y/n)? " << endl;
            cin >> addEnd;

            switch (addEnd){
                case 'y':
                    playlist + *all.getSongAtIndex(userSelection);
                case 'n':
                    cout << "========" << playlist.getName() << "========" << endl;
                    cout << playlist;
                    cout << "Which song would you like to insert before? ";
                    cin >> insertionPoint;
                    playlist.addSongAtIndex(insertionPoint, userSelection, all);
            }
        }
    }
    //double check if song is already in playlist
    //if it is, do not add a duplicate
    return exit;
}

bool modifyPlaylist(Playlist& playlist, const Playlist& all){
    promptTypesModificationSelection();
    bool exit;
    int userModType, songChoice;
    do{
        cout << "What would you like to do? ";
        cin >> userModType;
    }while(userModType< 1 || userModType > 4);
    system("clear");
    switch(userModType){
        case 1:
            exit = deleteSongFromPlaylist(playlist);
            break;
        case 2:
            exit = addSongToPlaylist(playlist, all);
            break;
        case 3:
            exit = false;
            break;
        case 4: 
            exit = true;
            break;
    }
    if(playlist.getFirstSong() != nullptr){
        writePlaylistToFile(playlist);
    }
    return exit;
}

bool deletePlaylist(Playlist& playlist){
    //deletes all songs in playlist
    //then deletes the playlist object
    //dont forget to remove playlist text file from directory as well
    string playlistName = playlist.getName() + ".txt";
    remove(playlistName.c_str());

    Song* temp = new Song;
    Song* temp1 = new Song;
    temp = playlist.getFirstSong();
    temp1 = temp->getNextSong();

    while (temp != nullptr){
        delete temp;
        temp = temp1;
        temp1 = temp1->getNextSong();
    }
    delete temp1;

    return false;
}

bool manageExistingPlaylists(const Playlist& all, Playlist& selectedPlaylist){
    //this is the main menu from which most major choices are made
    //each time this function is called a new array of playlists and fills each object with the relevant data
    string* playlistNames = new string[100];
    Playlist* playlists = new Playlist[5];
    int numPlaylists = getExistingPlaylists(playlistNames), userSelection = 0, userSelection1 = 0;
    bool exit;

    loadExistingPlaylists(playlistNames, playlists, numPlaylists);

    cout << "The following playlists are currently available:" << endl;
    for (int i = 0; i < numPlaylists; i++){
        cout << i+1 << playlistNames[i] << endl;
        string playlistName = playlistNames[i] + ".txt";
    }
    cout << numPlaylists+1 << "Return to Main Menu." << endl;
    cout << numPlaylists+2 << "Exit Program." << endl;

    while (userSelection <= numPlaylists){
        cout << "Which playlist would you like to load? ";
        cin >> userSelection;

        if (userSelection == numPlaylists+1){
            exit = false;
        }

        else if (userSelection == numPlaylists+2){
            exit = true;
        }

        else{
            Playlist* selectedPlaylist = new Playlist;
            selectedPlaylist = &playlists[userSelection];
            cout << "========" << selectedPlaylist->getName() << "========" << endl;
            cout << selectedPlaylist;

            cout << "1. Modify Playlist." << endl;
            cout << "2. Delete Playlist." << endl;
            cout << "3. Return to Main Menu." << endl;
            cout << "4. Exit Program." << endl;

            while (userSelection1 > 4 && userSelection1 <= 0){
                cout << "What would you like to do with " << selectedPlaylist->getName() << "? ";
                cin >> userSelection1;
            }

            switch (userSelection1){
                case 1:
                    modifyPlaylist(*selectedPlaylist, all);
                case 2:
                    deletePlaylist(*selectedPlaylist);
                case 3:
                    exit = false;
                case 4:
                    exit = true;

            }
        }
    }
    return exit;
    //an option to return to main menu should be provided
    //an option to exit program directly should be provided
    
    //user should select what playlist they want to manage
    //the next menu should then prompt user if they want modify or delete

    //if they want to modify call modify helper
    //if they want to delete call delete helper
}

//this function iterates through current working directory to look for any files ending with .txt
//any file with .txt is considered a playlist
int getExistingPlaylists(string* existingPlaylists){
    DIR *directoryPtr = opendir(".");
    struct dirent *directoryEntry;
    int numPlaylists = 0;
    if (directoryPtr) {
        while ((directoryEntry = readdir(directoryPtr)) != NULL) {
            string filename = directoryEntry->d_name;
            string empty = "";
            if(filename != "dbSmall.txt" && filename != "dbLarge.txt"){
                for(int i = filename.size()/sizeof('c')-4; i< filename.size()/sizeof('c'); i++){
                    empty += filename[i];
                }
                if(empty == ".txt"){
                    string cleanedFilename = "";
                    for(int i = 0; i< filename.size()/sizeof('a') -4; i++){
                        cleanedFilename += filename[i];
                    }
                    existingPlaylists[numPlaylists] = cleanedFilename;
                    numPlaylists++;
                }
            }
        }
            
    closedir(directoryPtr); //close all directory
    }
    return numPlaylists;
}

//song friend function directly cout (see below)
ostream & operator << (ostream &out, const Song &s){
    //just need to output title
    out << s.getTitle();
    return out;
}
//playlist friend function directly cout using song friend function
ostream& operator << (ostream &out, const Playlist &p){
    //will need to iterate through playlist to output all songs
    Song* temp = new Song;
    temp = p.getFirstSong();

    int currentSong = 1;
    while (temp != nullptr){
        out << currentSong << " " << temp->getTitle() << endl;
        currentSong++;
        temp = temp->getNextSong();
    }
    delete temp;
    return out;
}

void getUserEntry(int* entry){
    cin >> *entry;
}

void loadExistingPlaylists(string* playlistNames, Playlist* playlists, int numPlaylists){
    Playlist* temp = new Playlist[numPlaylists];
    for (int i = 0; i < numPlaylists; i++){
        ifstream currentPlaylist(playlistNames[i]);
        readData(currentPlaylist, temp[i]);
        currentPlaylist.close();
    }
    playlists = temp;
}
