# System Explorer

## What does it do?

Throws you around the system!

Specifically, the program will locate a random sub directory from the current one you are in(or the one provided), and throw you in there.

## How to run

```sh
. warp.sh [DIRECTORY] [-f] [-p]
```

Directory is an optional input to tell the program to start from there instead of your current directory.

## Optional Flags

-f : Do not stop randomly and only end upon reaching a directory with no sub directories

-p : Print the path rather than changing the directory to it

## To implement

Functionality of the f flag

Array bound checkers
