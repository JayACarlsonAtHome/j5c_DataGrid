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

#include <iostream>

namespace J5C_DSL_Code {

#ifndef DATAGRID_TEST_001_DATA_COLUMN_HEADER_H
#define DATAGRID_TEST_001_DATA_COLUMN_HEADER_H

    enum class enum_pad_direction {
        unknown = 0, right = 1, left = 2, both = 3, decimal = 4
    };
    using enum_padDir = enum_pad_direction;
    using usInt   = unsigned int;
    using sstr    = std::string;

    class DataColumnHeader {

    private:
        //
        // static variables
        //
        static const bool s_default_multi_line_output = false;
        static const enum_padDir s_default_pad_direction = enum_padDir::right;
        //
        static const usInt s_default_display_width = 25;
        static const usInt s_default_precision = 5;
        //
        // non static variables
        //
        bool m_debug                { false };
        bool m_multi_line_output    { false };
        bool m_sql_quote            { false };


        enum_padDir m_pad_direction { enum_pad_direction ::left };
        //
        sstr m_column_header                { "Default Header Name"};
        sstr m_column_description_long      { "Default Header Long Description"};
        sstr m_column_description_short     { "Default Short Description"};
        sstr m_left_fill_char               { " " };
        //
        usInt m_display_width               { 25 };
        usInt m_precision                   {  8 };

        void init(bool debug) noexcept;

        //
    public:

        explicit DataColumnHeader(std::unique_ptr<DataColumnHeader> &other) noexcept;         // copy constructor
        // Constructors
        DataColumnHeader()  noexcept;

        explicit DataColumnHeader(bool debug)  noexcept;
        virtual ~DataColumnHeader()  noexcept;


        //
        bool Get_Multi_Line_Enabled() noexcept;
        bool Get_SQL_Quote() noexcept;

        //
        DataColumnHeader*  Get_Address() noexcept;
        enum_pad_direction Get_Pad_Direction() noexcept;
        //
        sstr Get_ColumnDescriptionLong() noexcept;
        sstr Get_ColumnDescriptionShort() noexcept;
        sstr Get_ColumnHeader() noexcept;
        sstr Get_LeftFillCharacter() noexcept;
        //
        usInt Get_DisplayWidth() noexcept;
        usInt Get_Precision() noexcept;
        //
        void Copy_Values(std::unique_ptr<DataColumnHeader>& other) noexcept;
        void Display_Address() noexcept;
        void Initialize(const usInt display_width, const usInt precision, bool multi_line_enabled, const enum_padDir padding, const sstr left_fill_char,
                        const sstr column_header,  const sstr column_description_short, const sstr column_description_long) noexcept;
        void Set_ColumnHeader(const sstr value)  noexcept;
        void Set_ColumnDescriptionLong(const sstr value) noexcept;
        //
        void Set_ColumnDescriptionShort(const sstr value) noexcept;
        void Set_Debug() noexcept;
        void UnSet_Debug() noexcept;
        void Set_DisplayWidth(usInt value) noexcept;
        void Set_LeftFillCharacter(const sstr value) noexcept;
        void Set_MultiLineOutput(const bool value) noexcept;
        void Set_Pad_Direction(const enum_padDir value) noexcept;
        void Set_SQL_Quote(const bool value) noexcept;
        //
        void Set_Precision(const usInt value) noexcept;
        void Show_Data_Header() noexcept;
        void Show_Pad_Direction() noexcept;
    };


#endif //DATAGRID_TEST_001_DATA_COLUMN_HEADER_H
}