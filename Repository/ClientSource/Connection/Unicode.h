/*  Unicode
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_Unicode_H
#define PokemonAutomation_Unicode_H

#include <string>

namespace PokemonAutomation{

std::u16string utf8_to_utf16(const std::string& str);

}
#endif
