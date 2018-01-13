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

    DataColumnHeader::DataColumnHeader(bool debug) noexcept
    {
        init(debug);
    }

    DataColumnHeader::DataColumnHeader(const DataColumnHeader &other) noexcept
    {
        this->Copy_Values(other);
    }

    void DataColumnHeader::init(bool debug) noexcept
    {
        m_debug                     = debug;
        m_multi_line_output         = s_default_multi_line_output;
        m_sql_quote                 = false;
        m_pad_direction             = s_default_pad_direction;
        m_column_header             = "Default Header Name";
        m_column_description_long   = "Default Header Long  Description";
        m_column_description_short  = "Default Header Short Description";
        m_left_fill_char            = " ";
        m_display_width             = 25;
        m_precision                 = 8;

        if (m_debug)
        {
            std::cout << "Calling DataColumnHeader Constructor" << std::endl;
        }

    }


     DataColumnHeader::DataColumnHeader(const bool debug,
                              const bool multi_line_output,
                              const bool sql_quote,
                              const epadDir pad_direction,
                              const sstr column_header,
                              const sstr column_description_long,
                              const sstr column_description_short,
                              const sstr left_fill_char,
                              const usInt display_width,
                              const usInt precision) noexcept
    {
        m_debug                     = debug;
        m_multi_line_output         = multi_line_output;
        m_sql_quote                 = sql_quote;
        m_pad_direction             = pad_direction;
        m_column_header             = column_header;
        m_column_description_long   = column_description_long;
        m_column_description_short  = column_description_short;
        m_left_fill_char            = left_fill_char;
        m_display_width             = display_width;
        m_precision                 = precision;
    }



    DataColumnHeader::DataColumnHeader()
    {
        this->init(false);
    }

    DataColumnHeader::~DataColumnHeader() noexcept {
        if (m_debug) {
            std::cout << "Calling DataColumnHeader Destructor" << std::endl;
        }
    }

    bool DataColumnHeader::Get_Debug() const noexcept
    {
        return m_debug;
    }

    bool DataColumnHeader::Get_Multi_Line_Enabled() const noexcept {
        return m_multi_line_output;
    }

    bool DataColumnHeader::Get_SQL_Quote() const noexcept {
        return m_sql_quote;
    }

    epadDir DataColumnHeader::Get_Pad_Direction() const noexcept {
        return this->m_pad_direction;
    }

    sstr DataColumnHeader::Get_ColumnDescriptionLong() const noexcept {
        return this->m_column_description_long;
    }

    sstr DataColumnHeader::Get_ColumnDescriptionShort() const noexcept {
        return this->m_column_description_short.substr(0, m_display_width);
    }

    sstr DataColumnHeader::Get_ColumnHeader() const noexcept {
        return this->m_column_header;
    }

    sstr DataColumnHeader::Get_LeftFillCharacter() const noexcept {
        return m_left_fill_char;
    }


    usInt DataColumnHeader::Get_DisplayWidth() const noexcept {
        return this->m_display_width;
    }

    usInt DataColumnHeader::Get_Precision() const noexcept {
        return m_precision;
    }


    void DataColumnHeader::Copy_Values(const DataColumnHeader& other) noexcept {

        if (this->Get_Address_as_String() != other.Get_Address_as_String())  // prevent self move or assignment
        {
            m_debug                     = other.m_debug;
            m_multi_line_output         = other.m_multi_line_output;
            m_sql_quote                 = other.m_sql_quote;
            m_pad_direction             = other.m_pad_direction;
            m_column_header             = other.m_column_header;
            m_column_description_long   = other.m_column_description_long;
            m_column_description_short  = other.m_column_description_short;
            m_left_fill_char            = other.m_left_fill_char;
            m_display_width             = other.m_display_width;
            m_precision                 = other.m_precision;
        }
    }


    std::string DataColumnHeader::Get_Address_as_String() const noexcept {
        std::stringstream ss;
        ss << this;
        return ss.str();
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

    void DataColumnHeader::Set_Pad_Direction(const epadDir value) noexcept {
        m_pad_direction = value;
    }

    void DataColumnHeader::Set_Precision(const usInt value) noexcept {
        m_precision = value;
    }

    void DataColumnHeader::Set_SQL_Quote(const bool value) noexcept {
        m_sql_quote = value;
    }

    void DataColumnHeader::Show_Data_Header() const noexcept {
        std::cout << "Data Column Header Details:" << std::endl;
        std::cout << "Column Header:       " << this->Get_ColumnHeader() << std::endl;
        std::cout << "Description (Short): " << this->Get_ColumnDescriptionShort()   << std::endl;
        std::cout << "Description (Long) : " << this->Get_ColumnDescriptionLong()    << std::endl;
        std::cout << "Multi-line Enabled : " <<  std::boolalpha <<  this->Get_Multi_Line_Enabled() << std::endl;
        std::cout << "Width:     "           << this->Get_DisplayWidth()                 << std::endl;
        std::cout << "Precision: "           << this->Get_Precision()                    << std::endl;
        std::cout << "Padding:   ";             this->Show_Pad_Direction();            std::cout    << std::endl;
        std::cout << "Left Fill: \""         << this->Get_LeftFillCharacter() << "\""    << std::endl;
    }

    void DataColumnHeader::Show_Pad_Direction() const noexcept {
        sstr result;
        switch (m_pad_direction) {
            case epadDir::unknown : {
                result = "Unknown ";
                break;
            }
            case epadDir::left : {
                result = "Left ";
                break;
            }
            case epadDir::right : {
                result = "Right ";
                break;
            }
            case epadDir::both : {
                result = "Both ";
                break;
            }
            case epadDir::decimal : {
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
