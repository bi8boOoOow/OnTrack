#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"
#include <string>

// Represents a song stored in the music player
struct song_data
{
    string name;
    string id;
    string path;
    bool is_loved;
    int times;
};

// Represents the user's music player
struct music_player_data
{
    dynamic_array<song_data> songs;
    int next_song_id = 0;
};

// Adds a new song to the music player
void add_new_song (music_player_data &music_player) {
    song_data new_song;

    new_song.name = read_string("Input song name: ");
    new_song.path = read_string("Input song path: ");
    new_song.is_loved = read_string("Input if you love this song (YES/NO): ") == "YES"? 1 : 0;
    new_song.times = 0;
    new_song.id = "song-" + std::to_string(music_player.next_song_id);

    music_player.songs.add(new_song);
    music_player.next_song_id += 1;

    // Load music so it can be played later
    load_music(new_song.id, new_song.path);

    write_line("new song added successfully!");
    write_line();
}

// Allows the user to select a song based on partial name matching
int select_song(music_player_data &music_player) {
    string tartget_name = read_string("Input song name: ");
    dynamic_array<int> possible_songs_ids;

    // Collect all songs whose names contain the input text
    for (int i = 0; i < music_player.next_song_id; i++) {
        if (contains(music_player.songs[i].name, tartget_name)) {
            possible_songs_ids.add(i);
        }
    }

    write_line("Possible songs: ");
    for (int i = 0; i < possible_songs_ids.length(); i++) {
        write_line(std::to_string(i + 1) + ": " + music_player.songs[possible_songs_ids[i]].name);
    }

    int target_song_id = read_integer("Input the number of the song you want to modify: ");
    target_song_id = possible_songs_ids[target_song_id];

    return target_song_id;
}

// Updates details of a selected song
void update_song(music_player_data &music_player) {
    int target_song_id = select_song(music_player);
    bool is_updating = true;

    while (is_updating == true) {
        write_line("Details of the choosen song: ");
        write_line("name: " + music_player.songs[target_song_id].name);
        write_line("path: " + music_player.songs[target_song_id].path);
        write_line("times played: " + std::to_string(music_player.songs[target_song_id].times));
        string is_loved = music_player.songs[target_song_id].is_loved == 1? "yes": "no";
        write_line("is the song loved: " + is_loved);

        write_line("Options for updating song: ");
        write_line("1. Update name");
        write_line("2. Toggle loved");
        write_line("3. Reset times played");
        write_line("4. Delete");
        write_line("5. Quit update");

        int user_option = read_integer("Input the Option you choose from above: ");
        switch (user_option) {
            case 1:
                music_player.songs[target_song_id].name = read_string("Input new name: ");
                break;
            case 2:
                music_player.songs[target_song_id].is_loved = 1 - music_player.songs[target_song_id].is_loved;
                break;
            case 3:
                music_player.songs[target_song_id].times = 0;
                break;
            case 4:
                // Remove the selected song from the list
                music_player.songs.remove_at(target_song_id);
                break;
            case 5:
                is_updating = false;
                break;
            default:
                write_line("Invalid choise. Pick option in the list");
        }
    }

    write_line("new song updated successfully!");
    write_line();
}

// Plays a selected song and updates play count
void play_song(music_player_data &music_player) {
    int target_song_id = select_song(music_player);

    // Track how many times the song has been played
    music_player.songs[target_song_id].times += 1;

    write_line("Music successfully playing...");
    play_music(music_player.songs[target_song_id].id);
    write_line();
}

// Pauses or resumes music playback depending on current state
void pause_resume_song() {
    if (music_playing()) {
        pause_music();
        write_line("music paused");
    } else {
        resume_music();
        write_line("music resumed");
    }
    write_line();
}

// Prints a summary report of the music player
void print_status(music_player_data &music_player) {
    write_line("Reort: ");

    int play_list_len = music_player.songs.length();
    write_line("Number of songs: " + std::to_string(play_list_len));

    int total_times = 0;
    for (int i = 0; i < play_list_len; i++) {
        total_times += music_player.songs[i].times;
    }
    write_line("The number of songs played" + std::to_string(total_times));

    int total_loved_songs = 0;
    for (int i = 0; i < play_list_len; i++) {
        if (music_player.songs[i].is_loved) {
            total_loved_songs += 1;
        }
    }
    write_line("Total number of loved songs: " + std::to_string(total_loved_songs));
}

int main() {
    music_player_data music_player;
    music_player.next_song_id = 0;

    bool is_running = true;
    while (is_running)
    {
        write_line("Display music player options: ");
        write_line("1. Add a song");
        write_line("2. Update a song");
        write_line("3. Play a song");
        write_line("4. Pause/Resume");
        write_line("5. Print status");
        write_line("6. Quit");

        int choice = read_integer("Choose option: ");
        switch (choice)
        {
            case 1: 
                add_new_song(music_player);      
                break;
            case 2: 
                update_song(music_player);   
                break;
            case 3: 
                play_song(music_player);     
                break;
            case 4: 
                pause_resume_song();    
                break;
            case 5: 
                print_status(music_player);  
                break;
            case 6: 
                is_running = false;       
                break;
            default: 
                write_line("Invalid option, option not in the list. choose vali option.");
        }
    }

    write_line("end of program!");
    return 0;
}