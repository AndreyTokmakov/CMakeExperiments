//
// Created by andtokm on 26.07.22.
//

#ifndef UTILITIES_LONG_H
#define UTILITIES_LONG_H

#include <iostream>
#include <memory>

namespace Utilities
{
    struct Long {
        long value {0};

        explicit Long() : value(0) {
            std::cout << "Long(0)\n";
        }

        explicit Long(int val) : value{val} {
            std::cout << "Long(" << value << ")\n";
        }

        Long(const Long &obj) {
            this->value = obj.value;
            std::cout << "Long(" << value << ") [Copy constructor]\n";
        }

        Long(Long &&obj) noexcept: value{std::exchange(obj.value, 0)} {
            std::cout << "Long(" << value << ") [Move constructor]\n";
        }

        inline void setValue(long v) noexcept {
            value = v;
        }

        [[nodiscard]]
        inline long getValue() const noexcept {
            return value;
        }

        ~Long() {
            std::cout << "~Long(" << value << ")\n";
        }

        Long &operator=(const Long &right) {
            std::cout << "[Copy assignment] (" << value << " -> " << right.value << ")" << std::endl;
            if (&right != this)
                value = right.value;
            return *this;
        }

        Long &operator=(long val) {
            std::cout << "[Copy assignment (from long)]" << std::endl;
            this->value = val;
            return *this;
        }

        Long &operator=(Long &&right) noexcept {
            std::cout << "[Move assignment operator]" << std::endl;
            if (this != &right) {
                this->value = std::exchange(right.value, 0);
            }
            return *this;
        }

        Long &operator*(const Long &right) noexcept {
            this->value *= right.value;
            return *this;
        }

        /** Postfix increment: **/
        Long operator++(int) {
            auto prev = *this;
            ++value;
            return prev;
        }

        /** Prefix increment: **/
        Long operator++() {
            ++value;
            return *this;
        }

        friend Long operator*(const Long &left, long v) noexcept {
            return Long(left.value * v);
        }

        friend std::ostream &operator<<(std::ostream &stream, const Long &l) {
            stream << l.value;
            return stream;
        }
    };
}

#endif //UTILITIES_LONG_H
