/*  Pokemon Sword & Shield: Loto-ID
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *      Please refer to the user manual for instructions and documentation.
 * 
 */

#include "Common/SwitchFramework/SwitchControllerDefs.h"
#include "PokemonSwShPrograms/DateSpam-LotoFarmer.h"



//  Run Loto-ID this many times. You can set this number if you're also date
//  skipping to a particular den frame and you don't want to overshoot it.
//
//  Be aware that this program isn't intended to be an accurate date skipper.
//  It will occasionally miss frames causing it to fall short.
const uint32_t SKIPS    =   100000;

//  Mash B for this long to exit the dialog.
//  For some languages, (like German), you may need to increase this.
const uint16_t MASH_B_DURATION  =   8 * TICKS_PER_SECOND;
