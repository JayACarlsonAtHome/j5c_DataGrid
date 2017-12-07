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

    void DataDictionary::Add_ColumnNow(DataColumnHeader& dch) noexcept {
        this->mv_data_column_header.push_back(dch);
    }

    void DataDictionary::Clear() noexcept {
        m_is_full = false;
        mv_data_column_header.clear();
        mv_data_column_header.reserve(10);
    }

    void DataDictionary::Display_Column(const usLong i) noexcept {
        // This prints out all the data columns of the data dictionary or at least between start and stop
        std::cout << "DataDictionary Column Number:  " << std::setfill('0') << std::setw(4) << i << std::endl;
        Display_Address(i);
        std::cout << "  Column Name:      " << mv_data_column_header[i].Get_ColumnHeader() << std::endl;
        std::cout << "  Column Width:     " << mv_data_column_header[i].Get_DisplayWidth() << std::endl;
        std::cout << "  Column Precision: " << mv_data_column_header[i].Get_Precision() << std::endl;
        std::cout << "  Column Short Description: " << mv_data_column_header[i].Get_ColumnDescriptionShort()
                  << std::endl;
        std::cout << "  Column Long  Description: " << mv_data_column_header[i].Get_ColumnDescriptionLong()
                  << std::endl;
        std::cout << std::endl << std::endl;
    }

    void DataDictionary::Init(const bool is_silent) noexcept {
        Clear();
        m_is_silent = is_silent;
        m_version++;
    }

    void DataDictionary::Show_ColumnAlreadyExists() noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataColumn already exists; No column added to data dictionary."
                      << std::endl;
        }
    }

    void DataDictionary::Show_DictionaryIsNowFull() noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataDictionary is now full." << std::endl;
        }
    }

    void DataDictionary::Show_DictionaryIsAlreadyFull() noexcept {
        if (!m_is_silent) {
            std::cout << "Warning!!! -- The DataDictionary is already full. No column added to data dictionary."
                      << std::endl;
        }
    }


    void DataDictionary::Show_DictionaryIsEmpty() noexcept {
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

    sstr DataDictionary::Get_HeaderName(const usLong i) noexcept {
        return mv_data_column_header[i].Get_ColumnHeader();
    }

    sstr DataDictionary::Get_HeaderNameWithPadding(const usLong index) noexcept {

        const auto column_width = mv_data_column_header[index].Get_DisplayWidth();
        const auto size = mv_data_column_header.size();

        sstr display_header = "";
        sstr padding = "";
        sstr curr_header = mv_data_column_header[index].Get_ColumnHeader();
        epadDir padDir = mv_data_column_header[index].Get_Pad_Direction();

        if (index < size) {
            auto pad_length = column_width - curr_header.length();
            padding = std::string(pad_length, ' ');
            display_header = Get_TempValueWithPadding(padDir, curr_header, padding, column_width, 0, true);
        }
        return display_header;
    }


    sstr DataDictionary::Get_TempValueWithPadding(const epadDir padDir, const sstr value, const sstr padding,
                                                  const usLong column_width, const usInt precision,
                                                  const bool isHeader) noexcept {

        auto padding1 = padding;
        auto pad_length = padding.length() / 2;
        bool is_decimal;
        sstr working_value = value;
        sstr temp = "";
        sstr display_value = "";

        switch (padDir) {
            case epadDir::unknown :
                display_value = value;
                display_value.append(padding);
                break;
            case epadDir::left :
                display_value = padding;
                display_value.append(value);
                break;
            case epadDir::decimal :
                is_decimal = this->m_cf.validate_string_is_numeric(value);
                if (is_decimal) {
                    auto pos = value.find('.');
                    if (pos == s_max) // was not found
                    {
                        temp = std::string(precision, '0');
                        working_value.append(".");
                        working_value.append(temp);
                    }
                    pos = working_value.find('.');
                    if (((working_value.length() - pos)) <= precision)  // Add trailing zeros
                    {
                        temp = std::string(precision, '0');
                        working_value.append(temp);
                        working_value = working_value.substr(0, (pos + precision + 1));

                    }
                    pos = working_value.find('.');
                    if ((working_value.length() - pos) > precision)  // trim off trailing digits
                    {
                        working_value = working_value.substr(0, (pos + precision + 1));
                    }
                    // now we have to reset the padding based on new working value
                    pad_length = column_width - working_value.length();
                    if (pad_length > 0) {
                        temp = std::string(pad_length, ' ');
                        display_value.append(temp);
                        display_value.append(working_value);
                    }
                } else {
                    if (isHeader) {
                        padding1 = padding.substr(0, pad_length);
                        if (((pad_length * 2) + value.length()) < column_width) {
                            display_value = std::string(1, ' ');
                        }
                        display_value.append(padding1);
                        display_value.append(value);
                        display_value.append(padding1);
                    } else {

                        display_value = "NaN: ";
                        display_value.append(value);
                        pad_length = column_width - display_value.length();
                        if (pad_length > 0) {
                            temp = std::string(pad_length, ' ');
                            display_value.append(temp);
                        }

                    }
                }
                break;
            case epadDir::right :
                display_value = working_value;
                display_value.append(padding);
                break;

            case epadDir::both :
                // account for column widths that are odd.
                padding1 = padding.substr(0, pad_length);
                if (((pad_length * 2) + value.length()) < column_width) {
                    display_value = std::string(1, ' ');
                }
                display_value.append(padding1);
                display_value.append(value);
                display_value.append(padding1);
                break;
        }
        return display_value;
    }

    sstr DataDictionary::Get_ValueWithPadding(const usLong index, sstr value, const usLong max_width) noexcept {

        const auto column_width = mv_data_column_header[index].Get_DisplayWidth();
        const auto size = mv_data_column_header.size();
        const epadDir padDir = mv_data_column_header[index].Get_Pad_Direction();
        const auto precision = mv_data_column_header[index].Get_Precision();
        // variables
        sstr display_value = "";
        sstr padding = "";

        if (index < size) {
            usLong pad_length;
            if ((value.length() < max_width) && (padDir == epadDir::both)) {
                pad_length = max_width - value.length();
                display_value = std::string(pad_length, ' ');
                display_value.append(value);
                display_value = std::string(pad_length, ' ');
                display_value.append(value);
                value = display_value;
                display_value.clear();
            }
            pad_length = column_width - value.length();
            padding = std::string(pad_length, ' ');
            display_value = Get_TempValueWithPadding(padDir, value, padding, column_width, precision, false);
        }
        return display_value;
    }


    usLong DataDictionary::Add(DataColumnHeader& dch) noexcept {
        usLong result = 0;
        if (!m_is_full) {
            usLong size = mv_data_column_header.size();
            if (size > 0) {
                const auto found = Get_DataColumnIndex(dch.Get_ColumnHeader());
                // s_max is equivalent to -1 equivalent to not-found
                if (found == s_max) {
                    Add_ColumnNow(dch);
                    result = mv_data_column_header.size() - 1;
                } else {
                    result = found;
                    Show_ColumnAlreadyExists();
                }
            } else {
                Add_ColumnNow(dch);
                result = mv_data_column_header.size() - 1;
            }
            size = mv_data_column_header.size();
            // s_max is equivalent to -1 equivalent to full
            if (size == s_max) {
                m_is_full = true;
                Show_DictionaryIsNowFull();
            }
        } else {
            Show_DictionaryIsAlreadyFull();
        }

        return result;
    }

    usLong DataDictionary::Get_DataColumnIndex(const sstr data_column_header) noexcept {
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

    usLong DataDictionary::Get_Size() noexcept {
        return this->mv_data_column_header.size();
    }

    usLong DataDictionary::Get_Version() noexcept {
        return m_version;
    }

    usLong DataDictionary::Get_ColumnWidthSize(const usLong index) noexcept {
        const auto size = mv_data_column_header.size();
        if (index < size) {
            return this->mv_data_column_header[index].Get_DisplayWidth();
        } else {
            return 25UL;
        }
    }

    void DataDictionary::Display_Address(const usLong i) noexcept {
        std::cout << "  Column Address: ";
        mv_data_column_header[i].Get_Address_as_String();
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

    void DataDictionary::Replace(const sstr data_column_header, std::unique_ptr<DataColumnHeader>& dch) noexcept {
        //
        //early return possible
        //
        const auto index = Get_DataColumnIndex(data_column_header);

        if (DoesExist_Column(dch->Get_ColumnHeader()) != s_max) {
            Show_ColumnAlreadyExists();
            // early return
            return;
        }
        if (index != s_max) {
            mv_data_column_header[index].Copy_Values(*dch);
            m_version++;
        }
    }

    void DataDictionary::Show_DataDictionaryAll() noexcept {
        if (!mv_data_column_header.empty()) {
            const auto max = mv_data_column_header.size();
            for (auto i = 0UL; i < max; i++) {
                try {
                    mv_data_column_header.at(i).Get_DisplayWidth();
                    Display_Column(i);
                }
                catch (const std::exception e) {
                    i = max;
                }
            }
        } else {
            Show_DictionaryIsEmpty();
        }
    }

    void DataDictionary::Set_SQL_Quotes(const usLong i) noexcept {
        mv_data_column_header[i].Set_SQL_Quote(true);
    }

    void DataDictionary::UnSet_SQL_Quotes(const usLong i) noexcept {
        mv_data_column_header[i].Set_SQL_Quote(false);
    }

    bool DataDictionary::Get_SQL_Quotes(const usLong i) noexcept {
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
