[![Build Status](https://travis-ci.com/dreais/wFita.svg?branch=master)](https://travis-ci.com/dreais/wFita)
# wFita 

**CURRENTLY IN VERSION [v0.3.0](https://github.com/dreais/wFita/releases/tag/v0.3.0)!**

(windows Fed in the abyss)

(Contains standalone map generation and path finding)

Fita is a rogue-like game that runs on your terminal (be it from Windows or Linux!). It uses PDCurses as its 'engine'.

As mentioned you'll find 2 algorithms for path findings and procedural map generation.
## (about the 2 algorithms) What is it for? Why in C?

(previous version) I'm currently working on a roguelike game, called Fed in the Abyss, and I need a powerful pathfinding/map generation algorithm using the game's language (which is C).
As for 'why in C' regarding the game - no particular reason, I'm using ncurses on top of that, so it made it easier I guess!

As this repository is now the game, it made it easier to just continue in C.

#### How to reduce calculation's impact?

We could think of many things that I haven't tried yet, as creating a thread dedicated to path calculus.

**Side note:** My pathfinding implemented algorithm here is not the fastest, by far, and may even be (very) slow. This is however 
one that I'm implementing by passion and to see how far it goes, keep that in mind!

## What does it do, for now?
You can check the progress [on the project map](https://github.com/dreais/wFita/projects/1)!

If you're lazy, here's a quick summary:
- Basic movement
    - enemies and player have a hitbox
        - some issues with enemies' movement to fix (see roadmap)
        - they won't get out of range/out of bound
        - they cannot go on top of themself (as expected of a hitbox!)
- Basic printing
    - You can print using (or not) colors. Might get laggy on windows! see #14
    - Health bar (with colors!) on point, will be the same with EXP bar
    - Log file, named as of now "output.log", is created on launch.
- Core game
    - Currently now much:
        - structures are being prepared/done for the characters. charac_t is ONE monster/player.
        - windows. the main 'window' is for the games, and there's 2 others for logs and player's state
    - Can change the floor you're in (only 1 implemented statically though)
    - You can attack enemies and enemies can attack you
    - Integrated basic stuff (weapons and armors)
    
 
## Sources used
[Perlin noise code](https://gist.github.com/nowl/828013)

Was a bit modified, for setting up the hash array dynamically.

[Colors converted table for PDCurses](https://stackoverflow.com/a/47771858)

I used the keys to keep a track as of what color the program uses.

## A word regarding the issue
I'm _tagging_ the issue with many labels. The most important to keep track of are the -priority- labels. 

Priority goes from 1 to 3, 1 being the most important and 3 the less important. When adding a **x** priority, it's expected to have the **x-1** until x = 3

Ex.:
setting priority-l-1 should go with -l-2 and -l-3 as well.
-l-2 should ONLY go with -l-3.

Putting the non-priority with a priority level means that this is unlikely an issue I'll be working on in the near future, but will be later.

Planned means that the issue is planned, but not being the priority, will be worked on when I feel like it. These are usually not big issues or problematics, so don't mind it.

## Building

### Requirements (tested and built on):
- CMake version >= 3.13
- Windows: MinGW 64 bits >= 8.1.0
- Unix: GCC >= 4.5

### Steps
On Windows, easiest way:
1. Have CLion
2. Open CLion, Open New project
3. Load CMakeLists, build it (don't forget the right toolchain^)

On Unix:
1. `git clone https://github.com/dreais/wfita`
2. `cd wfita`
3. `mkdir build && cd build`
4. `cmake .. && make`
