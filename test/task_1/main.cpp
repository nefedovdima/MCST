#include <iostream>
#include <type_traits>
#include <cassert>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
isPowerOfTwo(T a) {
    if (a <= 0) {
        return false;
    }
    return (a & (a - 1)) == 0;
}

void runTests() {
    // Тесты для типа int
    assert(isPowerOfTwo(1) == true);
    assert(isPowerOfTwo(2) == true);
    assert(isPowerOfTwo(3) == false);
    assert(isPowerOfTwo(4) == true);
    assert(isPowerOfTwo(0) == false);
    assert(isPowerOfTwo(-1) == false);

    // Тесты для типа unsigned int
    assert(isPowerOfTwo(1u) == true);
    assert(isPowerOfTwo(2u) == true);

    // Тесты для типа long long
    assert(isPowerOfTwo(1ll) == true);
    assert(isPowerOfTwo(2ll) == true);
    assert(isPowerOfTwo(1152921504606846976ll) == true);
    assert(isPowerOfTwo(9223372036854775807ll) == false);
    assert(isPowerOfTwo(-1ll) == false);

    // Тесты для типа unsigned long long
    assert(isPowerOfTwo(9223372036854775808ull) == true);


    // Тесты для типа char
    assert(isPowerOfTwo('a') == false);
    assert(isPowerOfTwo(static_cast<char>(2)) == true);
    assert(isPowerOfTwo(static_cast<char>(3)) == false);
    assert(isPowerOfTwo(static_cast<char>(4)) == true);
    assert(isPowerOfTwo(static_cast<char>(0)) == false);
    assert(isPowerOfTwo(static_cast<char>(-1)) == false);
    assert(isPowerOfTwo(static_cast<char>(-2)) == false);

    // Тесты для типа unsigned char
    assert(isPowerOfTwo(static_cast<unsigned char>(1)) == true);
    assert(isPowerOfTwo(static_cast<unsigned char>(2)) == true);
    assert(isPowerOfTwo(static_cast<unsigned char>(3)) == false);
    assert(isPowerOfTwo(static_cast<unsigned char>(4)) == true);
    assert(isPowerOfTwo(static_cast<unsigned char>(0)) == false);

    std::cout << "All tests OK!" << std::endl;
}

int main() {
    runTests();

    return 0;
}
