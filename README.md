# ManiaKV
Does the tippity tap tap with the wap bap bap. (Mania Key Visualizer)

The goal of this project is to make a highly customizable key visualizer.

**Note**: This application is in a functional state, however, it is still in early developent, it has not been extensively tested, it is limited in functionality, and as of right now it doesn't have a stable release.

## Features
- [x] Customizables
	- [x] Body
	- [x] Instrument
	- [x] Hands
	- [x] Table
	- [x] Background
- [x] Shortcuts: Shortcuts to load key setups for faster scene/config swapping
- [ ] Hot-Reload: Ability to reload your config file without leaving the application
- [ ] In-App Config Modifying: Menu in settings for modifying your config files
- [ ] Key Sounds: Option to assign audio clips to key presses
- [ ] Modifiable Shortcuts: Options in the settings menu to allow for customizing application shortcuts
- [ ] Pointer Support: Support for drawing tablets and mice
- [ ] Custom Events: Support for customizable events that affect application visuals or sounds
- [ ] Twitch Chat Commands: Twitch chat user interactivity allowing for things like command activated custom events. (Later in development)

## Known Issues
- Not all key presses register when holding down multiple keys:
If you have this problem then I apologize but sadly I cannot do anything about it as this is a limitation of some keyboards.

- Images appear fuzzy or blurry:
Currently working on fixing this.

- Transparency shows up as black in recording software:
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
