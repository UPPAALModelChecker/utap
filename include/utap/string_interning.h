#pragma once
#include <algorithm>
#include <string>
#include <vector>

namespace UTAP {

/**
 * Used to highlight that an integer is an index into a string container.
 * Nothing is exposed to the user as all operations should go through a StringContainer
 */
class StringIndex
{
    friend class StringInternedContainer;

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
class StringInternedContainer
{
public:
    const std::vector<std::string>& get_strings() const { return strings; }
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
    std::vector<std::string> strings;
};

}  // namespace UTAP