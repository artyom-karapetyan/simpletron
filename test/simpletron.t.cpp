#include <simpletron.h>
#include <operations.h>
#include <gtest/gtest.h>
#include <string>


namespace {

std::string two_numbers_op(int op) {
    return std::format(R"(
        +1007
        +1008
        +2007
        +{}08
        +2109   
        +1109 
        +4300  
        +0000
        +0000
        +0000
    )", op);
}

const std::string add_two_ints = two_numbers_op(ADD);
const std::string sub_two_ints = two_numbers_op(SUBTRACT);
const std::string mul_two_ints = two_numbers_op(MULTIPLY);
const std::string div_two_ints = two_numbers_op(DIVIDE);

}

TEST(SimpletronTest, TrimWhitespaces)
{
    std::string str("  +4564  ");
    EXPECT_EQ(trim(str), "+4564");

    str = "+4564";
    EXPECT_EQ(trim(str), "+4564");

    str = "+4564\t\n";
    EXPECT_EQ(trim(str), "+4564");

    str = "  \r \t\n \f  \v ";
    EXPECT_EQ(trim(str), "");
}


TEST(SimpletronTest, AddTwoIntegers)
{
    EXPECT_EQ(run_simpletron(add_two_ints, "1 2"), "3");
    EXPECT_EQ(run_simpletron(add_two_ints, "-1 -2"), "-3");
    EXPECT_EQ(run_simpletron(add_two_ints, "1234 5678"), "6912");
}

TEST(SimpletronTest, AddTwoIntegers_PartialInput)
{
    EXPECT_THROW(run_simpletron(add_two_ints, "1 "), std::runtime_error);
}

TEST(SimpletronTest, AddTwoIntegers_Overflow)
{
    EXPECT_THROW(run_simpletron(add_two_ints, "9999 1"), std::out_of_range);
        // @todo:artyom - "Number 10000 is outside of range [-9999, 9999]".
}

TEST(SimpletronTest, AddTwoIntegers_InvalidInput)
{
    EXPECT_THROW(run_simpletron(add_two_ints, "1 123456"), std::out_of_range);
        // @todo:artyom - improve later to verify text - "Value doesn't fit inside the type s"
}

TEST(SimpletronTest, InvalidAddress)
{
    EXPECT_THROW(run_simpletron("+1015", "1"), std::runtime_error);
        // @todo:artyom - improve later to verify text - "Attempt to access memory at invalid address: 15"
}

TEST(SimpletronTest, DivisionTwoInts)
{
    EXPECT_EQ(run_simpletron(div_two_ints, "8 2"), "4");
    EXPECT_EQ(run_simpletron(div_two_ints, "-8 2"), "-4");
    EXPECT_EQ(run_simpletron(div_two_ints, "-8 -2"), "4");
    EXPECT_EQ(run_simpletron(div_two_ints, "2 8"), "0");
}

TEST(SimpletronTest, DivisionByZero)
{
    EXPECT_THROW(run_simpletron(div_two_ints, "1 0"), std::runtime_error);
        // @todo:artyom - improve later to verify text - "Attempt to divide by zero."
}
