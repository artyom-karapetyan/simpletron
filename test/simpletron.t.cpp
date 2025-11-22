#include <simpletron.h>
#include <gtest/gtest.h>
#include <string>


namespace {

const std::string_view add_two_ints = R"(
    +1007
    +1008
    +2007
    +3008
    +2109   
    +1109 
    +4300  
    +0000
    +0000
    +0000
)";

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
