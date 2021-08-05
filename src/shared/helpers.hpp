#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <functional>
#include <exception>

struct overflow_error : public std::exception {
    const char * what () const throw () {
    	return "integer overflow exception";
    }
};

#include <iostream>

int64_t add(int64_t a, int64_t b) {
    int64_t sum = 0;
    int carry = 0;
    for (int i = 0; i < sizeof(int64_t); i++) {
        const auto bit1 = static_cast<int>((a & (1ll << i)) != 0);
        const auto bit2 = static_cast<int>((b & (1ll << i)) != 0);
        auto resulting_bit = bit1 + bit2 + carry;
        if (resulting_bit >= 2) {
            resulting_bit %= 2;
            carry = 1;
        } else {
            carry = 0;
        }
        if (resulting_bit) {
            sum |= (1ll << i);
        }
    }
    if (carry) {
        // TODO this will fail for negative numbers
        throw overflow_error();
    }
    return sum;
}

using set_sum_t = std::unordered_map<uint64_t, uint64_t>;
using vec_t = std::vector<uint64_t>;

void find_largest_sum(uint64_t target, const vec_t& integer_set,
                      vec_t& integers_picked,
                      uint64_t& max_possible_sum) {
    // Finds a subset (integers_picked) that the sum (max_possible_sum)
    // of (integers_picked)'s elements is the largest among all subsets of (integer_set),
    // where (integers_picked) is less or equal to target

    set_sum_t possible_sums;
    possible_sums.insert({0, 0});
    auto sorted_values = integer_set;
    std::sort(sorted_values.begin(), sorted_values.end(), std::greater<int>());
    max_possible_sum = 0;
    for (const auto current_value : sorted_values) {
        set_sum_t new_possible_sums;
        for (const auto [possible_sum, last_added] : possible_sums) {
            // check for a possible overflow!!
            const auto new_sum = possible_sum + current_value;
            if (new_sum <= target) {
                new_possible_sums[new_sum] = current_value;
                max_possible_sum = std::max(max_possible_sum, new_sum);
            }
        }
        possible_sums.insert(new_possible_sums.begin(), new_possible_sums.end());
    }
    auto current_sum = max_possible_sum;
    auto it = possible_sums.find(max_possible_sum);
    while (current_sum != 0) {
        integers_picked.push_back(it->second);
        current_sum -= it->second;
        it = possible_sums.find(current_sum);
    }
}