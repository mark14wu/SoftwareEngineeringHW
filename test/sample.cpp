#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Core.hpp"

#include <numeric>

int compute_chain_size(const vector<string> &result) {
    return accumulate(result.begin(), result.end(), 0, [](int sum, string s) { return sum + s.size(); });
}

BOOST_AUTO_TEST_SUITE(test_gen_chain_char)

    BOOST_AUTO_TEST_CASE(testExact) {
        {
            vector<string> input = {"axe", "bed", "softly", "room"};
            vector<string> expected = {"softly"};
            BOOST_TEST(Core::gen_chain_char(input) == expected);
        }
        {
            vector<string> input = {"axe", "bed", "softly", "yak"};
            vector<string> expected = {"softly", "yak"};
            BOOST_TEST(Core::gen_chain_char(input) == expected);
        }
        {
            vector<string> input = {"axe", "extended", "extend"};
            vector<string> expected = {"axe", "extended"};
            BOOST_TEST(Core::gen_chain_char(input) == expected);
        }
        {
            vector<string> input = {"axe", "extended", "extend"};
            vector<string> expected = {"extended"};
            BOOST_TEST(Core::gen_chain_char(input, 'e', 'd') == expected);
        }
        {
            vector<string> input = {"axe", "extended", "extend"};
            vector<string> expected = {"axe", "extended"};
            BOOST_TEST(Core::gen_chain_char(input, 'a') == expected);
        }
    }

// No chain
    BOOST_AUTO_TEST_CASE(testNoChain) {
        BOOST_TEST(Core::gen_chain_char({"axe", "bed", "softly", "room"}) == vector<string>{"softly"});
    }

// One word chain
    BOOST_AUTO_TEST_CASE(testOneWordChain) {
        BOOST_TEST(Core::gen_chain_char({"axe", "bed", "sofa", "roommate"}).size() == 1);
    }

// Find most
    BOOST_AUTO_TEST_CASE(testFindMost) {
        BOOST_TEST(compute_chain_size(Core::gen_chain_char({"alpha", "alexa", "agenda", "algebra"})) == 23);
        BOOST_TEST(compute_chain_size(Core::gen_chain_char({"alpha", "alexa", "agenda", "algebras"})) == 24);
    }

    BOOST_AUTO_TEST_CASE(testEmpty) {
        BOOST_TEST(Core::gen_chain_char({}) == vector<string>{});
    }

BOOST_AUTO_TEST_SUITE_END()