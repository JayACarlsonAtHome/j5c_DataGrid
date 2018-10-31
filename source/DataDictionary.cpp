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

#include "DataDictionary.h"

namespace J5C_DSL_Code {

//
// Created by jay on 12/23/16.
//

//
// Private Methods
//

    usLong DataDictionary::DoesExist_Column(const sstr data_column_header) noexcept {
        sstr data_dictionary_header;
        auto found_column_header = mv_data_column_header.max_size();
        const auto max = mv_data_column_header.size();
        for (auto i = 0UL; i < max; i++) {
            data_dictionary_header = mv_data_column_header[i].Get_ColumnHeader();
            if (data_dictionary_header == data_column_header) {
                found_column_header = i;
                break;
            }
        }
        return found_column_header;
    }

    void DataDictionary::Add_ColumnNow(DataColumnHeader& dch) noexcept
    {
        m_is_empty = false;
        ++m_version;
        this->mv_data_column_header.push_back(dch);

    }

    void DataDictionary::Clear() noexcept {
        m_is_full = false;
        m_is_empty = true;
        m_version = 0;
        mv_data_column_header.clear();
        mv_data_column_header.reserve(10);
    }

    void DataDictionary::Display_Column(const usLong i) const noexcept {
        // This prints out all the data columns of the data dictionary or at least between start and stop

        std::cout << "DataDictionary Column Number:  " << std::setfill('0') << std::setw(4) << i << std::endl;
        sstr Address = Get_Address_As_String(i);
        if (Address.length() > 0)
        {
            std::cout << "  Column Address:   " << Address << std::endl;
        }

        std::cout << "  Column Name with padding: ***" << Get_HeaderNameWithPadding(i) << "*** "<< std::endl;
        std::cout << "  Column Name:      " << mv_data_column_header[i].Get_ColumnHeader() << std::endl;

        std::cout << "  Column Width:     " << mv_data_column_header[i].Get_DisplayWidth() << std::endl;
        std::cout << "  Column Precision: " << mv_data_column_header[i].Get_Precision()    << std::endl;
        std::cout << "  Column Short Description: "
                  << mv_data_column_header[i].Get_ColumnDescriptionShort()                 << std::endl;
        std::cout << "  Column Long  Description: "
                  << mv_data_column_header[i].Get_ColumnDescriptionLong()                  << std::endl;
        std::cout << "  Columm SQL_Quotes: " << Get_SQL_Quotes(i);
        std::cout << std::endl << std::endl;
    }

    void DataDictionary::Init(const bool is_silent) noexcept {
        Clear();
        m_is_silent = is_silent;
        m_version++;
    }

    void DataDictionary::Show_ColumnAlreadyExists() const noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataColumn already exists; No column added to data dictionary."
                      << std::endl;
        }
    }

    void DataDictionary::Show_DictionaryIsNowFull() const noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataDictionary is now full." << std::endl;
        }
    }

    void DataDictionary::Show_DictionaryIsAlreadyFull() const noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataDictionary is already full. No column added to data dictionary."
                      << std::endl;
        }
    }


    void DataDictionary::Show_DictionaryIsEmpty() const noexcept {
        std::cout << "The data dictionary is empty." << std::endl;
    }


    bool DataDictionary::Validate_String_is_Numeric(std::string str) const noexcept
    {
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


//
// Public Methods
//

    DataDictionary::DataDictionary() noexcept {
        bool not_silent = false;
        Init(not_silent);
    }

    DataDictionary::DataDictionary(const bool is_silent) noexcept {
        Init(is_silent);
    }

    DataDictionary::~DataDictionary() noexcept {
        if (m_debug) {
            std::cout << "Calling DataDictionary Destructor" << std::endl;
        }
        mv_data_column_header.clear();
    }

    DataColumnHeader& DataDictionary::Get_DataColumnHeader(DataColumnHeader& dch, const usLong i) noexcept {
                if (i < mv_data_column_header.size()) {
            dch.Copy_Values(mv_data_column_header.at(i));
        }
        return dch;
    }

    sstr DataDictionary::Get_HeaderName(const usLong i) const noexcept {
        return mv_data_column_header[i].Get_ColumnHeader();
    }

    sstr DataDictionary::Get_HeaderNameWithPadding(const usLong index) const noexcept {

        const auto column_width = mv_data_column_header[index].Get_DisplayWidth();
        const auto size = mv_data_column_header.size();
        const bool isHeader = true;

        sstr display_header = "";
        sstr padding = "";
        sstr curr_header = mv_data_column_header[index].Get_ColumnHeader();
        epadDir padDir = mv_data_column_header[index].Get_Pad_Direction();

        if (index < size) {
            auto pad_length = column_width - curr_header.length();
            padding = std::string(pad_length, ' ');
            display_header = Get_ValueWithPadding(index, curr_header, size, isHeader);
        }
        return display_header;
    }

    sstr DataDictionary::Get_ValueWithPadding(const usLong index, sstr value, const usLong max_width, bool isHeader) const noexcept
    {

        const auto column_width = mv_data_column_header[index].Get_DisplayWidth();
        const auto size         = mv_data_column_header.size();
        epadDir padDir          = mv_data_column_header[index].Get_Pad_Direction();
        const auto precision    = mv_data_column_header[index].Get_Precision();
        auto pad_length         = column_width - column_width;
        auto p1_2               = pad_length - pad_length;
        auto value_length       = value.length();


        if (isHeader)
        {
            if (padDir == enum_pad_direction::decimal)
            {
                padDir = enum_pad_direction::right;
            }
        }
        if (value_length > column_width)
        {
            value = value.substr(0,column_width);
        }

        if (column_width > value_length)
        {
            pad_length   = column_width - value_length;
        }

        bool is_decimal;
        sstr display_value;
        sstr padding;
        switch (padDir)
        {
            case epadDir::unknown :
            case epadDir::left :
                display_value = value;
                padding = std::string(pad_length, ' ');
                display_value.append(padding);
                break;
            case epadDir::right :
                padding = std::string(pad_length, ' ');
                display_value = padding;
                display_value.append(value);
                break;
            case epadDir::both :
                p1_2 = pad_length / 2;
                padding = std::string(p1_2, ' ');
                display_value = padding;
                display_value.append(value);
                display_value.append(padding);
                if (display_value.length() < column_width)
                {
                    display_value.append(" ");
                }
                break;
            case epadDir::decimal :
                is_decimal = Validate_String_is_Numeric(value);
                if (is_decimal) {
                    auto pos = value.find('.');
                    if (pos == snl_max) // was not found
                    {
                        if (column_width > value_length + precision + 1)
                        {
                            pad_length  = column_width;
                            pad_length -= value_length;
                            pad_length -= precision;
                            pad_length -= 1; // for the decimal place holder -- i.e. the dot -- "."
                        }
                        if (pad_length > 0)
                        {
                            padding = std::string(pad_length, ' ');
                        }
                        else
                        {
                            padding = "";
                        }
                        display_value = padding;
                        display_value.append(value);
                        sstr temp = std::string(precision, '0');
                        display_value.append(".");
                        display_value.append(temp);
                    }
                    else
                    {
                        pos = value.find('.');
                        if (((value.length() - pos)) < precision)  // Add trailing zeros
                        {
                            sstr temp = std::string(precision, '0');
                            value.append(temp);
                            display_value = value.substr(0, (pos + precision + 1));

                        }
                        pos = value.find('.');
                        if ((value.length() - pos) > precision)  // trim off trailing digits
                        {
                            display_value = value.substr(0, (pos + precision + 1));
                        }
                        // now we have to reset the padding based on new working value
                        pad_length = column_width - value.length();
                        if (pad_length > 0) {
                            sstr temp = std::string(pad_length, ' ');
                            display_value = temp;
                            display_value.append(value);
                        }
                    }
                }
                else
                {
                    display_value = "NaN: ";
                    display_value.append(value);
                    auto pad_length = column_width - display_value.length();
                    if (pad_length > 0 && pad_length < column_width) {
                        sstr temp = std::string(pad_length, ' ');
                        display_value.append(temp);
                    }
                }
                break;
        }
        return display_value;
    }

    usLong DataDictionary::Add(DataColumnHeader& dch) noexcept {
        usLong result = 0;
        if (!m_is_full) {
            const auto beforeSize = mv_data_column_header.size();
            const auto found = Get_DataColumnIndex(dch.Get_ColumnHeader());
            auto s_max = mv_data_column_header.max_size();
            if (found >= s_max) {
                Add_ColumnNow(dch);
                result = mv_data_column_header.size() - 1;
            } else {
                result = found;
                Show_ColumnAlreadyExists();
            }
            const auto afterSize = mv_data_column_header.size();
            // snl_max is equivalent to -1 equivalent to full
            if (afterSize == s_max) {
                m_is_full = true;
                Show_DictionaryIsNowFull();
            }
        } else {
            Show_DictionaryIsAlreadyFull();
        }
        if (mv_data_column_header.size() == 0)
        {
            m_is_empty = true;
        }
        else
        {
            m_is_empty = false;
        }
        return result;
    }

    usLong DataDictionary::Get_DataColumnIndex(const sstr data_column_header) const noexcept {
        auto result = mv_data_column_header.max_size();
        auto max_vector_element = mv_data_column_header.size();
        if (max_vector_element > 0)
        {
            --max_vector_element;
        }
        if (!m_is_full) {
            usLong size = mv_data_column_header.size();
            for (auto i = 0UL; i < size; i++) {
                if (mv_data_column_header[i].Get_ColumnHeader() == data_column_header) {
                    result = i;
                }
            }
        }
        if (result > max_vector_element)
        {
            std::cout << " *** Column \""   << data_column_header << "\" not found...\n";
            result = -1;
        }
        return result;
    }

    usLong DataDictionary::Get_Size() const noexcept {
        return this->mv_data_column_header.size();
    }

    usLong DataDictionary::Get_Version() const noexcept {
        return m_version;
    }

    usLong DataDictionary::Get_ColumnWidthSize(const usLong index) const noexcept {
        const auto size = mv_data_column_header.size();
        if (index < size) {
            return this->mv_data_column_header[index].Get_DisplayWidth();
        } else {
            return 25UL;
        }
    }

    sstr DataDictionary::Get_Address_As_String(const usLong i) const noexcept {
        return mv_data_column_header[i].Get_Address_as_String();
    }


    void DataDictionary::Remove(const sstr data_column_header) noexcept {
        bool removed = false;
        auto begin = mv_data_column_header.begin();
        auto end = mv_data_column_header.end();
        for (auto it = begin; it < end; it++) {
            if (it->Get_ColumnHeader() == data_column_header) {
                mv_data_column_header.erase(it);
                removed = true;
                ++m_version;
                break;
            }
        }
        if (!removed) {
            std::cout << "Warning!!! The data column did not exist, so it could not be removed" << std::endl;
        }
        if (mv_data_column_header.size() == 0)
        {
            m_is_empty = true;
        }
    }

    void DataDictionary::Replace(const sstr data_column_header, DataColumnHeader& dch) noexcept {
        //
        //early return possible
        //
        const auto index = Get_DataColumnIndex(data_column_header);

        if (DoesExist_Column(dch.Get_ColumnHeader()) != snl_max) {
            Show_ColumnAlreadyExists();
            // early return
            return;
        }
        if (index != snl_max) {
            mv_data_column_header[index].Copy_Values(dch);
            m_version++;
        }
    }

    void DataDictionary::Show_DataDictionaryAll() noexcept {
        std::cout << "Show All Dictionary Columns" << std::endl;
        std::cout << "================================================" << std::endl;
        if (this->m_is_empty ) {
            this->Show_DictionaryIsEmpty();
        }
        else
        {
            for (const auto &element : mv_data_column_header)
            {
                element.Show_Data_Header();
            }
        }
    }

    void DataDictionary::Set_SQL_Quotes(const usLong i) noexcept {
        mv_data_column_header[i].Set_SQL_Quote(true);
    }

    void DataDictionary::UnSet_SQL_Quotes(const usLong i) noexcept {
        mv_data_column_header[i].Set_SQL_Quote(false);
    }

    bool DataDictionary::Get_SQL_Quotes(const usLong i) const noexcept {
        return mv_data_column_header[i].Get_SQL_Quote();
    }

    void DataDictionary::Set_Debug()  noexcept
    {
        m_debug = true;
    }

    void DataDictionary::UnSet_Debug() noexcept {
        m_debug = false;
    }
}
