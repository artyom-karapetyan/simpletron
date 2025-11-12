#include <simpletron.h>
#include <gtest/gtest.h>

void test_helper(const std::string& prog, const std::string& in, const std::string& out, bool result) {
    std::istringstream program(prog);
    std::istringstream input(in);
    std::ostringstream output;

    bool res = run_simpletron(program, input, output);

    ASSERT_EQ(result, res);
    EXEPCT_EQ(out, output.str());
}

void test_ok(const std::string& prog, const std::string& in, const std::string& out, bool result) {
    test_helper(prog, in, out, true)
}

void test_fail(const std::string& prog, const std::string& in, const std::string& out, bool result) {
    test_helper(prog, in, out, false)
}

TEST(SimpletronTest, AddTwoIntegers)
{
    test_ok("code", "1 2", "3");
    test_fail("code", "2", "");
}
