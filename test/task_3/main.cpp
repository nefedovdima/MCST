#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


template <typename T>
std::vector<T> getRandomSample(const std::vector<T>& vec, std::size_t n) {
    if (n > vec.size()) {
        throw std::invalid_argument("n must be less than or equal to the size of vector a");
    }

    std::vector<T> sample(n);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::sample(vec.begin(), vec.end(), sample.begin(), n, gen);

    return sample;
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::size_t n = 5;

    try {
        std::vector<int> sample = getRandomSample(v, n);

        std::cout << "Random selection of " << n << " elements: ";
        for (const int& elem : sample) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
