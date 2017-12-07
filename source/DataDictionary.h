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

#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <stdexcept>

#include "Common_Functions.h"
#include "DataColumnHeader.h"

namespace J5C_DSL_Code {

//
// Created by jay on 12/23/16.
//

#ifndef DATAGRID_TEST_001_DATA_DICTIONARY_H
#define DATAGRID_TEST_001_DATA_DICTIONARY_H

    using usLong =  unsigned long ;


    class DataDictionary {
    private:

        static const usLong s_max = std::numeric_limits<usLong>::max();
        Common_Functions m_cf;
        bool m_is_full;
        bool m_debug;
        bool m_is_silent;
        //
        usLong m_version;
        //
        std::vector<DataColumnHeader> mv_data_column_header;
        //
        sstr Get_TempValueWithPadding(const enum_padDir padDir, const sstr value, const sstr padding, const usLong column_width, const usInt precision, const bool isHeader)  noexcept;
        //
        usLong DoesExist_Column(const sstr data_column_header) noexcept;
        //
        void Add_ColumnNow(DataColumnHeader& dch) noexcept;
        void Clear() noexcept;
        void Display_Column(const usLong i) noexcept;
        void Init(const bool is_silent) noexcept;
        void Show_ColumnAlreadyExists() noexcept;
        void Show_DictionaryIsAlreadyFull() noexcept;
        void Show_DictionaryIsEmpty() noexcept;
        void Show_DictionaryIsNowFull() noexcept;


    public:
        DataDictionary() noexcept;
        DataDictionary(const bool is_silent) noexcept;
        virtual ~DataDictionary() noexcept;

        //
        DataColumnHeader Get_DataColumnHeader(const usLong i) noexcept;
        //
        bool   Get_SQL_Quotes(const usLong i) noexcept;
        //
        sstr   Get_HeaderName(const usLong i) noexcept;
        sstr   Get_HeaderNameWithPadding(const usLong index) noexcept;
        sstr   Get_ValueWithPadding(const usLong index, sstr value, const usLong max_width) noexcept;
        //
        usLong Add(DataColumnHeader& dch) noexcept;
        usLong Get_ColumnWidthSize(const usLong index) noexcept;
        usLong Get_DataColumnIndex(const sstr data_column_header) noexcept;
        usLong Get_Size() noexcept;
        usLong Get_Version() noexcept;
        //
        void   Display_Address(const usLong i) noexcept;

        void   Set_Debug() noexcept;
        void   UnSet_Debug() noexcept;
        void   Set_SQL_Quotes(const usLong i) noexcept;
        void   UnSet_SQL_Quotes(const usLong i) noexcept;

        void   Remove(const sstr data_column_header) noexcept;
        void   Replace(const sstr data_column_header, std::unique_ptr<DataColumnHeader>& dch) noexcept;
        void   Show_DataDictionaryAll() noexcept;
    };


#endif //DATAGRID_TEST_001_DATA_DICTIONARY_H
}