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

#include "DataColumnHeader.h"

namespace J5C_DSL_Code {


//
// Created by jay on 12/23/16.
//

//
// private methods
//

//
// public methods
//

    DataColumnHeader::DataColumnHeader(std::unique_ptr<DataColumnHeader> &other) noexcept
    {
        //std::cout << "Copy Constructor" << std::endl;
        Copy_Values(other);
    }

    void DataColumnHeader::init(bool debug) noexcept
    {
        m_debug = debug;
        m_display_width = s_default_display_width;
        m_precision = s_default_precision;
        m_multi_line_output = false;
        m_pad_direction = s_default_pad_direction;
        m_left_fill_char = " ";

        m_column_header = "Default Header";
        m_column_description_short = "Default Short Description";
        m_column_description_long = "Default Long  Description";
        if (m_debug)
        {
            std::cout << "Calling DataColumnHeader Constructor" << std::endl;
        }

    }

    DataColumnHeader::DataColumnHeader() noexcept
    {
        this->init(false);
    }

    DataColumnHeader::DataColumnHeader(bool debug) noexcept
    {
        this->init(debug);
    }

    DataColumnHeader::~DataColumnHeader() noexcept {
        if (m_debug) {
            std::cout << "Calling DataColumnHeader Destructor" << std::endl;
        }
    }


    bool DataColumnHeader::Get_Multi_Line_Enabled() noexcept {
        return m_multi_line_output;
    }

    bool DataColumnHeader::Get_SQL_Quote() noexcept {
        return m_sql_quote;
    }

    DataColumnHeader *DataColumnHeader::Get_Address()  noexcept{
        return this;
    }

    enum_padDir DataColumnHeader::Get_Pad_Direction() noexcept {
        return this->m_pad_direction;
    }

    sstr DataColumnHeader::Get_ColumnDescriptionLong() noexcept {
        return this->m_column_description_long;
    }

    sstr DataColumnHeader::Get_ColumnDescriptionShort() noexcept {
        return this->m_column_description_short.substr(0, m_display_width);
    }

    sstr DataColumnHeader::Get_ColumnHeader() noexcept {
        return this->m_column_header;
    }

    sstr DataColumnHeader::Get_LeftFillCharacter() noexcept {
        return m_left_fill_char;
    }


    usInt DataColumnHeader::Get_DisplayWidth() noexcept {
        return this->m_display_width;
    }

    usInt DataColumnHeader::Get_Precision() noexcept {
        return m_precision;
    }

    void DataColumnHeader::Copy_Values(std::unique_ptr<DataColumnHeader>& other) noexcept {
        //this is used
        //std::cout << "Copy Values" << std::endl;

        if (this->Get_Address() != other->Get_Address())  // prevent self move or assignment
        {
            this->m_display_width = other->m_display_width;
            this->m_precision = other->m_precision;
            this->m_multi_line_output = other->m_multi_line_output;
            this->m_pad_direction = other->m_pad_direction;
            this->m_left_fill_char = other->m_left_fill_char;

            this->m_column_header = other->m_column_header;
            this->m_column_description_long = other->m_column_description_long;
            this->m_column_description_short = other->m_column_description_short;
            this->m_sql_quote = other->m_sql_quote;
        }
    }

    void DataColumnHeader::Display_Address() noexcept {
        std::cout << this << std::endl;
    }

    void DataColumnHeader::Initialize(const usInt display_width, const usInt precision, const bool multi_line_enabled,
                                      const enum_padDir padding, const sstr left_fill_char,
                                      const sstr column_header, const sstr column_description_short,
                                      const sstr column_description_long) noexcept {
        m_debug = false;
        m_sql_quote = false;
        Set_DisplayWidth(display_width);
        Set_Precision(precision);
        Set_MultiLineOutput(multi_line_enabled);
        Set_Pad_Direction(padding);
        Set_LeftFillCharacter(left_fill_char);
        Set_ColumnHeader(column_header);
        Set_ColumnDescriptionShort(column_description_short);
        Set_ColumnDescriptionLong(column_description_long);
        Set_Pad_Direction(padding);
    }


    void DataColumnHeader::Set_ColumnHeader(const sstr value) noexcept {
        if (value.length() > m_display_width) {
            m_column_header = value.substr(0, m_display_width);
        } else {
            m_column_header = value;
        }
    }

    void DataColumnHeader::Set_ColumnDescriptionLong(const sstr value) noexcept {
        {
            m_column_description_long = value;
        }
    }

    void DataColumnHeader::Set_ColumnDescriptionShort(const sstr value) noexcept {
        if (value.length() > m_display_width) {
            m_column_description_short = value.substr(0, m_display_width);
        } else {
            m_column_description_short = value;
        }
    }

    void DataColumnHeader::Set_DisplayWidth(usInt value) noexcept {
        if (value < 1) {
            value = 25;
        }
        m_display_width = value;
    }

    void DataColumnHeader::Set_LeftFillCharacter(const sstr value) noexcept {
        m_left_fill_char = value;
    }

    void DataColumnHeader::Set_MultiLineOutput(const bool value) noexcept {
        m_multi_line_output = value;
    }

    void DataColumnHeader::Set_Pad_Direction(const enum_padDir value) noexcept {
        m_pad_direction = value;
    }

    void DataColumnHeader::Set_Precision(const usInt value) noexcept {
        m_precision = value;
    }

    void DataColumnHeader::Set_SQL_Quote(const bool value) noexcept {
        m_sql_quote = value;
    }

    void DataColumnHeader::Show_Data_Header() noexcept {
        std::cout << "Data Column Header Details:" << std::endl;
        std::cout << "Column Header:       "          << this->Get_ColumnHeader() << std::endl;
        std::cout << "Description (Short): "    << this->Get_ColumnDescriptionShort()   << std::endl;
        std::cout << "Description (Long) : "    << this->Get_ColumnDescriptionLong()    << std::endl;
        std::cout << "Multi-line Enabled : "    <<  std::boolalpha <<  this->Get_Multi_Line_Enabled() << std::endl;
        std::cout << "Width:     "      << this->Get_DisplayWidth()                 << std::endl;
        std::cout << "Precision: "      << this->Get_Precision()                    << std::endl;
        std::cout << "Padding:   ";        this->Show_Pad_Direction(); std::cout    << std::endl;
        std::cout << "Left Fill: \""    << this->Get_LeftFillCharacter() << "\""    << std::endl;


    }

    void DataColumnHeader::Show_Pad_Direction() noexcept {
        sstr result;
        switch (m_pad_direction) {
            case enum_padDir::unknown : {
                result = "Unknown ";
                break;
            }
            case enum_padDir::left : {
                result = "Left ";
                break;
            }
            case enum_padDir::right : {
                result = "Right ";
                break;
            }
            case enum_padDir::both : {
                result = "Both ";
                break;
            }
            case enum_padDir::decimal : {
                result = "Decimal ";
            }
        }
        std::cout << result;
    }

    void DataColumnHeader::Set_Debug() noexcept {
        m_debug = true;
    }
    void DataColumnHeader::UnSet_Debug() noexcept {
        m_debug = false;
    }
}