/**============================================================================
Name        : Database.cpp
Created on  : 29.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Database modules implementation
============================================================================**/

#include "Database.h"

namespace DB
{
    template<typename T>
    bool operator==(const TableEntry<T> &left, const TableEntry<T> &right) {
        return left.id == right.id;
    }
}