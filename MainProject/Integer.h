//============================================================================
// Name        : Integer.h
// Created on  : 01.04.2020
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Integer class
//============================================================================

#ifndef INTEGER_INCLUDE_GUARD__H
#define INTEGER_INCLUDE_GUARD__H

#include <iostream>
#include <memory>

/** Integet class. **/
class Integer {
protected:
    int value;

public:
    Integer();
    explicit Integer(int val);
    Integer(const Integer &obj);
    Integer(Integer &&obj);

    virtual ~Integer();

    virtual int getValue() const noexcept;
    virtual void setValue(int val) noexcept;

    virtual void printInfo() const noexcept;
    virtual void increment(void) noexcept;


public: /** Operators reload. **/
    friend std::ostream& operator<<(std::ostream& stream,
                                    const Integer& integer);

    friend const Integer operator+(const Integer& left,
                                   const Integer& right);

    friend Integer& operator+=(Integer& left,
                               const Integer& right);

    friend bool operator==(const Integer& left,
                           const Integer& right);

    friend bool operator<(const Integer& left,
                          const Integer& right);

    friend bool operator>(const Integer& left,
                          const Integer& right);

    Integer& operator=(const Integer& right) {
        std::cout << "[Copy assignment operator from Integer -> Integer]" << std::endl;
        if (this == &right) {
            return *this;
        }
        value = right.value;
        return *this;
    }

    Integer& operator=(int val) {
        std::cout << "[Copy assignment operator from int -> Integer]" << std::endl;
        this->value = val;
        return *this;
    }

    Integer& operator=(Integer&& integer) noexcept {
        std::cout << "[Move assignment operator]" << std::endl;
        this->value = std::exchange(integer.value, 0);
        return *this;
    }

    friend const Integer operator+(const Integer& integer);
    friend const Integer operator-(const Integer& integer);


    friend int operator+(const Integer& integer, int v);
    friend int operator-(const Integer& integer, int v);


    friend const Integer& operator++(Integer& integer);
    friend const Integer operator++(Integer& integer, int);
    friend const Integer& operator--(Integer& integer);
    friend const Integer operator--(Integer& integer, int);
};

#endif // !INTEGER_INCLUDE_GUARD__H