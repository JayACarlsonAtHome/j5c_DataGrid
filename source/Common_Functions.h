//
//
// This is cppDataGrid...
//
//        It is a simple text based grid for console programs.
//
//
// Copyright (C) 2017  Jay A. Carlson of J5C Marketing LLC.
//
// This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#ifndef CPP_DATA_GRID_001_COMMON_FUNCTION_H
#define CPP_DATA_GRID_001_COMMON_FUNCTION_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <locale>
#include <limits>
#include <chrono>


namespace J5C_DSL_Code {

    class Common_Functions {

    private:

    public:
        Common_Functions() {};
        bool validate_string_is_numeric(std::string str);
    };
}



#endif //CPP_DATA_GRID_001_COMMON_FUNCTION_H
