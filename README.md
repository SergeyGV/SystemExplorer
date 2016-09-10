# System Explorer

## What does it do?

From whatever directory the program starts, it scans for all of the directories that lie within the current one.

It will then go to that directory, and repeat the process recursively.

It will stop upon either reaching a directory with no sub directories, or randomly after a certain amount of directories have been passed.

The program will change the current directory to whatever it happened to end at, and then terminate.

## Input

Optional input of providing your own file path from where to begin. Otherwise, the default is the current directory.

## Flags

-f
Do not stop randomly and only end upon reaching a directory with no sub directories
