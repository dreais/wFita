# wFita 
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
- Core game
    - Currently now much:
        - structures are being prepared/done for the characters. charac_t is ONE monster/player.
        - windows. the main 'window' is for the games, and there's 2 others for logs and player's state
 
## Sources used
[Perlin noise code](https://gist.github.com/nowl/828013)

Was a bit modified, for setting up the hash array dynamically.

[Colors converted table for PDCurses](https://stackoverflow.com/questions/47686906/ncurses-init-color-has-no-effect)

I used the keys to keep a track as of what color the program uses.