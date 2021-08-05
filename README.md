Ultra home assignment
================

## Requirements
I have boost 1.73 on my laptop but I guess 1.60+ should be fine.
CMake should also be intstalled on your system.

## How does it work?
Simply build and run unit tests
```
mkdir build
cmake ..
make
./test/ultra_ha_unit_tests
```

## From the author
I timeboxed the assignment to around 2,5 hours and naturally had to make sacrifices.
Some obvious improvements include:
- Better project structure
- CI pipeline (tests & linter check)
- More tests
- Simple demo (aka reading input from a file and printing to the console)
- More in-depth explanation of the solutions

### Integer sum
I went with a straightforward approach: treat a 64-bit integer
as an array of 64 values (0 or 1). Addition is then handled very easily
by using carries. Checking for an overflow is just making sure carry equals to 1. The problem with this solution is that it fails
to work for negative numbers because of the way they're represented in C/C++
(two's complement number system). I think a possible workaround
would to implement a subtraction algorithm similar to what I described. And then we just choose which of the algorithms
to use depending on the signs of `a` and `b` .

### Max subset sum <= T
In this problem I implemented a simple algorithm
that tracks possible sums after adding each element from the
integer set (`I`), i.e we start
with {0} (`P`) and on each iteration step we just add the current element from `I` to every element of `P`.
I used `std::unordered_map` as an optimization to avoid creating a large
array. Although I think even the hashmap will likely fail when both `T` and `I` are
sufficiently large because we need to store `min(2^|I|, T)` elements (possible sums) in memory.
As for getting the resulting set it's fairly straightforward if you keep
the last added element. Once you get the maximum possible sum you simply iterate backwards until you hit 0.
