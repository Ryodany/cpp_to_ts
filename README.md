# C++ Code Challenge

The objective is to print the contents of `ut/translator/test_files/target.ts` from C++ code (`include/entities/{order,balance}.hpp` headers), by using standard C++17 features, no external dependencies are allowed.

Extra points for leaning towards compile time as much as possible, rather than runtime.

Unit tests done with Catch2 for header-only convinience.

## Build & Run

`mkdir build && cd build && cmake .. && make && ./../bin/ut && ./../bin/challenge`
