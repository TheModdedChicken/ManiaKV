# ManiaKV
Does the tippity tap tap with the wap bap bap. (Mania Key Visualizer)

The goal of this project is to make a highly customizable key visualizer.

**Note**: This application is in a functional state, however, it is still in early developent, it has not been extensively tested, and is limited in functionality.
Though, if you'd still like to get your hands on it in it's current state then you can head [here](https://github.com/TheModdedChicken/ManiaKV/releases) and download the latest release.

## Wiki
Go [here](https://maniakv.vercel.app) to figure out how this works.

Go [here](https://github.com/TheModdedChicken/maniakv-docs) to contribute to the ManiaKV wiki

## Contact
If you need to contact me for any reason, here are three ways you can reach me:
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
All known issues can be found [here](https://maniakv.vercel.app/issues/general)

Listed below are any ongoing critical issues:

- **Application crashes after a fresh install (v0.1.1)**:
This is due to a bug introduced by the states system implemented in version 0.1.1. Version 0.2.0 will be released on either Feb 27th or March 6th which will fix this issue entirely.
As of right now, if you would like to fix this issue please head over to [this page](https://github.com/TheModdedChicken/ManiaKV/wiki/v0.1.1-Issues#application-crashes-after-a-fresh-install) which explains the process in doing so.

## Build
Will update when the application released

## Credit
[json.hpp](https://github.com/nlohmann/json) - Used for parsing JSON.

[Raylib](https://github.com/raysan5/raylib) (v3.7.0) - Used as main library for graphics, sound, etc.

[Mania Cat](https://github.com/malad1211/Mania-Cat) - Used for inspiration and it's bongo cat assets.

[oppai.c](https://github.com/l3lackShark/gosumemory/blob/master/pp/oppai.c) - Yoinked from [gosumemory](https://github.com/l3lackShark/gosumemory) to extract information from [osu!](https://github.com/ppy/osu).

Also, major thanks to [Floatyoats](https://github.com/Floatyoats) for testing, suggesting ideas, commissioning art, and being the reason I started creating this application in the first place :D

---

This project is supposed to be an unofficial successor to [malad1211's](https://github.com/malad1211) project called [Mania-Cat](https://github.com/malad1211/Mania-Cat). 
I was originally going to fork it but I ran into issues with the main library they were using so I decided to create a new application with [raylib](https://github.com/raysan5/raylib).
