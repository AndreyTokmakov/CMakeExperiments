//============================================================================
// Name        : Tests.cpp
// Created on  : 15.09.2021
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Tests C++ project
//============================================================================

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <tuple>
#include <cmath>

#include <thread>
#include <future>

#include <mutex>
#include <atomic>

#include <cmath>
#include <numeric>
#include <numbers>
#include <ostream>

#include <vector>
#include <any>
#include <list>
#include <map>
#include <algorithm>
#include <array>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <span>


#include <concepts>

using namespace std;

void f(int a, int b)
{
    std::cout << a - b;
}

struct E
{
    E() { cout << "E\n"; }
    E(const E&) { cout << "E(E&)\n"; }
    ~E() { cout << "~E\n"; }
};

struct A {
    A() { cout << "A\n"; }
    virtual ~A() { cout << "~A\n"; }
};

struct C {
    C() { cout << "C\n"; }
    ~C() { cout << "~C\n"; }
};

struct D {
    D() { cout << "D\n"; }
    ~D() { cout << "~D\n"; }
};

struct B: A {
    D d;

    B()
    {
        try {
            C c;
            throw E();
        } catch (E e) {
            cout << "catch\n";
        }
        throw E();
    }

    ~B()
    {
        cout << "~B\n";
    }
};

int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);
    std::cout << "Application started" << std::endl;

    try {
        B b;
    } catch (const E&) {
    }

    return EXIT_SUCCESS;
}

