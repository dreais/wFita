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

## Sources used
[Perlin noise code](https://gist.github.com/nowl/828013)

Was a bit modified, for setting up the hash array dynamically.

[Colors converted table for PDCurses](https://stackoverflow.com/questions/47686906/ncurses-init-color-has-no-effect)

I used the keys to keep a track as of what color the program uses.