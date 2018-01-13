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

#ifndef DATAGRID_TEST_001_DATAGRID_H
#define DATAGRID_TEST_001_DATAGRID_H


#include <string>
#include <limits>
#include <fstream>
#include <iostream>

#include "DataDictionary.h"

namespace J5C_DSL_Code {


    using sstr            = std::string;
    using usLong          = unsigned long;

    using DG_Row             = std::vector<sstr>;
    using DG_Vector          = std::vector<DG_Row >;
    using DD_Column_Index    = std::vector<usLong> ;
    using DD_Column_MaxWidth = std::vector<usLong> ;
    using DD_Box_Drawing     = std::vector<sstr >;

    enum class enum_border_type {
        unknown = 0, dashes = 1, light = 2, double_line = 3, heavy = 4, 
    };

    class DataGrid {
        //
    private:

        //Default border_type
        enum_border_type  m_border_type = enum_border_type::light;

        DD_Box_Drawing mv_box_characters;

        // Grid Border Unicode Definitions -- Light
        const sstr dashes_top__left = "\u250C";
        const sstr dashes_top_split = "\u252C";
        const sstr dashes_top_right = "\u2510";

        const sstr dashes_H__spacer = "\u254c";
        const sstr dashes_V__spacer = "\u2502";
        const sstr dashes_New__Line = "\n";

        const sstr dashes_mid__left = "\u251C";
        const sstr dashes_mid_split = "\u253C";
        const sstr dashes_mid_right = "\u2524";

        const sstr dashes_bot__left = "\u2514";
        const sstr dashes_bot_split = "\u2534";
        const sstr dashes_bot_right = "\u2518";

        // Grid Border Unicode Definitions -- Light
        const sstr light_top__left = "\u250C";
        const sstr light_top_split = "\u252C";
        const sstr light_top_right = "\u2510";

        const sstr light_H__spacer = "\u2500";
        const sstr light_V__spacer = "\u2502";
        const sstr light_New__Line = "\n";

        const sstr light_mid__left = "\u251C";
        const sstr light_mid_split = "\u253C";
        const sstr light_mid_right = "\u2524";

        const sstr light_bot__left = "\u2514";
        const sstr light_bot_split = "\u2534";
        const sstr light_bot_right = "\u2518";

        // Grid Border Unicode Definitions -- Double Lines
        const sstr double_top__left = "\u2554";
        const sstr double_top_split = "\u2566";
        const sstr double_top_right = "\u2557";

        const sstr double_H__spacer = "\u2550";
        const sstr double_V__spacer = "\u2551";
        const sstr double_New__Line = "\n";

        const sstr double_mid__left = "\u2560";
        const sstr double_mid_split = "\u256C";
        const sstr double_mid_right = "\u2563";

        const sstr double_bot__left = "\u255A";
        const sstr double_bot_split = "\u2569";
        const sstr double_bot_right = "\u255D";

        // Grid Border Unicode Definitions -- Heavy Lines
        const sstr heavy_top__left = "\u250F";
        const sstr heavy_top_split = "\u2533";
        const sstr heavy_top_right = "\u2513";

        const sstr heavy_H__spacer = "\u2501";
        const sstr heavy_V__spacer = "\u2503";
        const sstr heavy_New__Line = "\n";

        const sstr heavy_mid__left = "\u2523";
        const sstr heavy_mid_split = "\u254B";
        const sstr heavy_mid_right = "\u252B";

        const sstr heavy_bot__left = "\u2517";
        const sstr heavy_bot_split = "\u253B";
        const sstr heavy_bot_right = "\u251B";

        // Grid Box_Character indexes to retrieve box characters
        const usLong top__left =  0;
        const usLong top_split =  1;
        const usLong top_right =  2;

        const usLong horSpacer =  3; // horizontal spacer
        const usLong verSpacer =  4; // vertical   spacer
        const usLong nlnSpacer =  5; // new line

        const usLong mid__left =  6;
        const usLong mid_split =  7;
        const usLong mid_right =  8;

        const usLong bot__left =  9; // bot = bottom
        const usLong bot_split = 10; // bot = bottom
        const usLong bot_right = 11; // bot = bottom

        std::fstream m_file_stream;
        //static const bool   s_default_initializion = false;
        //static const usLong s_default_m_max_rows = std::numeric_limits<usLong>::max();
        //static const usLong s_default_m_curr_row = std::numeric_limits<usLong>::max();
        //static const auto   s_maxUL = std::numeric_limits<usLong>::max();
        //
        bool m_debug                    { false };
        bool m_valid                    { false } ;
        bool m_isEmpty                  { false };
        bool m_columnLock               { false };
        bool m_output_to_file           { false } ;
        bool m_file_stream_opened       { false } ;
        //

        DG_Row              mv_data_row;
        DG_Vector           mvv_data_grid_data;
        DataDictionary      mp_dd;
        DD_Column_Index     mv_dd_column_index     {  0 };
        DD_Column_MaxWidth  mv_dd_column_max_width { 25 };
        //
        sstr   m_post_text               { ""};
        sstr   m_pre_text                { ""};
        sstr   m_name                    { "Default DataGrid"};
        sstr   m_sql_insert_pretext      { ""};
        sstr   m_sql_table_name          { "Table Not Specified"};
        sstr   m_output_dir              { "./" };
        sstr   m_out_file_name           { "DataGrid_Output.txt" };
        //
        usLong m_curr_row                { 0 };
        usLong m_last_validated_row      { 0 };
        usLong m_max_rows                { 0 };
        usLong m_total_width             { 0 };
        usLong m_version                 { 0 };;
        //
        //void Show_Data(usLong index);
        sstr Generate_InsertColumnData(const DG_Row row, const usLong index, const bool add_comma)  noexcept;

        void Load_Dashes(DD_Box_Drawing& box_characters)  noexcept;
        void Load_Light(DD_Box_Drawing& box_characters)  noexcept;
        void Load_Double(DD_Box_Drawing& box_characters)  noexcept;
        void Load_Heavy(DD_Box_Drawing& box_characters)  noexcept;
        void Hspace(DD_Box_Drawing box_characters, usLong length)  noexcept;

        void Generate_SQL_InsertPreText()  noexcept;
        void Init()  noexcept;
        void Show_BlankLines(const int count)  noexcept;
        void Show_Top_DataGridEdge()  noexcept;
        void Show_Top_Row_Separator()  noexcept;
        void Show_Bottom_Row_Separator()  noexcept;
        void Show_AllData()  noexcept;
        void Show_Grid()  noexcept;
        void Show_Header()  noexcept;
        void Show_Post_Text()  noexcept;
        void Show_Pre_Text()  noexcept;
        void CreateFileStream()  noexcept;
        void Send_Output(const sstr& value)  noexcept;
        void Send_OutputCRLF(const sstr& value)  noexcept;

        //
    public:

        DataGrid(const sstr name, DataDictionary& dd) noexcept;
        virtual ~DataGrid()  noexcept;
        //
        sstr Get_Name()  noexcept;
        //
        void Add_Column(DataColumnHeader& dch)  noexcept;
        void Add_Row(const DG_Row row)  noexcept;
        void Add_DataToDataGrid(const DG_Row values)  noexcept;

        void Generate_InsertData()  noexcept;
        void Set_Border_Type(enum_border_type borderType) noexcept;
        void Set_OutputDirectory(const sstr value) noexcept;
        void Set_FileName(const sstr value) noexcept;
        void Reset_Columns() noexcept;
        void Reset_Data() noexcept;
        void Set_Debug() noexcept;
        void UnSet_Debug() noexcept;
        void Set_Post_Text(const sstr value) noexcept;
        void Set_Pre_Text(const  sstr value) noexcept;
        void Set_TableName(const  sstr value) noexcept;
        void Set_OutputToFile() noexcept;
        void UnSet_OutputToFile() noexcept;
        void Show() noexcept;
        void Show(const int blank_lines_before_pre,  const bool pre,  const int blank_lines_after_pre,
                  const int blank_lines_before_post, const bool post, const int blank_lines_after_post) noexcept;

        void SyncDataDictionaryVersion() noexcept;


        //void Update_NewRow(usLong Column, usLong Row, sstr Data);
        //void Update_OldRow(usLong Column, usLong Row, sstr Data);
    };

#endif //DATAGRID_TEST_001_DATAGRID_H
}