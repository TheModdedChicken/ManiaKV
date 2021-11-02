# ManiaKV
Does the tippity tap tap with the wap bap bap. (Mania Key Visualizer)

The goal of this project is to make a highly customizable key visualizer.

## Features
**Note**: This application is in a functional state, however, it is still in early developent, it has not been extensively tested, and it is limited in functionality.

- [x] Customizables
	- [x] Body
	- [x] Instrument
	- [x] Hands
	- [x] Table
	- [x] Background
- [x] Hotkeys: Add hotkeys to key setups for faster scene/config swapping
- [ ] Hot-Reload: Add ability to reload your config file without leaving the application
- [ ] In-App Config Modifying: Add menu to settings for modifying your config files
- [ ] Key Sounds: Add option to assign audio clips to key presses
- [ ] Modifiable Shortcuts: Add options in the settings menu to allow for customizing application shortcuts
- [ ] Custom Events: This application is mainly supposed to be for VSRGs (Visual Scrolling Rhythm Games) such as osu! or FNF. However, later down the line I plan to add custom events allowing for things like full keyboards and mice/drawing tablets. (Later in development)
- [ ] Twitch Chat Commands: Adds twitch chat user interactivity allowing for things like command activated custom events. (Later in development)

## Known Issues
- Not all key presses register when holding down multiple keys:
If you have this problem then I apologize but sadly I cannot do anything about it as this is a limitation of some keyboards.

- Images appear fuzzy or blurry:
Currently working on fixing this.

- Transparency shows up a black in recording software:
As far as I know this is a limitation of your recording software or OS so I can't do much about it.

## Wiki
Go [here](https://github.com/TheModdedChicken/ManiaKV/wiki) to figure out how this works.

## Build
Will update when the application released

## Credit
[json.hpp](https://github.com/nlohmann/json) - Used for parsing JSON.

[Raylib](https://github.com/raysan5/raylib) - Used as main library for graphics, sound, etc.

[Mania Cat](https://github.com/malad1211/Mania-Cat) - Used for inspiration and it's bongo cat assets

Also, thanks to [Floatyoats](https://github.com/Floatyoats) for suggesting I make this :D

This project is supposed to be an unofficial successor to [malad1211's](https://github.com/malad1211) project called [Mania-Cat](https://github.com/malad1211/Mania-Cat). 
I was originally going to fork it but I ran into issues with the main library they were using so I decided to create a new application with [raylib](https://github.com/raysan5/raylib).