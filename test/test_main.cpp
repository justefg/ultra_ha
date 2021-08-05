#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include "../src/shared/helpers.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const vec_t& vec) {
    os << "[";
    int sz = vec.size();
    for (const auto& v : vec) {
        os << v;
        sz--;
        if (sz) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

// vector serialization for BOOST_REQUIRE_EQUAL
// https://stackoverflow.com/questions/17572583/boost-check-fails-to-compile-operator-for-custom-types
namespace boost { namespace test_tools { namespace tt_detail {
template<>
struct print_log_value<vec_t> {
void operator()(std::ostream & os, const vec_t& vec) {
    ::operator<<(os, vec);
}
};
}}}

BOOST_AUTO_TEST_SUITE(ulta_ha)

BOOST_AUTO_TEST_CASE(add_non_negative) {
    BOOST_REQUIRE_EQUAL(0, add(0, 0));
    BOOST_REQUIRE_EQUAL(5, add(2, 3));
    BOOST_REQUIRE_EQUAL(201, add(123, 78));
}

BOOST_AUTO_TEST_CASE(add_non_negative_overflow) {
    // ...
}

// ===================================

BOOST_AUTO_TEST_CASE(empty_set) {
    vec_t result;
    uint64_t largest_sum;
    find_largest_sum(11, {}, result, largest_sum);
    const vec_t expected{};
    BOOST_REQUIRE_EQUAL(expected, result);
    BOOST_REQUIRE_EQUAL(0, largest_sum);
}

BOOST_AUTO_TEST_CASE(duplicate_elements) {
    vec_t result;
    uint64_t largest_sum;
    find_largest_sum(3, {1, 1}, result, largest_sum);
    const vec_t expected{1, 1};
    BOOST_REQUIRE_EQUAL(expected, result);
    BOOST_REQUIRE_EQUAL(2, largest_sum);
}

BOOST_AUTO_TEST_CASE(sample) {
    vec_t result;
    uint64_t largest_sum;
    find_largest_sum(11, {1, 2, 3, 4, 5, 6, 7}, result, largest_sum);
    // one possible answer would be
    const vec_t expected{5, 6};
    BOOST_REQUIRE_EQUAL(expected, result);
    BOOST_REQUIRE_EQUAL(11, largest_sum);
}

BOOST_AUTO_TEST_SUITE_END()