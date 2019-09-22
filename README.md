# MapGeneration
Contains map generation and path finding

## What is it for? Why in C?

I'm currently working on a roguelike game, called Fed in the Abyss, and I need a powerful pathfinding/map generation algorithm using the game's language (which is C).
As for 'why in C' regarding the game - no particular reason, I'm using ncurses on top of that, so it made it easier I guess!

## How to reduce calculation's impact?

We could think of many things that I haven't tried yet, as creating a thread dedicated to path calculus.

**Side note:** My implemented algorithm here is not the fastest, by far, and may even be (very) slow. This is however 
one that I'm implementing by passion and to see how far it goes, keep that in mind!