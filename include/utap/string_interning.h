#pragma once
#include <algorithm>
#include <list>
#include <string>

namespace UTAP {

/**
 * Special type used distinquish a int from a string index, also stores a reference to string for ease of use
 */
class StringIndex
{
    friend class InternedStringVector;

    std::string_view string;
    int interned_index;

    StringIndex(std::string_view str, int index): string{str}, interned_index{index} {}

public:
    bool operator==(const StringIndex& other) const { return interned_index == other.interned_index; }

    std::string_view str() const { return string; }
    int index() const { return interned_index; }
};

/**
 * Intern strings to reduce memory footprints
 */
class InternedStringVector
{
public:
    const std::list<std::string>& get_strings() const { return strings; }
    StringIndex add_string_if_new(std::string&& string)
    {
        auto it = std::find(std::begin(strings), std::end(strings), string);
        if (it == std::end(strings)) {
            strings.emplace_back(std::move(string));
            return StringIndex(strings.back(), strings.size() - 1);
        } else {
            return StringIndex(*it, std::distance(std::begin(strings), it));
        }
    }

private:
    // Strings must be constant and memory stable because StringIndex references the std::string data directly
    // Using list is nessecary because std::string are not moved in C++ versions below c++17
    std::list<std::string> strings;
};

}  // namespace UTAP