/**============================================================================
Name        : Database.h
Created on  : 29.12.2023
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Database modules implementation
============================================================================**/

#ifndef BOOKINGSERVICE_DATABASE_H
#define BOOKINGSERVICE_DATABASE_H

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>
#include <concepts>

namespace DB
{
    template<typename T>
    struct TableEntry
    {
        std::string name;
        size_t id { 0 };

        explicit TableEntry(std::string name) : name{std::move(name)} {
            // First entry shall have ID = 1 not zero
            id = ++uniqueEntryId;
        }

        template<typename Type>
        friend bool operator==(const TableEntry<Type> &, const TableEntry<Type> &);

    private:

        static inline size_t uniqueEntryId {0};
    };

    template <typename Ty>
    concept TableEntryType = std::derived_from<Ty, TableEntry<Ty>>;

    template<TableEntryType T>
    class Table
    {
        using EntryType = T;
        using EntryPointer = EntryType*;
        using SharedEntry = std::shared_ptr<EntryType>;

        // static_assert(!std::is_same_v<EntryType, void>, "ERROR: EntryType type can not be void");

        std::unordered_map<size_t, SharedEntry> entryTable{};
        std::unordered_map<std::string, SharedEntry> tableByName{};

    public:

        void addEntry(const std::string &name)
        {
            SharedEntry objPtr = std::make_shared<EntryType>(name);
            entryTable.emplace(objPtr->id, objPtr);
            tableByName.emplace(objPtr->name, std::move(objPtr));
        }

        // TODO: Clients of the function should not be involved in managing the lifecycle of the stored object:
        //       therefore returning *T instead of std::shared_ptr<T>
        std::optional<EntryPointer> findEntryName(const std::string &name) const noexcept {
            if (const auto it = tableByName.find(name); tableByName.end() != it)
                return std::make_optional<EntryPointer>(it->second.get());
            return std::nullopt;
        }

        // TODO: Clients of the function should not be involved in managing the lifecycle of the stored object:
        //       therefore returning *T instead of std::shared_ptr<T>
        std::optional<EntryPointer> findEntryByID(size_t id) const noexcept {
            if (const auto it = entryTable.find(id); entryTable.end() != it)
                return std::make_optional<EntryPointer>(it->second.get());
            return std::nullopt;
        }

        // TODO: Clients of the function should not be involved in managing the lifecycle of the stored object:
        //       therefore returning *T instead of std::shared_ptr<T>
        [[nodiscard]]
        std::vector<EntryPointer> getAllEntries() const {
            std::vector<EntryPointer> allRecords;
            allRecords.reserve(entryTable.size());
            for (const auto &[id, obj]: entryTable)
                allRecords.push_back(obj.get());
            return allRecords;
        }
    };
}

#endif //BOOKINGSERVICE_DATABASE_H
