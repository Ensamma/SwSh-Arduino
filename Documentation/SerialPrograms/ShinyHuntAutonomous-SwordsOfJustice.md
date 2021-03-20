# Shiny Hunt Autonomous - Swords of Justice

This is the autonomous version of [ShinyHuntUnattended-SwordsOfJustice](../NativePrograms/ShinyHuntUnattended-SwordsOfJustice.md).

This program will automatically hunt for a shiny Sword of Justice and automatically stop on a shiny. It fully utilizes video feedback and has these advantages over the unattended version of this program:
- No calibration is needed. This program will detect a shiny from its animation.
- When a shiny is encountered, this program will save a video of the encounter.
- This program will keep track of encounter statistics.

**Demo Video:** https://cdn.discordapp.com/attachments/755635697737531544/822268782910636062/2021-03-18_19-38-31.mp4

<img src="images/ShinyHuntAutonomous-SwordsOfJustice.jpg" width="800">

## Instructions:
- You must have system time unsynced.
- Casual mode is off.
- Your text speed must be set to fast.
- Airplane mode must be off.
- You must be offline.
- The cursor in the menu is over the "Pokémon Camp" option.
- Your lead Pokémon must be faster than the Sword of Justice.
- Your lead Pokémon must not be shiny. (this will cause false positive detections)
- You must have previously defeated or ran away from the Sword of Justice so that it is no longer present.
- You must be standing exactly on the spawn point of the Sword of Justice.
- You must be in the overworld. (not inside the menu)
- Start the program in the [Change Grip/Order Menu](../Appendix/ChangeGripOrderMenu.md).

**Recommended for Performance:**
- Have the Shiny Charm. This triples the chance to find a shiny.
- Your lead Pokémon does not have high happiness.
- Your lead Pokémon does not have an ability that activates upon entry to battle.

When the a shiny is found, the program will save a video of the encounter. Then it will go to the Switch home to idle.

## Options:

This program uses [`TOLERATE_SYSTEM_UPDATE_MENU_FAST`](../Appendix/GlobalSettings.md#tolerate-system-update-menu-fast) to bypass the system update window.

There is no option to search only for a square shiny. Nearly all shinies are square and only 15/65536 are star. Therefore it is infeasible to hunt for star shiny.

### Airplane Mode:

If you need to run the program in airplane mode, set this to true. It will slow down the program by a couple seconds.

### Exit Battle Time:

After running, wait this long to return to the overworld.

### Enter Camp Delay:

Wait this long after entering camp before you leave.

### Time Rollback:

Every this many hours, rollback the time by this many hours. This keeps the time constant to prevent the weather from changing. It also allows you to target time-specific marks. Set this to zero to disable this feature.

<hr>

**Back to:**
- [Project Home](/README.md)
- [Documentation Home](/Documentation/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)