# Previous COMPATIBILITY updates

* The update from 1.x.y.z to 2.x.y.z was justified by moving the entire project from Visual Studio to CMake, and making the project compatibile with both Windows and Linux.

# Previous update notes:

## V2.1.1.0
*12.09.2025*

**Minor:**
* Added tracking of won rounds in 2P mode for each session. I.e. the tracking resets after closing the game.
* Press F to enable and disable fast-scrolling in Leaderboard menu.
* Added sorting to Leaderboard menu.
* Removed auto-close of round after losing/winning.

**Patch:**
* Fixed bug in two player mode, that caused only player no. 1 speed to increase.
* Swapped starting positions in the two player mode, so that they match the keyboard layout.
* Decreased the text size in 2P mode by 33%.
* Fixed not working scroll keys in Leaderboard menu.

## V2.1.0.1
*25.03.2025*

**Patch:**
* Made the speed in two player mode the same as in normal mode.

## V2.1.0.0
*25.03.2025*

**Major:**
* Added two player mode. You can pass through yourself in two player mode.

**Minor:**
* Added number of highscores in leaderboard menu.
* Added scrolling using mouse wheel in leaderboard menu.

**Patch:**
* Clarified controls section of readme.
* Clarified ask for name screen after game end.

## V2.0.2.0
*19.03.2025*

**Minor:**
* Removed unnecessary setting "Ask for name after a round" from the settings GUI.

**Patch:**
* Revised and updated credits.
* Changes to windows CMake building system.
* Made windows version not require MinGW C++ .dll files. They are now statically linked.
* Fixed leaderboard "dot" bug.

## V2.0.1.3
*23.02.2025*

**Patch:**
* README changes.
* * Rewritten Controls section.
* When "Ask for a name after a round" is set to no, the default name will be used, instead of the "NOT-SET" name.
* Moved "Previous COMPATIBILITY updates" to updatelogs.md.
* Small update to "Building yourself" section.

## V2.0.1.2
*17.02.2025*

**Patch:**
* Made changes to CMakeLists.txt so that the resulting app has RPATH set to origin. This will allow the application to check for .so files in its own install directory. This means the user does not need to install SFML 2.6.2, because I will be shipping the required .so files with my game.
* Further changes to CMakeLists.txt that automate the build process.

## V2.0.1.1
*17.02.2025*

**Patch:**
* Made changes to CMakeLists.txt so that the resulting app has RPATH set to origin. This will allow the application to check for .so files in its own install directory. This means the user does not need to install SFML 2.6.2, because I will be shipping the required .so files with my game.

## V2.0.1.0
*16.02.2025*

**Minor:**
* Settings and highscores are updated from the text files during each change of menu. This is only made, so that if multiple people change the text files, you should always have the most up to date data from the text files.

**Patch:**
* Removed any limits regarding the choice of resoultions. This is because of inconsistencies between Linux and Windows machines, and general unwieldiness of that system. If you accidently select any setting that makes it impossible to change back to one that works, you can press R while in the save menu, that will reset the window to 800x600 fullscreen.

## V2.0.0.0
*15.02.2025*

**Compatibility:**
* Changed project structure from Visual Studio to CMake.

**Minor:**
* Changes to README and versioning.

## V1.3.1.0
*19.11.2024*

**Minor:**
* You can use B to go back to the main menu from the settings and leaderboard menu.
* * You can also use Right Control + B to go back to main menu during a game. This will lose progress, and the highscore wont be saved.
* Added buttons to leaderboard menu.
* Now the leaderboard menu shows the current listed highscores.

## V1.3.0.0
*10.11.2024*

**Major:**
* Added simple leaderboard menu that shows all saved highscores and the highscores version. Navigate using up and down arrows.

**Minor:**
* Highscore text in the main menu now only shows highscores that have a correct and version tag, and that version tag matches current version.

**Patches:**
* You now cannot set the in-game resolution higher than your screen resolution.

## V1.3.0.0-alpha-8
*05.11.2024*

**Patches:**
* More error-catching in set.txt.
* Error checking in data.txt.

## V1.3.0.0-alpha-7
*04.11.2024*

**Minor:**
* Changed ways to enter name a name after a round.

**Patches:**
* Lengthened the wait time after a round to 7 seconds.
* Removed the ability to start a game using space. This is so that enter is for default skipping, and space is for other uses.

## V1.3.0.0-alpha-6
*03.11.2024*

**Patches:**
* Fixed logo box misaligment in main menu.
* Added basic error catching, more to come.
* Rewritten README.

## V1.3.0.0-alpha-5
*03.11.2024*

**Major:**
* Highscores now use names as well. After each round, you will be prompted to give your name (unless turned off). If you don't give any names, the default
one will be used.
* Added new settings:
* * Resolution changing.
* * Default name changing.
* * Wheter to ask for a custom name after a round or use the default one.
* Settings show their current status next to the button or on it.

**Minor:**
* Use S in the main menu to go to settings quicker.
* Game logo has been added to the main menu.
* Warning about the settings the first time you open them.

**Patches:**
* Various back-end changes to make developing easier.
* Versioning changes.

## V1.3.0.0-alpha-4
*30.10.2024*

**Major:**
* Added basic settings menu along with changing and saving of fullscreen option.

**Minor:**
* Changed TPS to 128Hz, because of very small (but annoying) input lag on older machines with higher TPS.

**Patches:**
* Changes to versioning.
* Added tinydialogfiles, not used yet.
* Changes to "Building yourself" section.

## V1.3.0.0-alpha-3
*30.10.2024*

**Patches:**
* Changes to versioning.
* Fixed snake reloading.

## V1.3.0.0-alpha-2
*29.10.2024*

**Patches:**
* Fixed "Game not opening for certain data.txt files" bug.
* Fixed saving and reloading of highscores.

## V1.3.0.0-alpha-1
*29.10.2024*

**Major:**
* Added the set.txt file to gamedata folder (or it will be generated on first run). It contains three lines, first is resolution width,
second is height, and the third contains either 0 for window mode or 1 for fullscreen.
In the future a proper settings GUI will be implemented. This is the main reason as for the alpha suffix.

**Minor:**
* You can now close the game during a round using Q.
* Background of the game is now a very dark gray, so that during fullscreen play in an aspect ratio different from the monitor, you can see the
worlds edges.
* Highscore saving and loading system now reloades and resaves the highscores after each run. Normally this wouldn't be needed, but in the case that
many people will be playing on the same .exe file, this should prevent overwriting highscore data. (And yes, I am surprised that such people exist,
but oh well, the cost to add this redundancy is bascially zero, so I might as well.)
* Uncapped the amount of saved highscores.

**Patches:**
* Changes to versioning.
* Backend optimizations and code restructuring.

## V1.2.4.1
*29.10.2024*

**Patches:**
* Updated game icon.

## V1.2.4.0
*29.10.2024*

**Minor:**
* Reworked snake graphics.

## V1.2.3.0
*26.10.2024*

**Minor:**
* Changed snake graphics.
* Added wasd controlls.
* Changed game icon.

## V1.2.2.1
*25.10.2024*

**Patches:**
* Fixed typos in README.

## V1.2.2.0
*25.10.2024*

**Minor:**
* Changed font and game icon.

**Patches:**
* Small changes to saving mechanisms - added capability to give a version tag to each highscore. Ensured backward compatibilty with previous saves, now if the game detects a highscore without a versiontag, it adds the "before V1.2.2.0" tag into it.
* Small changes to README.

## V1.2.1.0
*22.10.2024*

**Minor:**
* Added color grading to the snake's body, so it is easier to see which part is moving where.
* Increased TPS to 256Hz
* Lose and win screen now stays for 5 seconds, however you can press enter or space to exit to main menu instantly.

**Patch:**
* Small changes to README.

## V1.2.0.3
*20.10.2024*

**Patches:**
* Fixed in-game version tag.
* Hid console window.

## V1.2.0.2
*20.10.2024*

**Patches:**
* Fixed updatelogs.md

## V1.2.0.1
*20.10.2024*

**Patches:**
* Small changes to README, as well as project architecture.

## V1.2.0.0
*20.10.2024*

**Major:**
* Fully implemented highscore saving and loading, but as of now only the highest score is displayed, with no name.
	* -> In the future, it will be easy to add names to each highscore, as well as displaying any amount of them.

**Patches:**
* Optimizations.
* Changes to README.
* Moved previous update logs to a seperate file.

## V1.1.1.1
*20.10.2024*

**Patches:**
* Small changes in README.
	* -> Added credits.
	* -> Added info on how to build the game yourself.
* Added functions for reading and saving data, as well as writing logs.

## V1.1.1.0
*16.10.2024*

**Minor:**
* Pressing space and enter now also start the game, and Q closes it. (This is so the game can also be played without a mouse.)

**Patch:**
* Refined speed formula.

## V1.1.0.0
*14.10.2024*

**Major:**
* Added main menu.
* Added lose screen.
* Added basic button class for creating simple buttons.

**Minor:**
* Moved keyboard events over to the simulation part of the gameloop. As a result, controls feel way more immidiate now.

**Patch:**
* Various small optimizations.
* Increased text size during gameplay.

## V1.0.2.0
*13.10.2024*

**Minor:**
* Reworked the speed function. It is now not incremental, but instead follows something akin to a very flattened parabola.
* Moved from .txt README format over to .mb. Changed the versioning section a bit, as well as moved previous patchnotes to the current standard.

**Patches:**
* Added seed randomization for varying the location of fruit between runs. Previously, the fruit spawned in consistant locations in each run.

## V1.0.1.2
*10.10.2024*

**Patches:**
* Corrected game window name.
* Corrected in-game version tag display.
* Fixed "passing by yourself" bug.

## V1.0.1.1
*10.10.2024*

**Patches:**
* Made VS2022 automatically add neccessesary files to build directory. (Such as .dlls and README)
* Small formatting changes to README

## V1.0.1.0
*10.10.2024*

**Minor:**
* Increased TPS from 60 to 120

**Patches:**
* Added README:
	* -> Defined Versioning
	* -> Added content

## V1.0.0
*09.10.2024*

No README in this version. This update note was added in V1.0.1.0.
First functional version with minimal features, and some bugs.

#
Hubert Gonera
