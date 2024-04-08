#include "helpers.h"
//this will not compile out of the box
//need to implement the red underlined methods
int main(){
    Playlist* all = new Playlist;
    all->setName("dbLarge");
    ifstream inFile("dbLarge.txt");
    readData(inFile, *all);

    int userEntry;
    bool exitProgram;
    do{
        Playlist* newest = new Playlist;
        Playlist* selectedPlaylist = new Playlist;
        system("clear");
        displayMainMenu();
        do{
            cout << "Make your selection: ";
            getUserEntry(&userEntry);
        }while(userEntry < 1 && userEntry > 3);
        system("clear");
        switch(userEntry){
            case 1:
                exitProgram = manageExistingPlaylists(*all, *newest); //implement delete, modify, and display
                if(newest->getNumSongsLoaded() == 0){
                    delete newest;
                }
                if(exitProgram){
                    return 0;
                }
                break;
            case 2:
                exitProgram = createNewPlaylist(*all, *newest);
                if(exitProgram){
                    return 0;
                }
                break;
            case 3:
            exitProgram = true;
                break; //user exit
            default:
                cout <<"Invalid option entered. Please try again." <<endl;
                break;
        }
    }while(userEntry != 3 && !exitProgram);
    return 0;
}
