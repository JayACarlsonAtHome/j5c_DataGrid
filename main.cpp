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
//
// This file runs tests, but also demonstrates how various components can be used.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

#include "source/DataGrid.h"

using namespace J5C_DSL_Code;

using epadDir = enum_pad_direction;
using usInt   = unsigned int;
using sstr    = std::string;
using usLong  = unsigned long;


enum class enum_test_result {
    ptrNull = 0, failed = 1, good = 2
};

//
// testing structure starts here
//
void horizontal_line() {
    std::cout << "-------------------------------------------" << std::endl;
}

void show_total_results(unsigned int results[]) {
    std::cout << "  Test Result Count of Type ptrNull : " << std::setfill('0') << std::setw(4)
              << results[static_cast<int>(enum_test_result::ptrNull)] << std::endl;
    std::cout << "  Test Result Count of Type Error   : " << std::setfill('0') << std::setw(4)
              << results[static_cast<int>(enum_test_result::failed)] << std::endl;
    std::cout << "  Test Result Count of Type Good    : " << std::setfill('0') << std::setw(4)
              << results[static_cast<int>(enum_test_result::good)] << std::endl;
    std::cout << std::endl;
}

void show_test_and_results(unsigned int test_number, std::string& test_name, unsigned int results[],
                           enum_test_result test_result) {

    std::cout << std::endl;
    results[static_cast<int>(test_result)] += 1;
    std::cout << "Test Number: ";
    std::cout << std::setfill('0') << std::setw(4) << test_number;
    std::cout << "  Test: " << test_name << std::endl;
    show_total_results(results);
    horizontal_line();
    std::cout << std::endl;

}
//
// end of testing structure
//


//
// specific test helping functions
//

enum_test_result validate_column(DataColumnHeader& dch,
        const bool debug,
        const bool multi_line_output,
        const bool sql_quote,
        const epadDir pad_direction,
        const sstr& column_header,
        const sstr& column_description_long,
        const sstr& column_description_short,
        const sstr& left_fill_char,
        const usInt display_width,
        const usInt precision)
{

    enum_test_result result = enum_test_result ::ptrNull;

    std::string tempString1 = "";
    std::string tempString2 = "";

    bool test01 = false;
    bool test02 = false;
    bool test03 = false;
    bool test04 = false;
    bool test05 = false;
    bool test06 = false;
    bool test07 = false;
    bool test08 = false;
    bool test09 = false;
    bool test10 = false;
    tempString1 = dch.Get_Address_as_String();

    if (tempString1 != "0") {
        if (dch.Get_Debug()                 == debug)                       test01 = true;
        if (dch.Get_Multi_Line_Enabled()    == multi_line_output)           test02 = true;
        if (dch.Get_SQL_Quote()             == sql_quote)                   test03 = true;
        if (dch.Get_Pad_Direction()         == pad_direction)               test04 = true;

        tempString1 = dch.Get_ColumnHeader();
        if (tempString1 == column_header)                                   test05 = true;

        tempString1 = dch.Get_ColumnDescriptionLong();
        if (tempString1 == column_description_long)                         test06 = true;

        tempString1 = column_description_short.substr(0, display_width);
        tempString2 = dch.Get_ColumnDescriptionShort().substr(0, display_width);

        if (tempString1 == tempString2)                                     test07 = true;
        if (dch.Get_LeftFillCharacter()     == left_fill_char)              test08 = true;
        if (dch.Get_DisplayWidth()          == display_width)               test09 = true;
        if (dch.Get_Precision()             == precision)                   test10 = true;

        if (test01 && test02 && test03 && test04 && test05
                   && test06 && test07 && test08 && test09 && test10)
        {
            result = enum_test_result::good;
        }
        else
        {
            result = enum_test_result::failed;
            std::cout << "!!! Warning --  Test Failed" << std::endl;
        }
    } else
    {
        result = enum_test_result::ptrNull;
        std::cout << "!!! Warning --  " << std::endl;
        std::cout << "!!! Warning -- DataColumnHeader* dch == ptrNull" << std::endl;
        std::cout << "!!! Warning --  " << std::endl;
    }
    return result;
}

std::string generate_test_name(bool make,
                               std::string& pre_text,
                               std::string& post_text,
                               std::unique_ptr<DataColumnHeader>& dch) {
    std::string test_name;
    if (pre_text.length() > 0) {
        test_name.append(pre_text);
        test_name.append(" ");
    }
    if (make) {
        test_name.append(" Make new DataColumnHeader(");
    } else {
        test_name.append(" Initialize DataColumnHeader(");
    }
    std::string str_width = std::to_string(dch->Get_DisplayWidth());
    std::string str_precision = std::to_string(dch->Get_Precision());
    std::string str_multi_line_enabled = "false, ";
    if (dch->Get_Multi_Line_Enabled()) {
        str_multi_line_enabled = "true, ";
    }

    test_name.append(str_width);
    test_name.append(", ");
    test_name.append(str_precision);
    test_name.append(", ");
    test_name.append(str_multi_line_enabled);
    switch (dch->Get_Pad_Direction()) {
        case enum_pad_direction::left :
            test_name.append("left, ");
            break;
        case enum_pad_direction::right :
            test_name.append("right, ");
            break;
        case enum_pad_direction::both :
            test_name.append("both, ");
            break;
        case enum_pad_direction::decimal :
            test_name.append("decimal, ");
            break;
        case enum_pad_direction::unknown :
            test_name.append("unknown, ");
            break;
    }

    test_name.append("\"");
    test_name.append(dch->Get_LeftFillCharacter());
    test_name.append("\", \"");
    test_name.append(dch->Get_ColumnHeader());
    test_name.append("\", \"");
    test_name.append(dch->Get_ColumnDescriptionShort());
    test_name.append("\", \"");
    test_name.append(dch->Get_ColumnDescriptionLong());
    test_name.append("\"");
    test_name.append(") ");
    if (post_text.length() > 0) {
        test_name.append(" ");
        test_name.append(post_text);
    }
    return test_name;

}

enum_test_result validate_indexes_match(unsigned long index1, DataDictionary &dd, std::string& column_name) {

    enum_test_result result = enum_test_result ::failed;

    auto index2 = dd.Get_DataColumnIndex(column_name);
    std::cout << "index1: " << index1 << "   Index2: " << index2 << std::endl;
    if (index1 == index2) {
        result = enum_test_result::good;
        std::cout << "Test index1 == index2" << std::endl;

    }
    return result;
}

//
// end of test helping functions
//

//
// test sets
//




int test_001() {
    horizontal_line();
    std::cout << std::endl;
    std::cout << "Testing DataColumnHeader Class:" << std::endl;
    std::cout << std::endl;



    // initialize variables
    unsigned int results[3] = {0, 0, 0};
    unsigned int test_number = 0;
    enum_test_result result;
    DataColumnHeader dch1{};

    bool debug = false;
    bool multi_line_output = false;
    bool sql_quote = false;
    epadDir pad_direction = enum_pad_direction::right;
    std::string column_header            = "Default Header Name";
    std::string column_description_short = "Default Header Short Description";
    std::string column_description_long  = "Default Header Long  Description";
    std::string left_fill_char = " ";
    usInt display_width = 25;
    usInt precision = 8;

    test_number++; // 1
    dch1.Show_Data_Header();
    std::string test_name = "Make Default DataColumnHeader";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                                column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 2
    debug = true;
    dch1.Set_Debug();
    dch1.Show_Data_Header();
    test_name = "Test Set Debug";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 3
    debug = false;
    dch1.UnSet_Debug();
    dch1.Show_Data_Header();
    test_name = "Test UnSet Debug";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 4
    multi_line_output = true;
    dch1.Set_MultiLineOutput(multi_line_output);
    dch1.Show_Data_Header();
    test_name = "Test multi_line_output switch to true";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 5
    sql_quote = true;
    dch1.Set_SQL_Quote(sql_quote);
    dch1.Show_Data_Header();
    test_name = "Test sql_quote switch to true";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 6
    pad_direction = enum_pad_direction ::left;
    dch1.Set_Pad_Direction(pad_direction);
    dch1.Show_Data_Header();
    test_name = "Test set pad_direction to left";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 7
    column_header = "Testing Header Name";
    dch1.Set_ColumnHeader(column_header);
    dch1.Show_Data_Header();
    test_name = "Test set header name";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 8
    column_description_long = "Testing Header Long  Description";
    dch1.Set_ColumnDescriptionLong(column_description_long);
    dch1.Show_Data_Header();
    test_name = "Test set long description";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 9
    column_description_short = "Testing Header Short Description";
    dch1.Set_ColumnDescriptionShort(column_description_short);
    dch1.Show_Data_Header();
    test_name = "Test set long description";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 10
    left_fill_char = "#";
    dch1.Set_LeftFillCharacter(left_fill_char);
    dch1.Show_Data_Header();
    test_name = "Test set left fill character";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 11
    display_width = 30;
    // we have to make the short description longer again for the test to work
    dch1.Set_DisplayWidth(display_width);
    column_description_short = "Testing Header Short Description";
    dch1.Set_ColumnDescriptionShort(column_description_short);

    dch1.Show_Data_Header();
    test_name = "Test set display width";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);


    test_number++; // 12
    precision = 5;
    // we have to make the short description longer again for the test to work
    dch1.Set_Precision(precision);
    dch1.Show_Data_Header();
    test_name = "Test set precision";
    result = validate_column(dch1, debug, multi_line_output, sql_quote, pad_direction, column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);
    show_test_and_results(test_number, test_name, results, result);

/*
 *
  column_header, column_description_long,
                             column_description_short, left_fill_char, display_width, precision);

 *
nabled, padding, left_fill_char, column_header, description_short, description_long);
    dch1->Show_Data_Header();
    test_name = "Set_ColumnHeader(column_header) : (\"" + column_header + "\")";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 3
    description_short = "Description Test Header 1 Short";
    dch1->Set_ColumnDescriptionShort(description_short);
    result = validate_column(dch1, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch1->Show_Data_Header();
    test_name = "dch1->Set_ColumnDescriptionShort(description_short) : (\"" + description_short + "\")";
    show_test_and_results(test_number, test_name, results, result);


    test_number++; // 4
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 25;
    precision = 5;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(column_header, description_short, description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    test_name = "Make new(std::nothrow) DataColumnHeader(\"" + column_header + "\", \"" + description_short + "\"" + ", \"" +
                description_long + "\")";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 5
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 5;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, column_header, description_short, description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    test_name =
            "Make new(std::nothrow) DataColumnHeader(" + std::to_string(width) + ", \"" + column_header + "\", \"" + description_short +
            "\"" + ", \"" + description_long + "\")";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 6
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, column_header, description_short, description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    test_name = "Make new(std::nothrow) DataColumnHeader(" + std::to_string(width) + ", " + std::to_string(precision) + ", \"" +
                column_header + "\", \"" + description_short + "\"" + ", \"" + description_long + "\")";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 7
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    test_name =
            "Make new(std::nothrow) DataColumnHeader(" + std::to_string(width) + ", " + std::to_string(precision) + ",  true, \"" +
            column_header + "\", \"" + description_short + "\"" + ", \"" + description_long + "\")";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 8
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 14;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    std::string pre_text = "";
    std::string post_text = "";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 9
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 14;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    pre_text = "";
    post_text = "";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 10
    std::cout << dch->Get_ColumnHeader() << ":  ";
    dch->Display_Address();
    std::cout << std::endl;
    if (dch->Get_Address() != nullptr) {
        result = enum_test_result::good;
    } else {
        result = enum_test_result::unknown;
    }
    test_name = "Show Address ";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 11
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 34;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short, description_long);
    dch->Set_Debug();
    std::string column_name1 = "This is a new(std::nothrow) header";
    pre_text = "";
    post_text = "Then Set ColumnHeader = " + column_name1;
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_ColumnHeader(column_name1);
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_name1, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 12
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short, description_long);
    dch->Set_Debug();
    validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    unsigned int width1 = 14;
    pre_text = "";
    post_text = "Then Set width = " + std::to_string(width1);
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_DisplayWidth(width1);
    validate_column(dch, width1, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 13
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    std::string description_long1 = "new(std::nothrow) -- Description Test Header 1 Long";
    pre_text = "";
    post_text = "Then Set description_long = " + description_long1;
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_ColumnDescriptionLong(description_long1);
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long1);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 14
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short, description_long);
    dch->Set_Debug();
    bool multi_line_output1 = true;
    pre_text = "";
    post_text = "Then Set multi line output = true ";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_MultiLineOutput(multi_line_output1);
    result = validate_column(dch, width, precision, multi_line_output1, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 15
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = true;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    multi_line_output1 = false;
    pre_text = "";
    post_text = "Then Set multi line output = false ";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_MultiLineOutput(multi_line_output1);
    result = validate_column(dch, width, precision, multi_line_output1, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 16
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    unsigned int precision1 = 17;
    pre_text = "";
    post_text = "Then Set precision = " + std::to_string(precision1);
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_Precision(precision1);
    result = validate_column(dch, width, precision1, multi_line_enabled, padding, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 17
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::left;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    enum_pad_direction pad_direction1 = enum_pad_direction::right;
    pre_text = "";
    post_text = "Then Set pad direction = right";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_Pad_Direction(pad_direction1);
    result = validate_column(dch, width, precision, multi_line_enabled, pad_direction1, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 18
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    pad_direction1 = enum_pad_direction::left;
    pre_text = "";
    post_text = "Then Set pad direction = left";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_Pad_Direction(pad_direction1);
    result = validate_column(dch, width, precision, multi_line_enabled, pad_direction1, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 19
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    pad_direction1 = enum_pad_direction::both;
    pre_text = "";
    post_text = "Then Set pad direction = both";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_Pad_Direction(pad_direction1);
    result = validate_column(dch, width, precision, multi_line_enabled, pad_direction1, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 20
    column_header = "Test Header 1";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::both;
    delete dch;
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_header, description_short,
                               description_long);
    dch->Set_Debug();
    pad_direction1 = enum_pad_direction::unknown;
    pre_text = "";
    post_text = "Then Set pad direction = unknown";
    test_name = generate_test_name(true, pre_text, post_text, *dch);
    dch->Set_Pad_Direction(pad_direction1);
    result = validate_column(dch, width, precision, multi_line_enabled, pad_direction1, left_fill_char, column_header, description_short, description_long);
    dch->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    std::string column_name2;

    test_number++; // 21
    column_name1 = "Test Header 1";
    column_name2 = "Test Header 2";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::both;
    delete dch;
    DataColumnHeader *dch1 = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name1,
                                                  description_short, description_long);
    dch1->Set_Debug();
    DataColumnHeader *dch2 = new(std::nothrow) DataColumnHeader(*dch1);
    dch2->Set_Debug();
    dch2->Set_ColumnHeader(column_name2);
    test_name = "Make new(std::nothrow) DataColumnHeader, Make copy of new(std::nothrow) DataColumnHeader, dch2->Set_ColumnHeader(\"Test Header 2\") and ensure the addresses are different ";
    enum_test_result test1 = validate_column(dch1, width, precision, multi_line_enabled, padding, left_fill_char, column_name1,
                                             description_short, description_long);
    enum_test_result test2 = validate_column(dch2, width, precision, multi_line_enabled, padding, left_fill_char, column_name2,
                                             description_short, description_long);
    bool test3 = (dch1 != dch2);
    if ((test1 == enum_test_result::good)
        && (test2 == enum_test_result::good)
        && (test3)) {
        result = enum_test_result::good;
    } else {
        result = enum_test_result::unknown;
    }
    dch1->Show_Data_Header();
    dch2->Show_Data_Header();
    dch1->Display_Address();
    dch2->Display_Address();
    show_test_and_results(test_number, test_name, results, result);


    test_number++; // 22
    column_name1 = "Test Header 1";
    column_name2 = "Test Header 2";
    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::both;
    delete dch1;
    delete dch2;
    dch1 = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name1, description_short,
                                description_long);
    dch1->Set_Debug();
    dch2 = dch1;
    dch2->Set_ColumnHeader(column_name2);
    test_name = "Make new(std::nothrow) data column header, assignment to data column Header, change name, and ensure the addresses are the same";
    test1 = validate_column(dch2, width, precision, multi_line_enabled, padding, left_fill_char, column_name2, description_short,
                            description_long);
    if (test1 == enum_test_result::good) {
        result = enum_test_result::good;
    } else {
        result = enum_test_result::unknown;
    }
    dch1->Show_Data_Header();
    dch2->Show_Data_Header();
    dch1->Display_Address();
    dch2->Display_Address();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 23
    column_name1 = "Test Header 1";
    column_name2 = "Test Header 2";

    description_short = "Description Test Header 1 Short";
    description_long  = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::both;
    delete dch1;
    // there is no dch2 at this time to free, if you make one you will get a really bad error message.
    dch1 = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name1, description_short,
                                description_long);
    dch1->Set_Debug();
    dch2 = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name2, description_short,
                                description_long);
    dch2->Set_Debug();
    std::cout << "Before Copy" << std::endl;
    dch1->Show_Data_Header();
    dch2->Show_Data_Header();
    dch2->Copy_Values(dch2, dch1);
    test_name = "Make new(std::nothrow) DataColumnHeader dch1, Make new(std::nothrow) DataColumnHeader dch2, Copy Values from dch1 to dch2, and ensure the addresses are different";
    test1 = validate_column(dch1, width, precision, multi_line_enabled, padding, left_fill_char, column_name1, description_short,
                            description_long);
    validate_column(dch2, width, precision, multi_line_enabled, padding, left_fill_char, column_name2, description_short,
                            description_long);
    if (test1 == enum_test_result::good) {
        result = enum_test_result::good;
    } else {
        result = enum_test_result::unknown;
    }
    std::cout << "After Copy" << std::endl;
    dch1->Show_Data_Header();
    dch2->Show_Data_Header();
    dch1->Display_Address();
    dch2->Display_Address();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // 24
    column_name1 = "Test Header 1";
    column_name2 = "Test Header 2";

    description_short = "Description Test Header 1 Short";
    description_long = "Description Test Header 1 Long";
    width = 45;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::both;
    delete dch1;
    delete dch2;
    dch1 = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name1, description_short,
                                description_long);
    dch1->Set_Debug();
    DataColumnHeader **p_dch1 = &dch1;
    test_name = "Make new(std::nothrow) DataColumnHeader dch1, Make pointer to dch1, ensure the addresses are same";
    validate_column(dch1, width, precision, multi_line_enabled, padding, left_fill_char, column_name1, description_short,
                            description_long);
    validate_column(dch2, width, precision, multi_line_enabled, padding, left_fill_char, column_name2, description_short,
                            description_long);
    dch1 = *p_dch1;
    dch1->Show_Data_Header();
    (*p_dch1)->Show_Data_Header();
    dch1->Display_Address();
    (*p_dch1)->Display_Address();
    show_test_and_results(test_number, test_name, results, result);

    delete dch1;
*/
    std::cout << "Testing DataColumnHeader Class Summary:" << std::endl;
    show_total_results(results);

    horizontal_line();


    return 0;
}

/*
int test_002()
{
    horizontal_line();
    std::cout << std::endl;
    std::cout << "Testing DataColumnHeader Class: Test Set 002" << std::endl;
    std::cout << std::endl;

    // initialize variables
    unsigned int results[3] = {0, 0, 0};
    unsigned int test_number = 0;
    auto max_number_of_tests = 1001UL;
    enum_test_result result;

    std::string default_name = "Column Name ";
    std::string column_name  = "";
    std::string column_pad   = "00000";
    std::string index_temp   = "";
    std::string index        = "";
    if (max_number_of_tests < 10)
    {
        max_number_of_tests = 10;
    }
    std::string max_tests   = std::to_string(max_number_of_tests);
    auto pad_max_length     = max_tests.length()-1;
    std::string description_short = "Default Short Description";
    std::string description_long  = "Default Long  Description";
    width = 25;
    precision = 5;
    bool multi_line_enabled = false;
    enum_pad_direction padding = enum_pad_direction::right;
    std::string left_fill_char = " ";
    std::string test_name = "Make new(std::nothrow) DataColumnHeader() ";
    std::string pre_text = "";
    std::string post_text = "";
    long pad_length = 0;
    DataColumnHeader *dch;
    for (auto i = 1UL; i < max_number_of_tests; i++ )
    {
        test_number++;
        index_temp = std::to_string(i);
        pad_length = pad_max_length - index_temp.length();

        if (pad_length > 0)
        {
            column_pad = std::string(pad_max_length - index_temp.length(), '0');
        } else
        {
            column_pad = "";
        }

        index.clear();
        index.append(column_pad);
        index.append(index_temp);
        column_name.clear();
        column_name.append(default_name);
        column_name.append(index);

        dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name, description_short, description_long);
        dch->Set_Debug();
        result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short,
                                 description_long);
        dch->Show_Data_Header();
        test_name= "Make new(std::nothrow) DataColumnHeader() ";
        test_name = generate_test_name(true, pre_text, post_text, *dch);
        show_test_and_results(test_number, test_name, results, result);
        delete(dch);
    }



    return 0;
};


int test_003() {
    horizontal_line();
    std::cout << std::endl;
    std::cout << "Testing Data Dictionary Class: Test Set 003" << std::endl;
    std::cout << std::endl;

    // initialize variables
    unsigned int results[3] = {0, 0, 0};
    unsigned int test_number = 0;

    DataColumnHeader *dch;
    DataColumnHeader *dch1;
    enum_test_result result;


    test_number++; // Test 1
    std::string column_name = "Test Header 1";
    std::string description_short = "Description Test Header 1 Short";
    std::string description_long = "Description Test Header 1 Long";
    width = 32;
    precision = 10;
    bool multi_line_enabled = false;
    enum_pad_direction padding = enum_pad_direction::right;
    std::string left_fill_char = " ";
    dch = new(std::nothrow) DataColumnHeader(width, precision, multi_line_enabled, padding, column_name, description_short, description_long);
    dch->Set_Debug();
    result = validate_column(dch, width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short,
                             description_long);
    dch->Show_Data_Header();
    std::string pre_text = "";
    std::string post_text = "";
    std::string test_name = generate_test_name(true, pre_text, post_text, *dch);
    show_test_and_results(test_number, test_name, results, result);

    //
    auto size = 0UL;
    unsigned long index;

    DataDictionary dd = DataDictionary(false);
    const std::string SHIP_TYPE = "Ship Type";

    test_number++; // Test 2
    description_short = "Type of ship";
    description_long = "Type of Ship for Deep Space Game.";
    width = 12;
    precision = 10;
    multi_line_enabled = false;
    padding = enum_pad_direction::right;
    //write over existing values;
    dch->Initialize(width, precision, multi_line_enabled, padding, left_fill_char, SHIP_TYPE, description_short, description_long);
    dd.Add(dch);
    size += 1;
    index = size - 1;
    result = validate_DD_column(dch, &dd, index);
    dch->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch = dd(index = 0)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 3
    test_name = "Test index = searched for index";
    result = validate_indexes_match(index, dd, SHIP_TYPE);
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 4
    dch->Initialize(5, 5, false, epadDir::right, left_fill_char, "Speed", "Speed of Ship Type", "Speed of Ship Type");
    dd.Add(dch);
    size += 1;
    index = size - 1;
    dch->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary. Ensure dch = dd(index = 1)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 5
    test_name = "Test index = searched for index";
    result = validate_indexes_match(index, dd, "Speed");
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 6
    dch->Initialize(11, 5, false, epadDir::right, left_fill_char, "Cargo Space", "Cargo Space of Ship Type", "Cargo Space of Ship Type");
    dd.Add(dch);
    size += 1;
    index = size - 1;
    dch->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary. Ensure dch = dd(index = 2)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 7
    test_name = "Test index = searched for index";
    result = validate_indexes_match(index, dd, "Cargo Space");
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 8
    dch->Initialize(10, 5, false, epadDir::right, left_fill_char, "Protection", "Protection of Ship Type", "Protection of Ship Type");
    dd.Add(dch);
    size += 1;
    index = size - 1;
    dch->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch = dd(index = 3)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 9
    test_name = "Test index = searched for index";
    result = validate_indexes_match(index, dd, "Protection");
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

    test_number++; // Test 10
    auto curr_size = dd.Get_Size();
    dch->Initialize(14, 5, false, epadDir::right, left_fill_char, SHIP_TYPE, "Type of ship", "Type of Ship for Deep Space Game.");
    dd.Add(dch);
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    test_name = "Try to add a column that is already be there.";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; //Test 11
    dch->Initialize(5, 5, false, epadDir::right, left_fill_char,  "Speed", "Speed of Ship Type", "Speed of Ship Type");
    dd.Add(dch);
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    test_name = "Try to add a column that is already there.";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; //Test 12
    dch->Initialize(11, 5, false, epadDir::right, left_fill_char, "Cargo Space", "Cargo Space of Ship Type", "Cargo Space of Ship Type");
    dd.Add(dch);
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    test_name = "Try to add a column that is already be there.";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 13
    dch->Initialize(11, 5, false, epadDir::right, left_fill_char, "Protection1", "Protection1 of Ship Type", "Protection1 of Ship Type");
    dd.Add(dch);
    curr_size++;
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    test_name = "Add a column";
    show_test_and_results(test_number, test_name, results, result);

    dch1 = new(std::nothrow) DataColumnHeader();
    dch1->Set_Debug();
    dch1->Initialize(15, 5, false, epadDir::right, left_fill_char, "This is a test", "This is a test of Ship Type", "This is a test of Ship Type");
    dd.Replace("Protection1", dch1);
    horizontal_line();
    dd.Show_DataDictionaryAll();

    horizontal_line();

    test_number++; //Test 14
    dd.Remove(SHIP_TYPE);
    dd.Remove("Speed");
    dd.Remove("Cargo Space");
    dd.Remove("Protection");
    dd.Remove("Protection1");
    dd.Remove("This is a test");
    curr_size = 0;
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    dd.Show_DataDictionaryAll();
    test_name = "Deleted All Columns";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 15
    dd.Remove(SHIP_TYPE);
    curr_size = 0;
    if (curr_size == dd.Get_Size())
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::unknown;
    }
    test_name = "Tried to remove a column that does not exist.";
    show_test_and_results(test_number, test_name, results, result);

    horizontal_line();

    std::cout << std::endl;
    std::cout << "Testing DataDictionary Class Summary:" << std::endl;
    show_total_results(results);

    horizontal_line();
    horizontal_line();
    if (dch != nullptr)
    {
        delete dch;
        dch = nullptr;
    }
    if (dch1 != nullptr)
    {
        delete (dch1);
        dch1 = nullptr;
    }

    return 0;
}

int test_004a(DataGrid* dg, DataColumnHeader* dch, enum_pad_direction padding)
{
    std::cout << "Entering function: test_004a" << std::endl;
    std::string column_name;
    std::string description_short;
    std::string description_long = "Column for DeepSpace game";
    width     = 25;
    precision = 3;
    bool multi_line_enabled = false;
    std::string left_fill_char = "*";
    enum_pad_direction padding1 = enum_pad_direction::right;
    column_name         = "Ship Type";
    description_short   = column_name;
    dch->Initialize(width, precision, multi_line_enabled, padding1, left_fill_char, column_name, description_short, description_long);
    dg->Add_Column(dch);

    column_name         = "Speed";
    description_short   = column_name;
    dch->Initialize(width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short, description_long);
    dg->Add_Column(dch);

    column_name         = "Cargo Space";
    description_short   = column_name;
    dch->Initialize(width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short, description_long);
    dg->Add_Column(dch);

    column_name         = "Protection";
    description_short   = column_name;
    dch->Initialize(width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short, description_long);
    dg->Add_Column(dch);

    column_name         = "Maneuverability";
    description_short   = column_name;
    dch->Initialize(width, precision, multi_line_enabled, padding, left_fill_char, column_name, description_short, description_long);
    dg->Add_Column(dch);

    return 0;
}

int test_004b(DataGrid* dg)
{
    std::cout << "Entering function: test_004b" << std::endl;
    dg->Reset_Data();
    DG_Row dataValues;
    dataValues.push_back("Destroyer");
    dataValues.push_back("15x");
    dataValues.push_back("10x");
    dataValues.push_back("5x");
    dataValues.push_back("8x");
    dg->Add_DataToDataGrid(dataValues);

    dataValues.clear();
    dataValues.push_back("Cruiser");
    dataValues.push_back("20910x");
    dataValues.push_back("948218x");
    dataValues.push_back("093839x");
    dataValues.push_back("9493827x");
    dg->Add_DataToDataGrid(dataValues);

    dataValues.clear();
    dataValues.push_back("BattleShip");
    dataValues.push_back("10007x");
    dataValues.push_back("235x");
    dataValues.push_back("130x");
    dataValues.push_back("124x");
    dg->Add_DataToDataGrid(dataValues);
    dg->Show();
    return 0;
}

int test_004d(DataGrid* dg)
{
    std::cout << "Entering function: test_004d" << std::endl;
    DG_Row dataValues;
    dg->Reset_Data();
    dg->Set_Border_Type(enum_border_type::dashes);

    dataValues.push_back("Destroyer");
    dataValues.push_back("1");
    dataValues.push_back("10");
    dataValues.push_back("100");
    dataValues.push_back("1000");
    dg->Add_DataToDataGrid(dataValues);

    dataValues.clear();
    dataValues.push_back("Cruiser");
    dataValues.push_back("10.1x");
    dataValues.push_back("10.01x");
    dataValues.push_back("100.001x");
    dataValues.push_back("1000.0001x");
    dg->Add_DataToDataGrid(dataValues);

    dataValues.clear();
    dataValues.push_back("BattleShip");
    dataValues.push_back("1.0001");
    dataValues.push_back("10.0001");
    dataValues.push_back("100.0001");
    dataValues.push_back("1000.0001");
    dg->Add_DataToDataGrid(dataValues);
    dg->Set_OutputDirectory("/home/jay/ClionProjects/cppDataGrid_001");
    dg->Set_FileName("Test.txt");
    dg->Set_OutputToFile();
    dg->Show();
    dg->UnSet_OutputToFile();
    std::cout << "Unset output to file" << std::endl;
    dg->Show();
    return 0;
}


int test_004() {
    //set one column

    std::cout << "Entering function: test_004" << std::endl;
    DataDictionary* dd = new(std::nothrow) DataDictionary(true);
    if (dd != nullptr)
    {
        epadDir padding;

        DataColumnHeader dch1;
        dch1.Set_Debug();

        DataGrid *dg1 = new(std::nothrow) DataGrid("Ship Type 1", dd);

        //dg1->Set_Border_Type(enum_border_type::light);
        //dg1->Set_Border_Type(enum_border_type::double_line);
        //dg1->Set_Border_Type(enum_border_type::heavy);
        dg1->Set_Border_Type(enum_border_type::dashes);

        if (dg1 != nullptr) {
            std::cout << "Datagrid Name: " << dg1->Get_Name() << std::endl;
            dg1->Set_Pre_Text("This is the Pre Text");
            dg1->Set_Post_Text("This is the Post Text");
            dg1->Reset_Columns();
            padding = epadDir::decimal;
            test_004a(dg1, &dch1, padding);
            test_004b(dg1);
            test_004d(dg1);
            if (dg1 != nullptr) {
                delete dg1;
                dg1 = nullptr;
            }
        }
        if (dd != nullptr) {
            delete dd;
            dd = nullptr;
        }
    }
    return 0;
}
*/
//
// end of test sets
//


int main() {

    std::string test;
    std::unique_ptr<DataColumnHeader> dch1 = std::make_unique<DataColumnHeader>(true);
    test_001();

    //test_002();
    //test_003();
    //test_004();
}
