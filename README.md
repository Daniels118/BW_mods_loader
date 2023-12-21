# Mods loader for Black & White
This project provides a DLL that can automatically load additional DLLs from a predefined directory.
It also adds a command line switch to open a console to see debug messages from the game or user mods.

## How to install
Just extract the file `ddraw.dll` in the game installation directory, and create a folder named `mods`. Put any user mod DLL in the `mods` directory, and they will be automatically loaded at game startup.

## How to open the console
Simply add `/console` when starting the main executable. You may want to create a simple batch script to launch the game with the console open without having to open a command prompt.

**Sample script:**
```
@echo off

start CreatureIsle.exe /console
```

## Recommendations
Never run the game as administrator. If any mod contains malicious code, it will be executed with admin privileges.

## Special thanks
This project has been derived from [Black & White Ultimate](https://github.com/ShaneDoyle/BW-Ultimate), so special thanks go to its author and who contributed to the project.
