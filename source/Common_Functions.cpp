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

#include "Common_Functions.h"

namespace J5C_DSL_Code {

    bool Common_Functions::validate_string_is_numeric(std::string str) {
        //
        // This is a generally good solution, but it is not a perfect solution.
        // There are some scientific false cases that could get through as true.
        // I don't use scientific notation much, so the code is "good enough" for me
        // but that may not be the case for your coding requirements.
        // but I added this comment so that you won't just blindly accept this as perfect in all cases.
        bool result;


        //if you are using C++ version before then 2011, then char>> needs to be replaced with char> > (on the next two lines)
        char point = std::use_facet < std::numpunct<char>>(std::cout.getloc()).decimal_point();
        char thousands_sep = std::use_facet < std::numpunct<char>>(std::cout.getloc()).thousands_sep();
        char test_character;

        unsigned int pos = 0;
        auto max = str.length();
        bool cont = true;
        bool pos_scientific = false;
        bool scientific = false;
        std::string temp;
        auto pos_x = max;
        auto pos_1 = max;
        auto pos_1_test = max;
        auto pos_0 = max;
        auto pos_Up = max;
        auto pos_sci_minus = max;
        bool sci_minus_exists = false;
        auto point_count = max - max;
        while ((pos < max) && (cont)) {
            test_character = str[pos];

            if (pos == 0) {
                if (!((isdigit(test_character)) || (test_character == '-') || (test_character == '+'))) {
                    cont = false;
                }
            }
            if ((pos > 0) && (!pos_scientific)) {
                if (!((isdigit(test_character)) || (test_character == point) || (test_character == thousands_sep))) {
                    cont = false;
                }
            }
            if ((pos > 0) && (pos_scientific)) {
                if (!((isdigit(test_character)) || (test_character == point) || (test_character == thousands_sep) ||
                      (test_character == 'x') ||
                      (test_character == ' ') || (test_character == '^') || (test_character == '-'))) {
                    cont = false;
                }
                if ((test_character == 'x') && (pos < pos_x)) {
                    pos_x = pos;
                    scientific = true;
                }
                if ((test_character == '1') && (pos < pos_1)) { pos_1 = pos; }
                if ((test_character == '0') && (pos < pos_0)) { pos_0 = pos; }
                if ((test_character == '^') && (pos < pos_Up)) { pos_Up = pos; }
                if ((test_character == '-') && (pos < pos_sci_minus)) { sci_minus_exists = true; }
                if ((test_character == '-') && (pos < pos_sci_minus)) { pos_sci_minus = pos; }
            }
            if ((pos == 1) && (test_character == point)) {
                pos_scientific = true;
            }

            // if not a digit or a decimal point then stop and return false
            if (test_character == point) {
                point_count++;
            }
            if (point_count > 1) {
                cont = false;
            }
            ++pos;
        }
        if (scientific) {
            if ((pos_x == max) || (pos_1 == max) || (pos_0 == max) || (pos_Up == max)) {
                cont = false;
            }
            pos_1_test = pos_1 + 1;
            if (pos_1_test != pos_0) {
                cont = false;
            }
            if ((sci_minus_exists) && (cont)) {
                if (pos_x < pos_1 < pos_0 < pos_Up >= pos_sci_minus) {
                    cont = false;
                }
            } else {
                if (pos_x < pos_1 < pos_0 >= pos_Up) {
                    cont = false;
                }
            }
        }
        result = cont;
        return result;
    }
}