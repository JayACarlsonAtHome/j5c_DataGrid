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

#include "DataGrid.h"

namespace J5C_DSL_Code {

    //
    // Private
    //


    //
    // Public
    //

    DataGrid::DataGrid(const sstr name, DataDictionary& dd) noexcept {
        m_name = name;
        mp_dd = dd;
        Init();
    }

    void DataGrid::Init() noexcept {
        // max is max unsigned long is the same as -1
        Reset_Data();
        m_total_width = 0;
        m_pre_text = "";
        m_post_text = "";
        m_file_stream_opened = false;
        m_output_to_file = false;
        m_valid = false;
        m_isEmpty = true;
        if (mv_box_characters.size() < 1)
        {
            Set_Border_Type(m_border_type);
        }
    }

    void DataGrid::Add_Column(DataColumnHeader& dch) noexcept {

        if (m_columnLock)
        {
            Reset_Data();
        }
        m_isEmpty = false;
        const auto index = mp_dd.Add(dch);
        mv_dd_column_index.push_back(index);
        mv_dd_column_max_width.push_back(0);
        if (index < 1) {
            m_total_width += mp_dd.Get_DataColumnHeader(dch, index).Get_DisplayWidth();
        } else {
            m_total_width += mp_dd.Get_DataColumnHeader(dch, index).Get_DisplayWidth() + 1;
        }
    }

    void DataGrid::Reset_Data() noexcept {
        m_max_rows = 0;
        m_curr_row = 0;
        m_last_validated_row = 0;
        m_columnLock = false;
        mvv_data_grid_data.clear();
        mv_data_row.clear();
        mv_dd_column_max_width.clear();
        m_version = mp_dd.Get_Version();
    }

    void DataGrid::Reset_Columns() noexcept {
        Reset_Data();
        mv_dd_column_index.clear();
        mv_data_row.clear();
        Init();
    }


    void DataGrid::Add_Row(const DG_Row row) noexcept {
        m_columnLock = true;
        mv_data_row = row;
        mvv_data_grid_data.push_back(mv_data_row);
        mv_data_row.clear();
        m_curr_row = mvv_data_grid_data.size() - 1;
    }

    void DataGrid::Add_DataToDataGrid(const DG_Row values) noexcept
    {
        const auto size  = mv_dd_column_index.size();
        std::string safe_value = "";

        DG_Row dg_row_temp;
        if (size == values.size()) {

            for (auto i = 0UL; i < values.size(); i++)
            {
                auto max_width = mp_dd.Get_ColumnWidthSize(mv_dd_column_index[i]);
                safe_value = values[i];
                if (mv_dd_column_max_width[i] < safe_value.length())
                {
                    mv_dd_column_max_width[i] = safe_value.length();
                    if (mv_dd_column_max_width[i] > max_width)
                    {
                        mv_dd_column_max_width[i] = max_width;
                        safe_value = safe_value.substr(0,max_width);
                    }
                }
                dg_row_temp.push_back(safe_value);
            }
            mvv_data_grid_data.push_back(dg_row_temp);

        } else
        {
            std::cout << "Warning!!!  Attempting to add data to datagrid but the number of columns" << std::endl;
            std::cout << "            Does not match the number of data values submitted." << std::endl;
        }
    }


    void DataGrid::Set_TableName(const  sstr value) noexcept
    {
        m_sql_table_name = value;
    }

    void DataGrid::Generate_SQL_InsertPreText() noexcept
    {
        m_sql_insert_pretext = "Insert Into ";
        m_sql_insert_pretext.append(m_sql_table_name);
        m_sql_insert_pretext.append(" ( ");
    }

    sstr DataGrid::Generate_InsertColumnData(const DG_Row row, const usLong index, const bool add_comma) noexcept
    {
        sstr value = "";
        if (mp_dd.Get_SQL_Quotes(index))
        {
            value.append("'");
            value.append(row[index]);
            value.append("'");
        } else
        {
            value.append(row[index]);
        }
        if (add_comma)
        {
            value.append(", ");
        } else
        {
            value.append(" ");
        }
        return value;
    }

    void DataGrid::Generate_InsertData() noexcept
    {
        Generate_SQL_InsertPreText();
        DG_Row row;
        sstr   value;
        sstr   pre_value;
        sstr   post_value;
        sstr   column_name;
        sstr   column_value;
        sstr   display_value;

        const auto size1 = mvv_data_grid_data.size();
        const auto sizex = mv_dd_column_index.size();

        if (size1 > 0)
        {
            for (auto index1 = 0UL; index1 < size1; index1++)
            {
                pre_value.clear();
                pre_value.append(m_sql_insert_pretext);
                post_value.clear();
                post_value.append(" ) values ( ");
                row = mvv_data_grid_data[index1];
                auto size2 = row.size();
                if ((size2 > 0) && (size2 == sizex))
                {
                    usLong LastOne = size2 - 1;
                    bool add_comma = true;
                    bool no_comma  = false;
                    for (auto index2 = 0UL; index2 < LastOne; index2++)
                    {
                        column_name = mp_dd.Get_HeaderName(index2);
                        column_name.append(", ");
                        pre_value.append(column_name);
                        column_value = Generate_InsertColumnData(row, index2, add_comma);
                        post_value.append(column_value);
                    }
                    column_name = mp_dd.Get_HeaderName(LastOne);
                    pre_value.append(column_name);
                    column_value = Generate_InsertColumnData(row, LastOne, no_comma);
                    post_value.append(column_value);
                }
            post_value.append(" ); ");
            display_value.clear();
            display_value.append(pre_value);
            display_value.append(post_value);
            std::cout << display_value << std::endl;
            }
        }
        std::cout << std::endl;
    }


    void DataGrid::Set_OutputDirectory(const sstr value) noexcept
    {
        // some sort of validation would be helpful here...
        m_output_dir = value;
    }

    void DataGrid::Set_FileName(const sstr value) noexcept
    {
        // some sort of validation would be helpful here...
        m_out_file_name = value;
    }

    void DataGrid::Set_OutputToFile() noexcept
    {
        m_output_to_file = true;
    }

    void DataGrid::UnSet_OutputToFile() noexcept
    {
        m_output_to_file = false;
    }

    void DataGrid::Set_Border_Type(enum_border_type borderType) noexcept
    {
        m_border_type = borderType;
        switch (m_border_type)
        {
            case enum_border_type::unknown :
                this->Load_Light(mv_box_characters);
                break;
            case enum_border_type::dashes :
                this->Load_Dashes(mv_box_characters);
                break;
            case enum_border_type::light :
                this->Load_Light(mv_box_characters);
                break;
            case enum_border_type::double_line :
                this->Load_Double(mv_box_characters);
                break;
            case enum_border_type::heavy :
                this->Load_Heavy(mv_box_characters);
                break;
        }
    }

    void DataGrid::Load_Dashes(DD_Box_Drawing &box_characters) noexcept {
        box_characters.clear();
        box_characters.reserve(12);

        box_characters.push_back(dashes_top__left);
        box_characters.push_back(dashes_top_split);
        box_characters.push_back(dashes_top_right);

        box_characters.push_back(dashes_H__spacer);
        box_characters.push_back(dashes_V__spacer);
        box_characters.push_back(dashes_New__Line);

        box_characters.push_back(dashes_mid__left);
        box_characters.push_back(dashes_mid_split);
        box_characters.push_back(dashes_mid_right);

        box_characters.push_back(dashes_bot__left);
        box_characters.push_back(dashes_bot_split);
        box_characters.push_back(dashes_bot_right);
    }
    void DataGrid::Load_Light(DD_Box_Drawing& box_characters) noexcept
    {
        box_characters.clear();
        box_characters.reserve(12);

        box_characters.push_back(light_top__left);
        box_characters.push_back(light_top_split);
        box_characters.push_back(light_top_right);

        box_characters.push_back(light_H__spacer);
        box_characters.push_back(light_V__spacer);
        box_characters.push_back(light_New__Line);

        box_characters.push_back(light_mid__left);
        box_characters.push_back(light_mid_split);
        box_characters.push_back(light_mid_right);

        box_characters.push_back(light_bot__left);
        box_characters.push_back(light_bot_split);
        box_characters.push_back(light_bot_right);
    }

    void DataGrid::Load_Double(DD_Box_Drawing& box_characters) noexcept
    {
        box_characters.clear();
        box_characters.reserve(12);

        box_characters.push_back(double_top__left);
        box_characters.push_back(double_top_split);
        box_characters.push_back(double_top_right);

        box_characters.push_back(double_H__spacer);
        box_characters.push_back(double_V__spacer);
        box_characters.push_back(double_New__Line);

        box_characters.push_back(double_mid__left);
        box_characters.push_back(double_mid_split);
        box_characters.push_back(double_mid_right);

        box_characters.push_back(double_bot__left);
        box_characters.push_back(double_bot_split);
        box_characters.push_back(double_bot_right);
    }

    void DataGrid::Load_Heavy(DD_Box_Drawing& box_characters) noexcept
    {
        box_characters.clear();
        box_characters.reserve(12);

        box_characters.push_back(heavy_top__left);
        box_characters.push_back(heavy_top_split);
        box_characters.push_back(heavy_top_right);

        box_characters.push_back(heavy_H__spacer);
        box_characters.push_back(heavy_V__spacer);
        box_characters.push_back(heavy_New__Line);

        box_characters.push_back(heavy_mid__left);
        box_characters.push_back(heavy_mid_split);
        box_characters.push_back(heavy_mid_right);

        box_characters.push_back(heavy_bot__left);
        box_characters.push_back(heavy_bot_split);
        box_characters.push_back(heavy_bot_right);
    }

    void DataGrid::Hspace(std::vector<std::string> box_characters, usLong length) noexcept
    {
        for (unsigned long i = 0; i < length; ++i)
        {
            std::cout << box_characters[horSpacer];
        }
    }

    void DataGrid::Show_Top_DataGridEdge() noexcept {
        DG_Row row = mvv_data_grid_data[0];
        auto size = row.size();
        usLong  count = 0;
        sstr display_value = "";
        display_value.append(mv_box_characters[top__left]);
        for (auto index2 = 0UL; index2 < size-1; index2++)
        {
            count = mp_dd.Get_ColumnWidthSize(index2);
            for (usLong i = 0; i < count; i++) {
                display_value.append(mv_box_characters[horSpacer]);
            }
            display_value.append(mv_box_characters[top_split]);
        }
        count = mp_dd.Get_ColumnWidthSize(size-1);
        for (usLong i = 0; i < count; i++) {
            display_value.append(mv_box_characters[horSpacer]);
        }
        display_value.append(mv_box_characters[top_right]);
        Send_Output(display_value);
        Send_OutputCRLF("");
    }

    void DataGrid::Show_Top_Row_Separator() noexcept {
        DG_Row row = mvv_data_grid_data[0];
        auto size = row.size();
        usLong  count = 0;
        sstr display_value = "";
        display_value.append(mv_box_characters[mid__left]);
        for (auto index2 = 0UL; index2 < size-1; index2++)
        {
            count = mp_dd.Get_ColumnWidthSize(index2);
            for (usLong i = 0; i < count; i++) {
                display_value.append(mv_box_characters[horSpacer]);
            }
            display_value.append(mv_box_characters[mid_split]);
        }
        count = mp_dd.Get_ColumnWidthSize(size-1);
        for (usLong i = 0; i < count; i++) {
            display_value.append(mv_box_characters[horSpacer]);
        }
        display_value.append(mv_box_characters[mid_right]);
        Send_Output(display_value);
        Send_OutputCRLF("");
    }

    void DataGrid::Show_Bottom_Row_Separator() noexcept {
        DG_Row row = mvv_data_grid_data[0];
        auto size = row.size();
        usLong  count = 0;
        sstr display_value = "";
        display_value.append(mv_box_characters[bot__left]);
        for (auto index2 = 0UL; index2 < size-1; index2++)
        {
            count = mp_dd.Get_ColumnWidthSize(index2);
            for (usLong i = 0; i < count; i++) {
                display_value.append(mv_box_characters[horSpacer]);
            }
            display_value.append(mv_box_characters[bot_split]);
        }
        count = mp_dd.Get_ColumnWidthSize(size-1);
        for (usLong i = 0; i < count; i++) {
            display_value.append(mv_box_characters[horSpacer]);
        }
        display_value.append(mv_box_characters[bot_right]);
        Send_Output(display_value);
        Send_OutputCRLF("");
    }

    void DataGrid::Show_Header() noexcept
    {
        const auto max = mv_dd_column_index.size();
        std::string temp;
        std::string display_header;

        // print column headers
        for (unsigned int i = 0; i < max; i++) {
            display_header.append(mv_box_characters[verSpacer]);
            temp = mp_dd.Get_HeaderNameWithPadding(mv_dd_column_index.at(i));
            display_header.append(temp);
        }
        display_header.append(mv_box_characters[verSpacer]);
        Send_OutputCRLF(display_header);
        Show_Top_Row_Separator();
    }

    void DataGrid::Show_Grid() noexcept {

        if (!m_isEmpty) {
            Show_Top_DataGridEdge();
            Show_Header();
            //Show_DataGridEdge();
            Show_AllData();
            Show_Bottom_Row_Separator();
        }
    }

    void DataGrid::Show_BlankLines(const int count) noexcept
    {
        for(int i = 0; i < count; i++)
        {
            std::cout << std::endl;
            Send_OutputCRLF("");
        }
    }

    void DataGrid::Show(const int blank_lines_before_pre,
                        const bool pre,
                        const int blank_lines_after_pre,
                        const int blank_lines_before_post,
                        const bool post,
                        const int blank_lines_after_post
                        )  noexcept {

        Show_BlankLines(blank_lines_before_pre);
        if (pre) Show_Pre_Text();
        Show_BlankLines(blank_lines_after_pre);
        Show_Grid();
        Show_BlankLines(blank_lines_before_post);
        if (post) Show_Post_Text();
        Show_BlankLines(blank_lines_after_post);
    }

    void DataGrid::CreateFileStream() noexcept
    {
        usLong size = m_output_dir.length();
        sstr temp;
        sstr full_filename;
        if (size > 0)
        {
            if (m_output_dir[size - 1] != '/')
            {
                full_filename.append(m_output_dir);
                full_filename.append("/");
                full_filename.append(m_out_file_name);
            }
            else
            {
                if (m_out_file_name.find(".txt") == 0)
                {
                    m_out_file_name.append(".txt");
                }
                full_filename.append(m_output_dir);
                full_filename.append("/");
                full_filename.append(m_out_file_name);

            }
        } else
        {
            m_output_dir = "./";
            m_out_file_name = "dataGrid_";
            m_out_file_name.append(m_name);
            m_out_file_name.append(".txt");
            full_filename.append(m_out_file_name);
        }

        std::replace(full_filename.begin(), full_filename.end(), ' ', '_');

        if(!m_file_stream_opened)
        {
            m_file_stream.open(full_filename, std::ios_base::out|std::ios_base::trunc);
        }

        if(m_file_stream.is_open())
        {
            m_file_stream_opened = true;
            std::cout << "full_filename = " << full_filename << std::endl;
            if (!m_file_stream.is_open())
            {
                std::cout << " Tried but unable to open file at " << full_filename << std::endl;
            } else
            {
                std::cout << " Output file is opened " << full_filename << std::endl;
            }
        }
    }

    void DataGrid::Show() noexcept
    {
        if (m_output_to_file)
        {
            CreateFileStream();
        }
        Show(1, true, 0, 0, true, 1);
    }

    DataGrid::~DataGrid() noexcept
    {
        if (m_debug) {
            std::cout << "Calling DataGrid Destructor" << std::endl;
        }
        if (m_file_stream.is_open()) {
            if (m_debug) {
                std::cout << "Closing file stream." << std::endl;
            }
            m_file_stream.flush();
            m_file_stream.close();
        }
        mv_data_row.clear();
        mvv_data_grid_data.clear();
        mv_dd_column_index.clear();
        mv_dd_column_max_width.clear();
    }

    void DataGrid::Show_AllData() noexcept {

        DG_Row row;
        sstr   temp;
        sstr   value;
        sstr   display_value;
        const auto size1 = mvv_data_grid_data.size();
        const auto sizex = mv_dd_column_index.size();
        usLong  count = 0;
        if (size1 > 0) {
            for (auto index1 = 0UL; index1 < size1; index1++) {
                row = mvv_data_grid_data[index1];
                auto size2 = row.size();
                if ((size2 > 0) && (size2 == sizex))
                {
                    // Get and Output Data
                    display_value.clear();
                    for (auto index2 = 0UL; index2 < size2; index2++)
                    {
                        value = row[index2];
                        temp = mp_dd.Get_ValueWithPadding(index2, value, mv_dd_column_max_width[index2]);
                        display_value.append(mv_box_characters[verSpacer]);
                        display_value.append(temp);
                    }
                    Send_Output(display_value);
                    Send_OutputCRLF(mv_box_characters[verSpacer]);
                    // Create and Output Row_Separator
                    if (index1 < (size1 - 1)) {
                        display_value.clear();
                        display_value.append(mv_box_characters[mid__left]);
                        for (auto index2 = 0UL; index2 < size2 - 1; index2++) {
                            count = mp_dd.Get_ColumnWidthSize(index2);
                            for (usLong i = 0; i < count; i++) {
                                display_value.append(mv_box_characters[horSpacer]);
                            }
                            display_value.append(mv_box_characters[mid_split]);
                        }
                        count = mp_dd.Get_ColumnWidthSize(size2 - 1);
                        for (usLong i = 0; i < count; i++) {
                            display_value.append(mv_box_characters[horSpacer]);
                        }
                        display_value.append(mv_box_characters[mid_right]);
                        Send_Output(display_value);
                        Send_OutputCRLF("");
                    }
                }
            }
        }
    }

    void DataGrid::Show_Pre_Text() noexcept {
        Send_OutputCRLF(m_pre_text);
    }

    void DataGrid::Show_Post_Text() noexcept {
        Send_OutputCRLF(m_post_text);
    }

    //void Update_OldRow(unsigned long Column, unsigned long Row, std::string Data) { }

    void DataGrid::Set_Pre_Text(const std::string value) noexcept {
        m_pre_text = value;
    }

    void DataGrid::Set_Post_Text(const std::string value) noexcept{
        m_post_text = value;
    }

    sstr DataGrid::Get_Name() noexcept{
        return m_name;
    }

    void DataGrid::Send_Output(const sstr& value) noexcept
    {
        if ((m_output_to_file) && (m_file_stream_opened))
        {
            if (m_file_stream.is_open()) {
                m_file_stream << value;
            }
            else
            {
                std::cout << "File stream is not open" << std::endl;
            }
        }
        else {
            std::cout << value;
        }
    }
    void DataGrid::Send_OutputCRLF(const sstr& value) noexcept
    {
        if ((m_output_to_file) && (m_file_stream_opened))
        {
            Send_Output(value);
            if (m_file_stream.is_open())
            {
                m_file_stream << std::endl;
                m_file_stream.flush();

            }
            std::cout << std::endl;

        } else
        {
            std::cout << value << std::endl;
        }
    }
    void DataGrid::SyncDataDictionaryVersion() noexcept
    {
        m_version =  mp_dd.Get_Version();
    }

    void DataGrid::Set_Debug() noexcept
    {
        m_debug = true;
    }

    void DataGrid::UnSet_Debug() noexcept {
        m_debug = false;
    }

}
