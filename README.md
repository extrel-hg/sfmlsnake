# V2.0.1.3 - 23.02.2025
By Hubert Gonera

## Welcome

Welcome to my take on the snake genre.
I have made this game primarly to familiarize myself with SFML, as well as working on Github on bigger projects.

I am sure You know what snake is about, but if You do not, here are the basics:

* You are a snake.
* The only way to win is to fill the whole map.
* To grow you need to eat fruit.

## Controls:

### General

* Q - closes the game

### Main Menu

* Enter - start the game
* L - leaderboard
* S - settings

### Leaderboard

* B - back to menu
* Up and down arrows - move leaderboard

### Settings

* B - back to menu
* R - reset graphics settings

* Default name - name used for the score, when the player does not input any name.
* Ask for a name after a round - when set to no, the game will never allow to input a name. Only the default name will be used.

### Game

* WASD or arrows - change Snake direction

### Game end

* Space - go back to menu and use default name.
* Enter - ask for name, then go back to menu. If the name is left blank, the default name will be used. If "Ask for a name after a round" is set to no, the game won't ask for a name.

## Update notes:

**Patch:**
* README changes.
* * Rewritten Controls section.
* When "Ask for a name after a round" is set to no, the default name will be used, instead of the "NOT-SET" name.
* Moved "Previous COMPATIBILITY updates" to updatelogs.md.
* Small update to "Building yourself" section.

## Versioning:

Version format: VCOMPATIBILITY.MAJOR.MINOR.PATCH(-suffix)

Version flags:

* COMPATIBILITY - Wheter or not this version savefiles etc. will work with another version. Some parts may still work with previous versions. May also be increased when a major update to the backend happens, or if the project structure (on the programmers end) majorly changes.
* MAJOR - Incermented if added new feature systems, heavily reworked existing ones, or added large features.
* MINOR - Incremented if added small to medium features in existing systems, or if they were reworked. NOT INCREMENTED if new feature systems were added. Then MAJOR is incremented.
* PATCH - No new features, just bug fixes.
* suffix - Explained below.

A version that contains the -alpha-n suffix is in development. New systems, features or reworks are underway, but the game itself is also playable
(albeit with bugs and unpolished). The n after alpha stands for the current alpha version. Think of the -alpha suffix as something analogous to 0.y.z
versions in the semantic versioning system (semver.org). Many changes are coming, and when the version is ready, the suffix is deleted and the
version with just the tag is released.

In some cases in the update notes there will be a section covering changes from previous versions. Notably, when exiting the alpha suffix into a full release (eg. 1.3.0.0 from 1.3.0.0-alpha-8), all changes
from each alpha version (alpha-8, alpha-7 etc.) may be added to release update notes. This does not apply to updatelogs.md, they only contain changes for that version.

Each README has its build version in the beginning, and build date in dd/mm/yyyy.


## Credits
Thanks to everyone who created and manages SFML.
www.sfml-dev.org

Thanks to Guillaume Vareille for creating and managing tinyfiledialogs.
www.ysengrin.com

Big thanks to Miroslaw Zelent and Damian Stelmach for giving me an easy introduction to c++ in the first place, many years ago.
www.youtube.com/channel/UCzn6vAfspIcagLax1fck_jw

Thanks to Tymon Drop for designing the snake graphics in V1.2.3.0 and implementing WASD controls.
www.github.com/Kimoworwa

## Building the game yourself

I have provided a CMakeLists.txt file for easy building on both Windows and Linux.

The project as of now uses two 3rd party libraries, SFML and tinyfiledialogs.

### Tinyfiledialogs

Download the latest version of tinyfiledialogs. The current version of the game uses v3.19.1. As it is a header-only library, there is no need for downloading the built library. You just include the header in your project and it is build along with the app. My CMake file will properly add TFD that is present in snake/tinyfiledialogs. Specifically, inside that folder there should be the tinyfiledialogs .c and .h file, and my CMakeLists.txt script, which is included in the source code.

### SFML

On both Windows and Linux, the CMake file will load any SFML library present in the SFML-X.Y.Z folder. As of now, the game uses SFML-2.6.2.

On Linux, use the SFML version that is built using GCC 64-bit. That version is avaible for download on SFMLs website. Download the compressed file, and exctract it. Put the SFML-2.6.2 folder into snake. My CMake script will automatically load it.

On Windows, I encountered problems with the already built versions of SFML, as such, the windows version of CMake requires you build SFML yourself, using the same compilier you will use for the game.

Download the SFML source code for 2.6.2, and excract it somewhere on your PC. SFML also uses CMake for building, I highly recommend using MinGW Makefiles for building, instead of Visual Studio solutions. Assuming you use MinGW Makefiles (all of my scripts for Windows do that, you have to explicitly state that you are using something else), you can build SFML from source using those commands:

Open terminal in the SFML-2.6.2 folder, that was extracted from the source code zip file. Send those commands:
* mkdir build
* cd build
* cmake .. -G "MinGW Makefiles"
* make

The built library will be in SFML-2.6.2/build/lib. You can find both .dll and .a files there.

Take all of them, and put them in snake/SFML-BUILTLIBS.  Take the source code for SFML-2.6.2, and put that whole folder into the snake folder as well. This is necessary for my CMake script to include the library.

### Build scripts

I have included two .sh scripts for automatically building snake.

My CMake script has a variable called "INCLUDEDLLS". If it is set to false (default), CMake is set in the Linux configuration. If set to true, it will build for Windows. This variable affects wheter or not the RPATH of the .exe will be edited, and what files to include in the installed folder.

### Linux build script

```
1 mkdir build
2 cd build
3 cmake .. -DINCLUDEDLLS=false
4 make
5 cmake --install .
6 $SHELL
```

The first two lines make and enter the build folder. The 3rd command runs cmake, and sets it to not include dlls (Linux config). The 4th line builds snake. The 5th installs it in the snake/build/finishedsnake folder. During this step, all required .so files and resource files are included. Snake is now finished! The last line prevents the shell script from closing.

### Windows build script

```
1 mkdir build
2 cd build
3 cmake .. -DINCLUDEDLLS=true -G "MinGW Makefiles"
4 make
5 cmake --install .
6 $SHELL
```

The only difference here is that in the 3rd line, we set INCLUDEDLLS to true, as we are building on Windows. We also set the CMake generator to MinGW Makefiles.

**Make sure to use the same build system and compiler that you used for SFML library. I use MinGW compiler and MinGW Makefiles everywhere on my Windows machine, so that is what all my programs default to. Make sure to change this, if you have a different workflow.**

I highly reccommend getting familiar with my CMakeLists.txt file. I am still a beginner user of CMake, and I will be claryfing and editing my CMake script, so that it is more readable.