/*  List of all Panels
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_PanelList_H
#define PokemonAutomation_PanelList_H

#include <memory>
#include <vector>
#include <map>
#include "ConfigSet.h"
#include "Program.h"

const std::vector<std::unique_ptr<ConfigSet>>& SETTINGS_LIST();
const std::map<QString, ConfigSet*>& SETTINGS_MAP();

const std::vector<std::unique_ptr<Program>>& PROGRAM_LIST();
const std::map<QString, Program*>& PROGRAM_MAP();

#endif
