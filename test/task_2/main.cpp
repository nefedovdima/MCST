#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>

class BitVector {
private:
    std::vector<uint64_t> data;
    std::size_t bit_size;

public:
    // Конструктор (разрядность, массив переменных интегрального типа)
    BitVector(std::size_t bit_size, const std::vector<uint64_t>& input_data)
            : bit_size(bit_size), data(input_data) {
        if (data.size() * 64 < bit_size) {
            throw std::invalid_argument("Insufficient data to initialize the bit vector");
        }
    }

    // Метод для получения разрядности
    std::size_t getBitSize() const {
        return bit_size;
    }

    // Метод для установки битового поля (смещение, битвектор)
    void setBitField(std::size_t offset, const BitVector& bv) {
        if (offset + bv.bit_size > bit_size) {
            throw std::out_of_range("Bit field exceeds vector bounds");
        }
        for (std::size_t i = 0; i < bv.bit_size; ++i) {
            setBit(offset + i, bv.getBit(i));
        }
    }

    // Метод для установки битового поля (смещение, разрядность, переменная интегрального типа)
    void setBitField(std::size_t offset, std::size_t length, uint64_t value) {
        if (offset + length > bit_size) {
            throw std::out_of_range("Bit field exceeds vector bounds");
        }
        for (std::size_t i = 0; i < length; ++i) {
            setBit(offset + i, (value >> i) & 1);
        }
    }

    BitVector getBitField(std::size_t offset, std::size_t length) const {
        if (offset + length > bit_size) {
            throw std::out_of_range("Bit field exceeds vector bounds");
        }
        std::vector<uint64_t> result_data((length + 63) / 64, 0);

        // Write bits to result_data
        for (std::size_t i = 0; i < length; ++i) {
            if (getBit(offset + i)) {
                result_data[i / 64] |= (1 << (i % 64));
            }
        }
        BitVector result(length, result_data);
        return result;
    }

    // Метод для получения битового поля (смещение, разрядность) в переменную интегрального типа
    uint64_t getBitFieldAsInt(std::size_t offset, std::size_t length) const {
        if (length > 64 || offset + length > bit_size) {
            throw std::out_of_range("Bit field exceeds vector bounds");
        }
        uint64_t result = 0;
        for (std::size_t i = 0; i < length; ++i) {
            result |= (static_cast<uint64_t>(getBit(offset + i)) << i);
        }
        return result;
    }

    // Метод для получения строкового представления в 16-ричном виде
    std::string toHexString() const {
        std::ostringstream oss;
        for (auto it = data.rbegin(); it != data.rend(); ++it) {
            oss << std::setfill('0') << std::setw(16) << std::hex << *it;
        }
        return oss.str();
    }

private:
    // Вспомогательный метод для установки бита
    void setBit(std::size_t index, bool value) {
        if (index >= bit_size) {
            throw std::out_of_range("Index exceeds vector bounds");
        }
        std::size_t data_index = index / 64;
        std::size_t bit_index = index % 64;
        if (value) {
            data[data_index] |= (1ULL << bit_index);
        } else {
            data[data_index] &= ~(1ULL << bit_index);
        }
    }

    // Вспомогательный метод для получения значения бита
    bool getBit(std::size_t index) const {
        if (index >= bit_size) {
            throw std::out_of_range("Index exceeds vector bounds");
        }
        std::size_t data_index = index / 64;
        std::size_t bit_index = index % 64;
        return (data[data_index] >> bit_index) & 1;
    }
};

int main() {
    // Пример использования класса BitVector
    std::vector<uint64_t> input_data = {0x123456789ABCDEF0, 0x0FEDCBA987654321};
    BitVector bv(128, input_data);

    std::cout << bv.toHexString() << "\n";
    std::cout << "BitSize: " << bv.getBitSize() << std::endl;

    // Установка и получение битового поля
    BitVector bv2 = bv.getBitField(4, 8);
    std::cout << "BitField: " << bv2.toHexString() << std::endl;

    // Установка битового поля с использованием переменной интегрального типа
    bv.setBitField(16, 8, 0xAA);
    std::cout << "Modified bit vector: " << bv.toHexString() << std::endl;

    // Получение битового поля в переменную интегрального типа
    uint64_t field_value = bv.getBitFieldAsInt(16, 8);
    std::cout << "The resulting bit field as int: " << std::hex << field_value << std::endl;

    return 0;
}
