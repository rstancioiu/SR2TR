#include "CSV_file_reader.hpp"

#include "gtest/gtest.h"

using namespace sr2tr::reader;

class CSV_file_reader_test : public ::testing::Test {
   public:
    CSV_file_reader_test()
        : file_reader("test/sample-tests/test1/source.csv") {}

    CSV_file_reader file_reader;
};

TEST_F(CSV_file_reader_test, get_columns) {
    std::vector<std::string> columns = file_reader.get_columns();
    ASSERT_EQ(6u, columns.size());
    ASSERT_EQ("A", columns[0]);
    ASSERT_EQ("err_A", columns[1]);
    ASSERT_EQ("B", columns[2]);
    ASSERT_EQ("err_B", columns[3]);
    ASSERT_EQ("C", columns[4]);
    ASSERT_EQ("err_C", columns[5]);
}

TEST_F(CSV_file_reader_test, get_line) {
    std::vector<std::string> columns = file_reader.get_columns();
    std::vector<double> line_values = file_reader.get_line();
    ASSERT_EQ(6u, line_values.size());
    ASSERT_EQ(0.25, line_values[0]);
    ASSERT_EQ(0.25, line_values[1]);
    ASSERT_EQ(0.5, line_values[2]);
    ASSERT_EQ(0.5, line_values[3]);
    ASSERT_EQ(0.5, line_values[4]);
    ASSERT_EQ(0.5, line_values[5]);
}