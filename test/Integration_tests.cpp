#include <filesystem>

#include "gtest/gtest.h"
#include "sr2tr/Mapping.hpp"
#include "sr2tr/Reader.hpp"

using namespace sr2tr;

class Integration_test : public ::testing::Test {
   protected:
    void Setup_relations(const std::string& source_relation_relative_path,
                         const std::string& target_relation_relative_path) {
        const std::string source_full_path =
            std::filesystem::current_path().string() +
            source_relation_relative_path;
        const std::string target_full_path =
            std::filesystem::current_path().string() +
            target_relation_relative_path;
        std::tie(source, column_names_source) =
            Reader::Read_file(source_full_path);
        std::tie(target, column_names_target) =
            Reader::Read_file(target_full_path);
    }

    Relation source;
    Relation target;
    std::vector<std::string> column_names_source;
    std::vector<std::string> column_names_target;
};

TEST_F(Integration_test, Sample_test_1_satisfaction_metric_1) {
    Setup_relations("/test/sample-tests/test1/source.csv",
                    "/test/sample-tests/test1/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 1;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_NEAR(1.714285, cost, 1e-6);
    ASSERT_EQ(3u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"A", "F"}, {"B", "G"}, {"C", "E"}};
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}

TEST_F(Integration_test, Sample_test_1_satisfaction_metric_2) {
    Setup_relations("/test/sample-tests/test1/source.csv",
                    "/test/sample-tests/test1/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 2;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_NEAR(1.714285, cost, 1e-6);
    ASSERT_EQ(3u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"A", "F"}, {"B", "G"}, {"C", "E"}};
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}

TEST_F(Integration_test, Sample_test_2_satisfaction_metric_1) {
    Setup_relations("/test/sample-tests/test2/source.csv",
                    "/test/sample-tests/test2/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 1;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    mapping.print_results(column_names_source, column_names_target);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_EQ(0, cost);
    ASSERT_EQ(4u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"A", "A"}, {"B", "B"}, {"C", "C"}, {"D", "D"}};
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}

TEST_F(Integration_test, Sample_test_2_satisfaction_metric_2) {
    Setup_relations("/test/sample-tests/test2/source.csv",
                    "/test/sample-tests/test2/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 2;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    mapping.print_results(column_names_source, column_names_target);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_EQ(0, cost);
    ASSERT_EQ(4u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"A", "A"}, {"B", "B"}, {"C", "C"}, {"D", "D"}};
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}

TEST_F(Integration_test, Large_test_satisfaction_metric_1) {
    Setup_relations("/test/large-tests/source.csv",
                    "/test/large-tests/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 1;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    mapping.print_results(column_names_source, column_names_target);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_NEAR(10.7793054, cost, 1e-6);
    ASSERT_EQ(11u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"ra", "ra"},   {"dec", "dec"}, {"u", "u"},     {"g", "i"},
        {"r", "z"},     {"i", "r"},     {"z", "g"},     {"u-g", "i-z"},
        {"g-r", "g-r"}, {"r-i", "u-g"}, {"i-z", "r-i"},
    };
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}

TEST_F(Integration_test, Large_test_satisfaction_metric_2) {
    Setup_relations("/test/large-tests/source.csv",
                    "/test/large-tests/target.csv");
    Mapping mapping;
    static constexpr int Satisfaction = 2;
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        mapping.SR2TR(source, target, Satisfaction);
    mapping.print_results(column_names_source, column_names_target);
    double& cost = matching.first;
    std::vector<std::pair<uint32_t, uint32_t>>& function = matching.second;
    ASSERT_NEAR(5.263489, cost, 1e-6);
    ASSERT_EQ(11u, function.size());
    std::vector<std::pair<std::string, std::string>> expected_column_pairs = {
        {"ra", "ra"},   {"dec", "dec"}, {"u", "i"},     {"g", "r"},
        {"r", "z"},     {"i", "g"},     {"z", "u"},     {"u-g", "i-z"},
        {"g-r", "g-r"}, {"r-i", "u-g"}, {"i-z", "r-i"},
    };
    for (uint32_t index = 0; index < expected_column_pairs.size(); index++) {
        ASSERT_EQ(expected_column_pairs[index].first,
                  column_names_source[function[index].first - 1]);
        ASSERT_EQ(expected_column_pairs[index].second,
                  column_names_target[function[index].second - 1]);
    }
}