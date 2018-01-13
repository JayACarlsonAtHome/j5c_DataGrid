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



//
// Created by jay on 12/23/16.
//

#ifndef DATAGRID_TEST_001_DATA_DICTIONARY_H
#define DATAGRID_TEST_001_DATA_DICTIONARY_H

#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <iomanip>
#include <stdexcept>

#include "Common_Functions.h"
#include "DataColumnHeader.h"

namespace J5C_DSL_Code {

    using epadDir = enum_pad_direction;
    using usInt   = unsigned int;
    using sstr    = std::string;
    using usLong  = unsigned long ;


    class DataDictionary {
    private:

        static const auto s_max = std::numeric_limits<usLong>::max();

 //       static notFound_DCH std::vector<DataColumnHeader>::max_size();

        Common_Functions m_cf;
        bool m_is_full;
        bool m_is_empty;
        bool m_debug;
        bool m_is_silent;
        //
        usLong m_version;
        //
        std::vector<DataColumnHeader> mv_data_column_header;
        //
        sstr Get_TempValueWithPadding(const epadDir padDir, const sstr value, const sstr padding, const usLong column_width, const usInt precision, const bool isHeader)  noexcept;
        //
        usLong DoesExist_Column(const sstr data_column_header) noexcept;
        //
        void Add_ColumnNow(DataColumnHeader& dch) noexcept;
        void Clear()                              noexcept;
        void Display_Column(const usLong i) const noexcept;
        void Init(const bool is_silent)           noexcept;
        void Show_ColumnAlreadyExists()     const noexcept;
        void Show_DictionaryIsAlreadyFull() const noexcept;
        void Show_DictionaryIsEmpty()       const noexcept;
        void Show_DictionaryIsNowFull()     const noexcept;


    public:
        DataDictionary()                                noexcept;
        DataDictionary(const bool is_silent)            noexcept;
        virtual ~DataDictionary()                       noexcept;

        DataColumnHeader&
        Get_DataColumnHeader(DataColumnHeader& dch,
                                 const usLong i)        noexcept;

        usLong Add(DataColumnHeader& dch)               noexcept;
        void   Set_Debug()                              noexcept;
        void   UnSet_Debug()                            noexcept;
        void   Set_SQL_Quotes(const usLong i)           noexcept;
        void   UnSet_SQL_Quotes(const usLong i)         noexcept;
        void   Remove( const sstr data_column_header)   noexcept;
        void   Replace(const sstr data_column_header,
                       DataColumnHeader& dch)           noexcept;

        bool   Get_SQL_Quotes(const usLong i)                       const noexcept;
        usLong Get_ColumnWidthSize(const usLong index)              const noexcept;
        usLong Get_DataColumnIndex(const sstr data_column_header)   const noexcept;
        usLong Get_Size()                                           const noexcept;
        usLong Get_Version()                                        const noexcept;

        sstr   Get_Address_As_String(const usLong i)                const noexcept;
        sstr   Get_HeaderName(const usLong i)                       const noexcept;
        sstr   Get_HeaderNameWithPadding(const usLong index)        const noexcept;
        sstr   Get_ValueWithPadding(const usLong index,
                                    sstr value,
                                    const usLong max_width)         const noexcept;
        void Show_DataDictionaryAll()                               const noexcept;


    };


#endif //DATAGRID_TEST_001_DATA_DICTIONARY_H
}
