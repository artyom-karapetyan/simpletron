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

// void test_helper(std::string_view prog, std::string_view in, std::string_view out, Result res) {
//     std::istringstream program(std::string{prog});
//     std::istringstream input(std::string{in});
//     std::ostringstream output;

//     if (res == Result::Success)
//     {
//         EXPECT_NO_THROW(run_simpletron(program, input, output));
//         EXPECT_EQ(out, output.str());
//     }
//     else
//     {
//         EXPECT_THROW(run_simpletron(program, input, output));
//     }
// }

// void test_ok(std::string_view prog, std::string_view in, std::string_view out) {
//     test_helper(prog, in, out, Result::Success);
// }

// void test_fail(std::string_view prog, std::string_view in, std::string_view out) {
//     test_helper(prog, in, out, Result::Fail);
// }

TEST(SimpletronTest, AddTwoIntegers)
{
    EXPECT_EQ(run_simpletron(add_two_ints, "1 2"), "3");

    // EXPECT_THROW(run_simpletron(add_two_ints, "1 2"), std::runtime_error);
}
