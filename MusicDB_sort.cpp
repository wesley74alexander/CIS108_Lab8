#include "song.h"
#include "MusicDB_Sort.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <id3/tag.h>
#include "id3/misc_support.h"

using namespace std;

vector<music::Song> mysongs;

void get_menu(vector<char*> menu){ //Prints menu one line at a time
    for (int i = 0; i < menu.size(); i++){
      cout << menu[i] << endl;
    };
  };//must compile with c++ 11 or later for get_menu to work

music::music_genre str_toenum(string str) { //real function to take in a string and return an enum genre
   if (str == "blues" || str == "Blues") {
     return music::music_genre::Blues;
   }
   else if (str == "country" || str == "Country") {
     return music::music_genre::Country;
   }
   else if (str == "electronic" || str == "Electronic" || str == "edm" || str == "EDM") {
     return music::music_genre::Electronic;
   }
   else if (str == "folk" || str == "Folk") {
     return music::music_genre::Folk;
   }
   else if (str == "hiphop" || str == "HipHop" || str == "Hip Hop" || str == "hip hop" || str == "Hip-Hop" || str == "rap" || str == "Rap") {
     return music::music_genre::HipHop;
   }
   else if (str == "jazz" || str == "Jazz") {
     return music::music_genre::Jazz;
   }
   else if (str == "latin" || str == "Latin") {
     return music::music_genre::Latin;
   }
   else if (str == "pop" || str == "Pop") {
     return music::music_genre::Pop;
   }
   else if (str == "rock" || str == "Rock"){
     return music::music_genre::Rock;
   }
   else {
     return music::music_genre::fail_case;
   };
};

string enum_tostring(music::music_genre genre_index) {
   if (genre_index == 0) {
     return "Other";
   }
   else if (genre_index == 1) {
     return "Blues";
   }
   else if (genre_index == 2) {
     return "Country";
   }
   else if (genre_index == 3) {
     return "Electronic";
   }
   else if (genre_index == 4) {
     return "Folk";
   }
   else if (genre_index == 5) {
     return "Hip-Hop";
   }
   else if (genre_index == 6) {
     return "Jazz";
   }
   else if (genre_index == 7) {
     return "Latin";
   }
   else if (genre_index == 8) {
     return "Pop";
   }
   else if (genre_index == 9) {
     return "Rock";
   };
};

void add_song(music::Song& s){ //reads user input into members of s
    string inputstr;
    cout << "Enter song title: ";
    getline(cin >> ws, inputstr); //**second parameter must be a string, s.title is a character array** **use string copy function**
    if (inputstr.length() > sizeof(s.title))
      throw runtime_error("Song title is too large!"); //used runtime_error rather than exception because string args to exception are a VS extension
    else
      strcpy(s.title, inputstr.c_str());
    cout << "Enter artist: ";
    getline(cin, inputstr);
    if (inputstr.length() > sizeof(s.artist))
      throw runtime_error("Artist name is too large!");
    else
      strcpy(s.artist, inputstr.c_str());
    cout << "Enter album name: ";
    getline(cin, inputstr);
    if (inputstr.length() > sizeof(s.artist))
      throw runtime_error("Album name is too large!");
    else
      strcpy(s.album, inputstr.c_str());
    cout << "Enter genre: ";
    getline(cin, inputstr);
    s.genre = str_toenum(inputstr);
    cout << "Enter track #: ";
    getline(cin , inputstr);
    try
    {
      s.track = stoi(inputstr);
    }
    catch(invalid_argument)
    {
      throw runtime_error("Numeric input required for track field");
    }
    catch(out_of_range)
    {
      throw runtime_error("Input is too large!");
    }
    cout << "Enter year: ";
    getline(cin, inputstr);
    try
    {
      int iyear = stoi(inputstr);
      if (iyear <= 2019)
        s.year = iyear;
      else
        throw runtime_error("You can't add songs from the future!");
    }
    catch(invalid_argument)
    {
      throw runtime_error("Numeric input required for year field");
    }
    catch(out_of_range)
    {
      throw runtime_error("Input is too large!");
    }
    mysongs.push_back(s);
};


void save_song(music::Song& s, string fname){ //writes the members of Song s to a file // must declare count before calling func
    ofstream outfile;
    outfile.open(fname, ios::out | ios::binary);
    auto mysongs_itr = mysongs.begin();
    while (mysongs_itr != mysongs.end()){
      music::Song s = *mysongs_itr;
      outfile.write((char*)&s ,sizeof(s));
      mysongs_itr ++;
    }
     //writes entire song to binary file rather than member by member to text file like lab5. This is much simpler. See http://courses.cs.vt.edu/~cs2604/fall00/binio.html
    outfile.close(); //**save from vector rather than most recent s entry. set flag to overwrite rather than append to avoid repeats.**
};

void clear_file(string fname){
    ofstream cfile;
    mysongs.clear();
    cfile.open(fname, ios:: binary | ios::out | ios::trunc);
    cfile.close();
};


void list_song(){
  int count = 0;
  vector<music::Song>::iterator songs_itr;
  music::Song s;

  for (songs_itr = mysongs.begin(); songs_itr < mysongs.end(); songs_itr ++){
    s = *songs_itr; //sets s equal to the element pointed to by songs_itr
    cout << "Song #: " << count + 1 << endl;
    cout << " Title: " << s.title << endl;
    cout << " Artist: " << s.artist << endl;
    cout << " Album: " << s.album << endl;
    cout << " Genre: " << enum_tostring(s.genre) << endl;
    cout << " Track #: " << s.track << endl;
    cout << " Year: " << s.year << endl;
    count ++;
  };
};


int get_global_count(){
  int global_count = 0;
  vector<music::Song>::iterator songs_itr;

  for (songs_itr = mysongs.begin(); songs_itr < mysongs.end(); songs_itr ++){
    global_count ++;
  };
  return global_count;
};


void load_vector(string fname){
  music::Song s;
  ifstream infile;
  mysongs.clear();

	try
	{
		infile.open(fname, ios::in | ios::binary);
		infile.exceptions(ifstream::failbit);

		while (infile.is_open() && infile.peek() != EOF)
		{
			infile.exceptions(ifstream::badbit);
			infile.read((char*)& s, sizeof(s));
			mysongs.push_back(s);
		};
		infile.close();
	}
  catch (const ifstream::failure& e) {
    cout << "Error opening file " << fname << endl;
  }
};

bool sort_title(music::Song& ls, music::Song& rs){
  return ls.title[0] < rs.title[0];
};

bool sort_artist(music::Song& ls, music::Song& rs){
  return ls.artist[0] < rs.artist[0];
};

bool sort_year(music::Song& ls, music::Song& rs){
  return ls.year < rs.year;
};

void sortby(string c) { //I'm doing all of this in a function because mysongs vector is never declared in Main.cpp
  if (c == "title") {
    sort(mysongs.begin(), mysongs.end(), sort_title);
  }
  else if (c == "artist") {
    sort(mysongs.begin(), mysongs.end(), sort_artist);
  }
  else if (c == "year") {
    sort(mysongs.begin(), mysongs.end(), sort_year);
  }
  else {
    cout << "You can't sort by that! \n";
  };
};

music::Song find_song() {
  string title_to_find;
  music::Song found;
  music::Song empty;
  cout << "Enter a title to search: ";
  cin >> title_to_find;
  transform(title_to_find.begin(), title_to_find.end(), title_to_find.begin(), ::tolower);
  auto it = find_if(mysongs.begin(), mysongs.end(), [&] (music::Song& el) -> bool {title_to_find == el.title;});
  if (it != mysongs.end()) {
    int idx = distance(mysongs.begin(), it);
    found = mysongs[idx];
  }
  else {
    cout << "Song not found \n";
    found = empty;
  };
  return found; // always returns not found... possibly has something with comparison not used warning on line 253
};

void import_song() {
	string song_path;
	music::Song s;
	char* imported_tag; //not sure why I'm getting errors when imported_tag is type string or char array
	cout << "Enter full path to song file \n";
	cin >> song_path;
	ID3_Tag my_tag(song_path.c_str());
	ID3_Tag* ptr_tag = &my_tag;
	
	imported_tag = ID3_GetTitle(ptr_tag); //retreive title tag
	strcpy_s(s.title, imported_tag); //copy retreived title tag to title member of Song s

	imported_tag = ID3_GetArtist(ptr_tag);//retreive artist tag
	strcpy_s(s.artist, imported_tag);//copy retreived artist tag to artist member of Song s

	imported_tag = ID3_GetAlbum(ptr_tag);//retreive album tag
	strcpy_s(s.album, imported_tag);//copy retreived album tag to album member of Song s

	imported_tag = ID3_GetTrack(ptr_tag);//retreive track tag as string
	s.track = stoi(imported_tag);//convert string track number to an int and store in track member of Song s

	imported_tag = ID3_GetYear(ptr_tag);//retreive year tag as string
	s.year = stoi(imported_tag);//convert string year to an int and store in year member of Song s

	imported_tag = ID3_GetGenre(ptr_tag);//retreive genre tag
	s.genre = str_toenum(imported_tag);//convert string genre to an enum

	mysongs.push_back(s); //add new song to the global vector
	
};



		//add song to vec
};
