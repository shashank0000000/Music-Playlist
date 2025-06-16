#include <iostream>
#include <string>

using namespace std;

// Node for each song
struct Song {
    string title;
    string artist;
    Song* next;
    Song* prev;

    Song(string t, string a) {
        title = t;
        artist = a;
        next = prev = nullptr;
    }
};

// Playlist class using circular doubly linked list
class Playlist {
private:
    Song* head;     // First song
    Song* current;  // Currently playing

public:
    Playlist() {
        head = nullptr;
        current = nullptr;
    }

    // Add a song at the end
    void addSong(const string& title, const string& artist) {
        Song* newSong = new Song(title, artist);

        if (!head) {
            head = newSong;
            head->next = head->prev = head;
            current = head;
        } else {
            Song* tail = head->prev;

            tail->next = newSong;
            newSong->prev = tail;
            newSong->next = head;
            head->prev = newSong;
        }

        cout << "Added: " << title << " by " << artist << endl;
    }

    // Delete the current song
    void deleteCurrentSong() {
        if (!current) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "Deleted: " << current->title << " by " << current->artist << endl;

        if (current->next == current) {
            delete current;
            head = current = nullptr;
            return;
        }

        Song* prevSong = current->prev;
        Song* nextSong = current->next;

        prevSong->next = nextSong;
        nextSong->prev = prevSong;

        if (current == head)
            head = nextSong;

        delete current;
        current = nextSong;
    }

    // Play next song
    void playNext() {
        if (!current) {
            cout << "Playlist is empty.\n";
            return;
        }
        current = current->next;
        showCurrent();
    }

    // Play previous song
    void playPrevious() {
        if (!current) {
            cout << "Playlist is empty.\n";
            return;
        }
        current = current->prev;
        showCurrent();
    }

    // Show the currently playing song
    void showCurrent() {
        if (!current) {
            cout << "No song is currently playing.\n";
            return;
        }
        cout << "Now Playing: " << current->title << " by " << current->artist << endl;
    }

    // Show all songs in the playlist
    void showAllSongs() {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "All Songs in Playlist:\n";

        Song* temp = head;
        do {
            cout << "- " << temp->title << " by " << temp->artist << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // Destructor to free memory
    ~Playlist() {
        if (!head) return;

        Song* temp = head->next;
        while (temp != head) {
            Song* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        delete head;
    }
};

// Main function with menu
int main() {
    Playlist playlist;
    int choice;
    string title, artist;

    do {
        cout << "\n====== Music Playlist ======\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Current Song\n";
        cout << "3. Play Next Song\n";
        cout << "4. Play Previous Song\n";
        cout << "5. Show Current Song\n";
        cout << "6. Show All Songs\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                playlist.addSong(title, artist);
                break;

            case 2:
                playlist.deleteCurrentSong();
                break;

            case 3:
                playlist.playNext();
                break;

            case 4:
                playlist.playPrevious();
                break;

            case 5:
                playlist.showCurrent();
                break;

            case 6:
                playlist.showAllSongs();
                break;

            case 0:
                cout << "Exiting Playlist. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
