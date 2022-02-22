# ManiaKV
Does the tippity tap tap with the wap bap bap. (Mania Key Visualizer)

The goal of this project is to make a highly customizable key visualizer.

**Note**: This application is in a functional state, however, it is still in early developent, it has not been extensively tested, and is limited in functionality.
Though, if you'd still like to get your hands on it in it's current state then you can head [here](https://github.com/TheModdedChicken/ManiaKV/releases) and download the latest release.

## Contact
If you need to contact me for any reason here are three ways you can reach me:
- Discord: TheModdedChicken#5225
- Twitter: [@TheModdedChickn](https://twitter.com/TheModdedChickn)
- Email: moddedchicken1744@gmail.com

## Development
If you'd like to check how development is progressing then you can go [here](https://github.com/TheModdedChicken/ManiaKV/projects)

## Features
- [x] Customizables
	- [x] Body
	- [x] Instrument
	- [x] Hands
	- [x] Table
	- [x] Background
- [x] Shortcuts: Keyboard shortcuts to load key setups for faster scene/config swapping
- [ ] Map Detection: Toggle to only show ManiaKV when playing a map (osu! Only)
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

- Transparency shows up as black in recording software:
As far as I know this is a limitation of your recording software or OS so I can't do much about it.

- 6 Key gameplay doesn't work:
This is due to a hacky system for assigning textures to key bindings, however, reworking the system has proven to be too big brain of a task for me to handle. With this being the case, don't expect this to be fixed for awhile.

## Wiki
Go [here](https://github.com/TheModdedChicken/ManiaKV/wiki) to figure out how this works.

## Build
Will update when the application released

## Credit
[json.hpp](https://github.com/nlohmann/json) - Used for parsing JSON.

[Raylib](https://github.com/raysan5/raylib) - Used as main library for graphics, sound, etc.

[Mania Cat](https://github.com/malad1211/Mania-Cat) - Used for inspiration and it's bongo cat assets.

[oppai.c](https://github.com/l3lackShark/gosumemory/blob/master/pp/oppai.c) - Yoinked from [gosumemory](https://github.com/l3lackShark/gosumemory) to extract information from [osu!](https://github.com/ppy/osu).

Also, major thanks to [Floatyoats](https://github.com/Floatyoats) for testing, suggesting ideas, commissioning art, and being the reason I started creating this application in the first place :D

---

This project is supposed to be an unofficial successor to [malad1211's](https://github.com/malad1211) project called [Mania-Cat](https://github.com/malad1211/Mania-Cat). 
I was originally going to fork it but I ran into issues with the main library they were using so I decided to create a new application with [raylib](https://github.com/raysan5/raylib).
