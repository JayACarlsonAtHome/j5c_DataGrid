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
        auto found_column_header = s_max;
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
        this->mv_data_column_header.push_back(dch);
    }

    void DataDictionary::Clear() noexcept {
        m_is_full = false;
        m_is_empty = true;
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

        sstr display_header = "";
        sstr padding = "";
        sstr curr_header = mv_data_column_header[index].Get_ColumnHeader();
        epadDir padDir = mv_data_column_header[index].Get_Pad_Direction();

        if (index < size) {
            auto pad_length = column_width - curr_header.length();
            padding = std::string(pad_length, ' ');
            display_header = Get_ValueWithPadding(index, curr_header, size);
        }
        return display_header;
    }

    sstr DataDictionary::Get_ValueWithPadding(const usLong index, sstr value, const usLong max_width) const noexcept
    {

        const auto column_width = mv_data_column_header[index].Get_DisplayWidth();
        const auto size         = mv_data_column_header.size();
        const epadDir padDir    = mv_data_column_header[index].Get_Pad_Direction();
        const auto precision    = mv_data_column_header[index].Get_Precision();
        auto pad_length   = size - column_width;
        auto p1_2 = pad_length / 2;
        bool is_decimal;
        sstr display_value = "value";
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
                padding = std::string(p1_2, ' ');
                display_value.append(padding);
                display_value.append(value);
                display_value.append(padding);
                if (display_value.length() < column_width)
                {
                    display_value.append(" ");
                }
                break;
            case epadDir::decimal :

                /*
                is_decimal = this->m_cf.validate_string_is_numeric(value);
                if (is_decimal) {
                    auto pos = value.find('.');
                    if (pos == s_max) // was not found
                    {
                        sstr temp = std::string(precision, '0');
                        display_value.append(".");
                        display_value.append(temp);
                    }
                    pos = value.find('.');
                    if (((value.length() - pos)) <= precision)  // Add trailing zeros
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
                        display_value.append(temp);
                        display_value.append(value);
                    }
                }
                else
                {
                    display_value = "NaN: ";
                    display_value.append(value);
                    auto pad_length = column_width - display_value.length();
                    if (pad_length > 0) {
                        sstr temp = std::string(pad_length, ' ');
                        display_value.append(temp);
                    }
                }
                */
                display_value = "Not Implemented Yet";
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
            // s_max is equivalent to -1 equivalent to full
            if (afterSize == s_max) {
                m_is_full = true;
                Show_DictionaryIsNowFull();
            }
        } else {
            Show_DictionaryIsAlreadyFull();
        }
        return result;
    }

    usLong DataDictionary::Get_DataColumnIndex(const sstr data_column_header) const noexcept {
        auto result = s_max;
        if (!m_is_full) {
            usLong size = mv_data_column_header.size();
            for (auto i = 0UL; i < size; i++) {
                if (mv_data_column_header[i].Get_ColumnHeader() == data_column_header) {
                    result = i;
                }
            }
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
                m_version++;
                break;
            }
        }
        if (!removed) {
            std::cout << "Warning!!! The data column did not exist, so it could not be removed" << std::endl;
        }
    }

    void DataDictionary::Replace(const sstr data_column_header, DataColumnHeader& dch) noexcept {
        //
        //early return possible
        //
        const auto index = Get_DataColumnIndex(data_column_header);

        if (DoesExist_Column(dch.Get_ColumnHeader()) != s_max) {
            Show_ColumnAlreadyExists();
            // early return
            return;
        }
        if (index != s_max) {
            mv_data_column_header[index].Copy_Values(dch);
            m_version++;
        }
    }

    void DataDictionary::Show_DataDictionaryAll() const noexcept {
        std::cout << "Show All Dictionary Columns" << std::endl;
        std::cout << "================================================" << std::endl;
        if (this->m_is_empty ) {
            this->Show_DictionaryIsEmpty();
        }
        else {
            auto max        = this->Get_Size();
            auto current    = 0;

            while (current < max) {
                mv_data_column_header[current].Show_Data_Header();
                ++current;
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
