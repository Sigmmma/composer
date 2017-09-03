 ██████╗ ██████╗ ███╗   ███╗██████╗  ██████╗ ███████╗███████╗██████╗ 
██╔════╝██╔═══██╗████╗ ████║██╔══██╗██╔═══██╗██╔════╝██╔════╝██╔══██╗
██║     ██║   ██║██╔████╔██║██████╔╝██║   ██║███████╗█████╗  ██████╔╝
██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██║   ██║╚════██║██╔══╝  ██╔══██╗
╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ╚██████╔╝███████║███████╗██║  ██║
 ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝

================================================================================

What is Composer:

  Composer is a music player that operates exclusively on the sound
  and sound_looping files used in the "Halo" game series. Composer
  is currently only capable of using Halo 1 sound and sound_looping
  files, but there are plans to expand this to later Halo games.

  Composer is also my first C++ program(and will be my first mobile
  device program thanks to JUCE when I get it compiling for Android).


Why use Composer:

  Halo's CD soundtrack is pretty amazing(which I recommend you buy),
  but it isn't the same thing as the dynamic music you hear ingame.
  A CD soundtrack is static(always the same content and length),
  whereas video game BGM is usually designed to seamlessly loop an
  infinite number of times until it needs to end. Halo goes a step
  further by using permutations, skip fractions, and alternate loops.

  Permutations keep things from getting too repetative by virtue of
  being different variants of the loop that can be played in any order.

  Skip fractions specify how often a permutation will be skipped if it
  is about to be selected to be played(introduces randomness).

  Alternate loops are just like loops(can have their own permutations
  with their own skip fractions), and usually sound pretty similar to
  the loops, except the game designers control when they are activated.
  These are used for when the designers want the music to keep playing,
  but need to to seamlessly change its feel(change from a tense version
  of a track to a heart pounding one when you get into battle).


  Composer allows you to listen to all the soundtracks as they would be
  heard ingame, and allows you to customize playback using "commands".
  You can specify how long to play a track, when to switch to alternate
  permutations, which permutations to play(ignores skip fractions), how
  many times to repeat a command, whether or not to play permutations
  in a "normal" way(in ascending order and using skip fractions), etc.
  This is the reason for Composer's name, you compose the music yourself.

================================================================================

Installation/Setup:

  ---DISCLAIMER---
  Composer operates on the sound and sound_looping game files that
  are used to make a Halo map. These files are called "tags", and
  are a proprietary binary file format designed to work with Halo's
  development tools as well as the game itself.

  Composer does NOT come with any sound or sound_looping files,
  nor is it capable of producing them. If you wish to listen to
  music from the Halo games you must obtain the files yourself.
  I will not provide the files, nor will I explain how to rip the
  sound tags from Halo maps.
  ---DISCLAIMER---

  1: Make a folder to store your playlists(there should be an empty
     "playlists" folder that came with Composer).

  2: Make or locate your tags directory and put the sound_looping
     and sound tags you want to play in it.

  3: Run Composer.exe, go to the "Settings" panel, set the playlists
     folder to the one you just created.

  4: Click "New playlist" and then set its tags directory to the one
     you just created or located.

  5: You are ready to add tracks to play. Click "Save playlist" after
     you are done editing it. This is the only way to save edits to
     the playlist. The playlist that was last open when you exit
     will be automatically opened when you run Composer again.


How to use Composer:

  Once Composer is setup you are able to add tracks to the current
  playlist and specify how to play them. The Playlist, Commands, and
  Settings tabs are where you do all of these things and more.

  Here is a breakdown of each tab and their widgets:

  Playlist:
    The Playlist tab is where you manage the tracks(sound_looping files)
    in the playlist. The currently playing track will have an arrow off
    to the left pointing to it. The currently SELECTED track will be
    highlighted in white.

    Aside from the "Add' button, all controls on the playlist tab will
    affect the currently SELECTED track, not the track that is playing.

    * Add
        Adds a new track to the end of the playlist.

    * Remove
        Removes the currently selected track from the playlist.

    * Shift up
        Shifts the currently selected track up by 1.

    * Shift down
        Shifts the currently selected track down by 1.

    * Loop
        Loops back to the beginning when the last track is played.

    * Shuffle
        Plays the tracks in a randomized order. Clicking this will
        force "Loop" to be on as the playlist wont be read linearly.

    * Track playtime
        Number of seconds to play the currently selected track.
        If set to zero, the track will play forever.
        When a track is added to the playlist, this will default to
        180 seconds(3 minutes). Max time is 1 hour(3600 seconds).

        NOTE: To the left of the playtime slider is the number of
        seconds the currently PLAYING track has played.

        NOTE2: The playtime you specify is not a hard limit, but rather
        the minimum amount of time to play before trying to end the music.
        The current permutation MUST finish before entering the end phase.
        During the end phase, either an end sound will play or the
        permutations will continue to play with a fadeout applied to them.


  Commands:
    The Commands tab allows you to carefully tweak how the currently
    PLAYING track will play. Double click a track in the playlist and
    then click "Pause". The Commands tab will now be populated.

    * Add
        Adds a new command to the end of the command list.

    * Remove
        Removes the currently selected command from the command list.

    * Shift up
        Shifts the currently selected command up by 1.

    * Shift down
        Shifts the currently selected command down by 1.


    * Permutation
      Allows you to tweak how the currently SELECTED command specifies
      a permutation should be chosen. Also displays the permutation
      currently being played in the section's left central box.

      - Alt
          Play the alternate loops(if available).

      - Any
          Randomly choose a permutation from the available ones.

      - Normal
          Play permutations in the way Halo normally would.

      - Permutation to play
          If "Any" and "Normal" are not selected, you can specify which
          permutation to play with the plus and minus buttons.


    * Loop count
      Allows you to tweak how many times the currently SELECTED command
      should be repeated. Also displays the current loop iteration in
      the section's left central box.

      - Skip
          Skip over executing this command.
          Used to temporarily disable commands for testing.

      - Endless
          Execute this command endlessly until the track ends.

      - Number of loops
          If Endless is not selected, you can specify how many times to
          execute this command before going on to the next one.


  Settings:
    The settings tab is where you can edit some of Composer's config
    settings as well as fixing a playlist's tags directory location
    if you want to transfer the playlist to another device.

    * New playlist
        Unloads the current playlist(doesnt save) and makes a new one.

    * Load playlist
        Unloads the current playlist(doesnt save) and loads one from a file.

    * Save playlist
        Asks you where to save the current playlist to and saves it there.

    * Change tags directory
        Allows you to set the tags directory of the currently loaded
        playlist. Used mainly for transferring playlists between devices.

    * Change playlists directory
        Allows you to set the default directory for loading playlists from
        and saving them to.

================================================================================

Contact:

  * mosesbobadilla@gmail.com


Credits:

  * Devin Bobadilla(author of Composer)
  * Julian Storer(author of the kickass JUCE framework that Composer uses)


License:

  Copyright (C) 2017 Devin Bobadilla

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

================================================================================

Known bugs/issues:

  * The timer going over the time you specify is NOT a bug. Read NOTE2 under
    "Track playtime" in the "Playlist" section of "How to use Composer".

  * If a sound_looping file references a sound that doesnt exist(or
    cant be loaded), playback will end and Composer will proceed to
    play the next available track.

  * Sounds do NOT crossfade between normal and alternate sounds, even
    if the sound_looping file specifies they should. This is due to how
    the system for selecting samples works(It cannot predict the next
    block of samples in advance). As such, this is more of a limitation
    of the program than an outright bug.

  * Be on the lookout for bugs invloving filepaths. This is my first real
    C++ program, so I haven't done enough research into making/using proper
    universal path manipulating functions in C++. I am sure something will
    break at some point, but for now it works lol.


Troubleshooting:

  * If Composer wont load properly(or at all) delete composer_config.cfg and
    try to open Composer again.

  * If Composer says a track is missing, make sure the tags directory is
    correct. If it is not, set it to where it should point to, save the
    playlist, and re-open it.

  * If a track isn't marked as missing, but wont play, check if the sound tags
    it points to are in the tags directory with it where they should be. This
    will require downloading and installing the Halo Editing Kit for PC to get
    an editing tool called Guerilla to open the sound_looping file. Hopefully
    you never have to try fixing this issue.


Changelog:

  * v1.0.5
    Fixed a bug with directly copying uncompressed samples to output buffer

  * v1.0.4
    Fixed a bug where uncompressed 16-bit pcm sounds would not decode properly

  * v1.0.3
    Fixed a bug with playlist not being blanked when making a new one
    Fixed a bug with potentially reading random memory as a string

  * v1.0.2
    Fixed a bug with shifting commands and tracks not redrawing the lists properly.

  * v1.0.1
    Fixed bug where the permutation 1 was skipped after the start sound ends.

  * v1.0.0
    Initial release.


Todo:
  * Figure out how Halo 2 sounds are structured(gonna be giving Kornman00's
    blamite another look) and incorporate reading them into Composer.
