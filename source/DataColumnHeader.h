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



#ifndef DATAGRID_TEST_001_DATA_COLUMN_HEADER_H
#define DATAGRID_TEST_001_DATA_COLUMN_HEADER_H

#include <iostream>
#include <sstream>

namespace J5C_DSL_Code {

    enum class enum_pad_direction {
        unknown = 0, right = 1, left = 2, both = 3, decimal = 4
    };
    using epadDir = enum_pad_direction;
    using usInt   = unsigned int;
    using sstr    = std::string;

    class DataColumnHeader {

    private:
        //
        // static variables
        //
        static const bool s_default_multi_line_output = false;
        static const epadDir s_default_pad_direction = epadDir::right;
        //
        static const usInt s_default_display_width = 25;
        static const usInt s_default_precision = 5;

        //
        // non static variables
        //
        bool m_debug{false};
        bool m_multi_line_output{false};
        bool m_sql_quote{false};

        epadDir m_pad_direction{enum_pad_direction::left};
        //
        sstr m_column_header{"Default Header Name"};
        sstr m_column_description_long{"Default Header Long  Description"};
        sstr m_column_description_short{"Default Header Short Description"};
        sstr m_left_fill_char{" "};
        //
        usInt m_display_width{25};
        usInt m_precision{8};

        void init(bool debug) noexcept;

        //order of variables to be consistent
        //m_debug
        //m_multi_line_output
        //m_sql_quote
        //m_pad_direction
        //m_column_header
        //m_column_description_long
        //m_column_description_short
        //m_left_fill_char
        //usInt m_display_width
        //usInt m_precision

        //order of variables to be consistent
        //const bool debug
        //const bool multi_line_output
        //const bool sql_quote
        //const epadDir pad_direction
        //const sstr column_header
        //const sstr column_description_long
        //const sstr column_description_short
        //const sstr left_fill_char
        //const usInt display_width
        //const usInt precision


        //
    public:

        // Constructors
        DataColumnHeader();

        explicit DataColumnHeader(bool debug)    noexcept;

        explicit DataColumnHeader(const bool debug,
                         const bool multi_line_output,
                         const bool sql_quote,
                         const epadDir pad_direction,
                         const sstr column_header,
                         const sstr column_description_long,
                         const sstr column_description_short,
                         const sstr left_fill_char,
                         const usInt display_width,
                         const usInt precision) noexcept;


        DataColumnHeader(const DataColumnHeader &other)  noexcept;       // copy constructor
        DataColumnHeader &operator=(const DataColumnHeader &other) {
            this->Copy_Values(other);
            return *this;
        };                       // assignment

        virtual ~DataColumnHeader()                       noexcept;

        //
        bool Get_Debug() const noexcept;

        bool Get_Multi_Line_Enabled() const noexcept;

        bool Get_SQL_Quote() const noexcept;

        //
        std::string Get_Address_as_String() const noexcept;

        enum_pad_direction Get_Pad_Direction() const noexcept;

        //
        sstr Get_ColumnDescriptionLong() const noexcept;

        sstr Get_ColumnDescriptionShort() const noexcept;

        sstr Get_ColumnHeader() const noexcept;

        sstr Get_LeftFillCharacter() const noexcept;

        //
        usInt Get_DisplayWidth() const noexcept;

        usInt Get_Precision() const noexcept;

        //
        void Copy_Values(const DataColumnHeader &other)     noexcept;

        void Set_ColumnHeader(const sstr value)             noexcept;

        void Set_ColumnDescriptionLong(const sstr value)    noexcept;

        //
        void Set_ColumnDescriptionShort(const sstr value)   noexcept;

        void Set_Debug()    noexcept;

        void UnSet_Debug()  noexcept;

        void Set_DisplayWidth(usInt value)              noexcept;

        void Set_LeftFillCharacter(const sstr value)    noexcept;

        void Set_MultiLineOutput(const bool value)      noexcept;

        void Set_Pad_Direction(const epadDir value)     noexcept;

        void Set_SQL_Quote(const bool value)            noexcept;

        //
        void Set_Precision(const usInt value) noexcept;

        void Show_Data_Header() const noexcept;

        void Show_Pad_Direction() const noexcept;
    };

};
#endif //DATAGRID_TEST_001_DATA_COLUMN_HEADER_H

