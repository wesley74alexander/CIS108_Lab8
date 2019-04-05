using namespace std;
#include "MusicDB_Sort.h"
#include "song.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  music::Song song;
  string file = "MusicFile.bin";

  vector<char*> menu = { //**use an array instead** //or compile with c++ 11 or later to define a vector of static strings
     "===========================================",
     "add : Add a new song to the music database",
     "list : List the songs in the music database",
     "save : Save the music database",
     "help : Display this menu",
     "exit : Exit the Program",
     "clear : Empty the music database",
     "sort : Sort the songs in the music database",
     "find : Search for a song title in the music database",
     "===========================================\n"
  };

  get_menu(menu); //Prints the menu line by line when the program first runs.
  string command;
  string sortcom;
  load_vector(file);
  int count = get_global_count();

  while (true) { //Reads commands from user until a break is encountered.
    cout << "\n> ";
    cin >> command;

      if (command == "add") {
        add_song(song);
        count = get_global_count();
      }
      //must use cout to prompt user for data
      //use cin to read user entered data from the console
      else if (command == "list") {
        list_song();
      }
      //must use an ifstream to read the contents of the file
      //use cout to print the file from ifstream object to console
      else if (command == "save" && count <= 8) {
        save_song(song, file);
      }
      else if (command == "save" && count > 8) { //when song saves, have it write count on first line of file. Then, you can just get that count from the first line and not output the first line when list is called
        cout << "Your file is full!";
      }
      //must dump additions from ofstream buffer into a file
      else if (command == "help") {
        get_menu(menu); //Prints menu line by line when user enters "help"
      }

      else if (command == "exit") {
        cout << "Goodbye!";
        break;
      }
      else if (command == "clear") {
        clear_file(file);
      }
      else if (command == "sort") {
        cout << "Sort by title, artist, or year? \n> ";
        cin >> sortcom;
        sortby(sortcom);
      }
      else if (command == "find") {
        find_song();
      }
      else {
        cout << "Enter one of the following commands!\n";
        get_menu(menu);
      };
  };
  return 0;
};
