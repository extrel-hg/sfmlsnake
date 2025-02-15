# HOW TO PREPARE FOR RELEASE:
-> During development, note every change in update notes here.

-> Copy everything below of Vdev ddev into README.md, and set proper version tags and date.

-> Copy patch notes with proper version tag and date into updatelogs.md.

-> If update concerns a more major version flag than the previous one, copy all required patch notes as well.

-> Set proper version tags and date constants in mainheader.h.

-> Clear patch notes here.

-> Make sure you dont include gamedata folder in release.

-> Delete debugging file.


# Vdev - ddev
By Hubert Gonera

## Welcome

Welcome to my take on the snake genre.
I have made this game primarly to familiarize myself with SFML, as well as working on Github on bigger projects.

I am sure You know what snake is about, but if You do not, here are the basics:

* You are a snake.
* The only way to win is to fill the whole map.
* To grow you need to eat fruit.

## Controls:

Use arrows or WASD to change snake direction.

You can use enter to start the game.
You can (almost anywhere) use Q instead of the X button to close the game.

The GUI elements work as well, but using only the keyboard is way faster.

After a round if the "Ask for a name after a round" setting is set to "No", the game will set the name to "NOT-SET" and go straight to the menu, no matter what.
If that setting is set to "Yes", pressing space will use the default name, while pressing enter will prompt the user to type a name.

## Update notes:

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

### SFML
This version uses SFML 2.6.2. Download the SFML libary either for linux or windows, depending on which one you are using.

The CMakeLists.txt file should automatically link and include any SFML version, that is present in the snake/SFML folder. The SFML folder should contain include, lib and share folders.

### tinyfiledialogs
This version uses tinyfiledialogs v3.19.1.

This libary is already present in this repo, you don't need to download it. It is cross-platform, so no need to change from Windows to Linux version of the library, or vice versa.


### Notice
I am a beginner and self-taught game developer. If anything I've written is inconcise, or any term I've used it not proper, I am sorry. I am still learning.