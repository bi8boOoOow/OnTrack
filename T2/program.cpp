#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"
#include <string>

//using std::to_string;

/**
 * @brief represents a song and store its relavant data
 * 
 */
struct song_data
{
    string name;   // name for the song
    string id;     // unique identifier for the song
    string path;   // a path to the file the song is loaded from
    bool is_loved; // a loved status
    int times;     // the number of times played
};

/**
 * @brief represents a music player and store its relavant data
 *
 */
struct music_player_data
{
    dynamic_array<song_data> songs; // the songs that the music player store
    int next_song_id = 0;        // the id for the next song
};

/**
 * @brief this procedure adds a new song to users' music player
 * 
 * @param music_player the user's music player to be add the new song into
 */
void add_new_song (music_player_data &music_player) {
    // creating a new song
    song_data new_song;
    new_song.name = read_string("Input song name: ");
    new_song.path = read_string("Input song path: ");
    new_song.is_loved = read_string("Input if you love this song (YES/NO): ") == "YES"? 1 : 0;
    new_song.times = 0;
    new_song.id = "song-" + std::to_string(music_player.next_song_id);

    // adding the created song into the music player
    music_player.songs.add(new_song);

    // incrementing the next song id
    music_player.next_song_id += 1;

    //load the file so that the song can be played
    load_music(new_song.id, new_song.path);

    // displaying a msg that the song has been successfully added
    write_line("new song added successfully!");
    write_line();
}

/**
 * @brief helper function for update_song and play_song, it selete the target song of the user
 * 
 * @param music_player the music list the the user choose songs from
 * @return int the id of the choosen target song
 */
int select_song(music_player_data &music_player) {
    // ask the user to input a name
    string tartget_name = read_string("Input song name: ");

    // find the songs with name that contains target text
    dynamic_array<int> possible_songs_ids;

    for (int i = 0; i < music_player.next_song_id; i++) {
        if (contains(music_player.songs[i].name, tartget_name)) {
            possible_songs_ids.add(i);
        }
    }

    // show the numbered list of all the songs that contain that text to choose from 
    write_line("Possible songs: ");
    for (int i = 0; i < possible_songs_ids.length(); i++) {
        write_line(std::to_string(i + 1) + ": " + music_player.songs[possible_songs_ids[i]].name);
    }

    int target_song_id = read_integer("Input the number of the song you want to modify: ");
    target_song_id = possible_songs_ids[target_song_id];

    return target_song_id;
}

/**
 * @brief the user can update the detailed of one or multiple songs
 * 
 * @param music_player the user's music player where songs are updated
 */
void update_song(music_player_data &music_player) {
    int target_song_id = select_song(music_player);
    bool is_updating = true;

    // entsure that the user still want to update the the music list is updateable
    while (is_updating == true) {
        // show the users the details of the song
        write_line("Details of the choosen song: ");
        write_line("name: " + music_player.songs[target_song_id].name);
        write_line("path: " + music_player.songs[target_song_id].path);
        write_line("times played: " + std::to_string(music_player.songs[target_song_id].times));
        string is_loved = music_player.songs[target_song_id].is_loved == 1? "yes": "no";
        write_line("is the song loved: " + is_loved);

        // show users the options for updating
        write_line("Options for updating song: ");
        write_line("1. Update name");
        write_line("2. Toggle loved");
        write_line("3. Reset times played");
        write_line("4. Delete");
        write_line("5. Quit update");

        // updating detail
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
                music_player.songs.remove_at(target_song_id);
                // TODO: do we need to update ids?
                break;
            case 5:
                is_updating = false;
                break;
            default:
                write_line("Invalid choise. Pick option in the list");
        }
    }


    // displaying a msg that the song has been successfully updated
    write_line("new song updated successfully!");
    write_line();
}

/**
 * @brief the user wil select a song fist and play it
 * 
 * @param music_player the users' music list that conatining the song to be played
 */
void play_song(music_player_data &music_player) {
    int target_song_id = select_song(music_player);

    // update the times the song is played
    music_player.songs[target_song_id].times += 1;

    // play the music
    write_line("Music successfully playing...");
    play_music(music_player.songs[target_song_id].id);
    write_line();
}

/**
 * @brief this function will pause or resume the song depending on whether the song is playing currently
 * 
 */
void pause_resume_song() {
    if (music_playing()) { // if the music is currently playing then pause
        pause_music();
        write_line("music paused");
    } else { // other wise resume
        resume_music();
        write_line("music resumed");
    }
    write_line();
}


/**
 * @brief printing the report generated based on the users's music play list
 * 
 * @param music_player the users' music list that the report will be generated based on
 */
void print_status(music_player_data &music_player) {
    write_line("Reort: ");

    int play_list_len = music_player.songs.length();
    // number of songs the user hav ein the music list
    write_line("Number of songs: " + std::to_string(play_list_len));

    // totle number of songs played

    int total_times = 0;
    for (int i = 0; i < play_list_len; i++) {
        total_times += music_player.songs[i].times;
    }
    write_line("The number of songs played" + std::to_string(total_times));

    // total number of loved songs
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