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
            std::cout << "test01 = " << std::boolalpha << test01 << std::endl;
            std::cout << "test02 = " << std::boolalpha << test02 << std::endl;
            std::cout << "test03 = " << std::boolalpha << test03 << std::endl;
            std::cout << "test04 = " << std::boolalpha << test04 << std::endl;
            std::cout << "test05 = " << std::boolalpha << test05 << std::endl;
            std::cout << "test06 = " << std::boolalpha << test06 << std::endl;
            std::cout << "test07 = " << std::boolalpha << test07 << std::endl;
            std::cout << "test08 = " << std::boolalpha << test08 << std::endl;
            std::cout << "test09 = " << std::boolalpha << test09 << std::endl;
            std::cout << "test10 = " << std::boolalpha << test10 << std::endl;

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

    std::cout << "Testing DataColumnHeader Class Summary:" << std::endl;
    show_total_results(results);

    horizontal_line();


    return 0;
}


int test_002()
{

    horizontal_line();
    std::cout << std::endl;
    std::cout << "Testing DataColumnHeader Class: Test Set 002" << std::endl;
    std::cout << std::endl;

    // initialize variables
    unsigned int results[3] = {0, 0, 0};
    unsigned int test_number = 0;
    enum_test_result result;

    bool debug = true;
    bool multi_line_output = false;
    bool sql_quote = false;
    int max_number_of_tests = 100000;
    epadDir pad_direction = enum_pad_direction::right;
    std::string default_name = "Column Name ";
    std::string column_name  = "";
    std::string column_pad   = "00000";
    std::string index_temp   = "";
    std::string index        = "";

    std::string max_tests   = std::to_string(max_number_of_tests);
    auto pad_max_length     = max_tests.length()-1;
    std::string description_short = "Default Short Description";
    std::string description_long  = "Default Long  Description";
    int width = 26;
    int precision = 5;
    bool multi_line_enabled = false;
    enum_pad_direction padding = enum_pad_direction::right;
    std::string left_fill_char = " ";
    std::string test_name = "make unique pointer to data column header";
    std::string pre_text = "";
    std::string post_text = "";
    long pad_length = 0;
    for (auto i = 1UL; i <= max_number_of_tests; i++ )
    {
        std::unique_ptr<DataColumnHeader> dch1 = std::make_unique<DataColumnHeader>(debug);
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

        dch1->Set_ColumnHeader(column_name);
        dch1->Set_ColumnDescriptionShort(description_short);
        dch1->Set_ColumnDescriptionLong(description_long);
        dch1->Set_DisplayWidth(width);
        dch1->Set_Precision(precision);
        result = validate_column(*dch1, debug, multi_line_output, sql_quote, pad_direction, column_name, description_long,
                                 description_short, left_fill_char, width, precision);
        show_test_and_results(test_number, test_name, results, result);
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

    enum_test_result result;

    auto size = 0UL;
    unsigned long index;

    DataDictionary dd = DataDictionary(false);
    const std::string SHIP_TYPE = "Ship Type";

    test_number++; // Test 1
    std::string test_name = "Create data column header";
    std::string column_name = "Test Header 1";
    std::string description_short = "Short Test Header";
    std::string description_long  = "Long  Test Header";
    bool debug = true;
    bool sql_quote = false;
    int width = 32;
    int precision = 10;
    bool multi_line_enabled = false;
    enum_pad_direction padding = enum_pad_direction::right;
    std::string left_fill_char = " ";
    std::unique_ptr<DataColumnHeader> dch1 = std::make_unique<DataColumnHeader>(debug);

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dd.Add(*dch1);

    result = validate_column(*dch1, debug, multi_line_enabled, sql_quote, padding, column_name, description_long,
                             description_short, left_fill_char, width, precision);
    dch1->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 2
    test_name = "Create data column header";
    column_name       = "Type of Ship";
    description_short = "Type of ship";
    description_long  = "Type of Ship for Deep Space Game.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dd.Add(*dch1);

    result = validate_column(*dch1, debug, multi_line_enabled, sql_quote, padding, column_name, description_long,
                             description_short, left_fill_char, width, precision);

    dch1->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 3
    test_name = "Create data column header";
    column_name       = "Armor of Ship";
    description_short = "Armor of ship";
    description_long  = "Armor of Ship for Deep Space Game.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dd.Add(*dch1);

    result = validate_column(*dch1, debug, multi_line_enabled, sql_quote, padding, column_name, description_long,
                             description_short, left_fill_char, width, precision);

    dch1->Show_Data_Header();
    show_test_and_results(test_number, test_name, results, result);


    dd.Show_DataDictionaryAll();

    /*
    size += 1;
    index = size - 1;
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch1 = dd(index = 0)";
    show_test_and_results(test_number, test_name, results, result);


    test_number++; // Test 3
    column_name       = "Armor of Ship";
    description_short = "Armor of ship";
    description_long  = "Armor of Ship for Deep Space Game.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dch1->Set_Pad_Direction(enum_pad_direction::both);

    dd.Add(*dch1);
    size += 1;
    index = size - 1;
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch1 = dd(index = 1)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 4
    column_name       = "Speed of Ship";
    description_short = "Speed of ship";
    description_long  = "Speed of Ship for Deep Space Game.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dch1->Set_Pad_Direction(enum_pad_direction::right);

    dd.Add(*dch1);
    size += 1;
    index = size - 1;
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch1 = dd(index = 2)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 5
    column_name       = "Cargo Space";
    description_short = "Cargo Space of ship";
    description_long  = "Cargo Space of ship.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dch1->Set_Pad_Direction(enum_pad_direction::decimal);

    dd.Add(*dch1);
    size += 1;
    index = size - 1;
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch1 = dd(index = 3)";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; // Test 6
    column_name       = "Weapons";
    description_short = "Weapons of ship";
    description_long  = "Weapons of ship.";

    dch1->Set_ColumnHeader(column_name);
    dch1->Set_ColumnDescriptionShort(description_short);
    dch1->Set_ColumnDescriptionLong(description_long);
    dch1->Set_DisplayWidth(width);
    dch1->Set_Precision(precision);
    dch1->Set_Pad_Direction(enum_pad_direction::left);

    dd.Add(*dch1);
    size += 1;
    index = size - 1;
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Set DataColumnHeader and add DeepCopy to Data_Dictionary.. Ensure dch1 = dd(index = 4)";
    show_test_and_results(test_number, test_name, results, result);


    dd.Show_DataDictionaryAll();

    test_number++; // Test 7
    dd.Add(*dch1);
    result = validate_indexes_match(index, dd, column_name);
    dch1->Show_Data_Header();
    dd.Get_HeaderNameWithPadding(index);
    test_name = "Try to add a column that is already be there.";
    show_test_and_results(test_number, test_name, results, result);

    test_number++; //Test 8
    auto curr_size = dd.Get_Size();
    auto i = curr_size - curr_size;

    for (; i < curr_size; ++i )
    {
        std::cout << "***" << dd.Get_HeaderNameWithPadding(i)            << "***" << std::endl;
        std::cout << "***" << dd.Get_ValueWithPadding(i, "This is a Test by Jay", 32 ) << "***" << std::endl;
    }



    test_number++; //Test 8
    dd.Remove("Type of Ship");
    curr_size = dd.Get_Size();
    if (curr_size == 4)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove the first column.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();


    test_number++; //Test 9
    dd.Remove("Armor of Ship");
    curr_size = dd.Get_Size();
    if (curr_size == 3)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove the first column.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

    test_number++; //Test 10
    dd.Remove("Cargo Space");
    curr_size = dd.Get_Size();
    if (curr_size == 2)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove the first column.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

    test_number++; //Test 11
    dd.Remove("Weapons");
    curr_size = dd.Get_Size();
    if (curr_size == 1)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove the last column.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

    test_number++; //Test 12
    dd.Remove("Speed of Ship");
    curr_size = dd.Get_Size();
    if (curr_size == 0)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove the only column.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

    test_number++; //Test 12
    dd.Remove("");
    curr_size = dd.Get_Size();
    if (curr_size == 0)
    {
        result = enum_test_result::good;
    } else
    {
        result = enum_test_result::failed;
    }
    test_name = "Try to remove a column from an empty data dictionary.";
    show_test_and_results(test_number, test_name, results, result);

    dd.Show_DataDictionaryAll();

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
        result = enum_test_result::failed;
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
        result = enum_test_result::failed;
    }
    test_name = "Tried to remove a column that does not exist.";
    show_test_and_results(test_number, test_name, results, result);

    */

    horizontal_line();
    std::cout << std::endl;
    std::cout << "Testing DataDictionary Class Summary:" << std::endl;
    show_total_results(results);
    horizontal_line();
    horizontal_line();

    return 0;
}


/*
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

void test5()
{
    static std::string temp;
    auto max0 = temp.max_size();
    auto max1 = max0;
    max1++;

    static std::vector<sstr> temp1;
    auto max4 = temp1.max_size();
    auto max5 = max4;
    max5++;

    static std::vector<int> temp2;
    auto max8 = temp2.max_size();
    auto max9 = max8;
    max9++;

    static std::vector<DataColumnHeader> temp3;
    auto max12 = temp3.max_size();
    auto max13 = max12;
    max13++;
    auto min = max0 - max0;


}

int main() {

    //test_001();
    //test_002();
    //test_003();
    //test_004();
    test5();
}
