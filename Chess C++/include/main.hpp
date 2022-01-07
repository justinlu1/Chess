#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <map>
#include "initialize.hpp"
#include "pieces.hpp"
#include "game.hpp"
#include "specialRules.hpp"

std::ostream& operator<<(std::ostream&, std::map<std::string, Cell>&);

#endif //_MAIN_HPP_