#pragma once

#include <array>
#include <type_traits>
#include <utility>
#include <stdexcept>





template<typename K, typename V, size_t count>
class CexprMap {
public:
    using key_type = K;
    using value_type = V;

    template<class... Entries>
    constexpr CexprMap(Entries&&... entries) : values({entries...}) {
        verify_no_duplicates();
    }

    /**
     * Entry count.
     */
    constexpr size_t size() const {
        return count;
    }

    /**
     * Is the key in the map?
     */
    constexpr bool contains(const K &key) const {
        return find(key) != values.end();
    }

    /**
     * Get a key's value
     */
    constexpr const V &get(const K &key) const {
        auto it = find(key);
        if (it == values.end())
            throw std::out_of_range("cexpr_map: key not found");
        return it->second;
    }

    /**
     * Get a key's value by map[key].
     */
    constexpr const V &operator [](const K &key) const {
        return get(key);
    }

private:
    /**
     * Checks if keys are duplicated.
     * Throws std::invalid_argument on duplicate key.
     */
    constexpr void verify_no_duplicates() const {
        for (size_t i = 0; i < values.size(); ++i) {
            for (size_t j = i + 1; j < values.size(); ++j) {
                if (values[i].first == values[j].first)
                    throw std::invalid_argument("cexpr_map: duplicate keys not allowed");
            }
        }
    }

    /**
     * Returns the iterator matching key from the array.
     *  - `values.end()` if the key is not found.
     */
    constexpr auto find(const K &key) const {
        auto it = values.begin();
        while (it != values.end() && it->first != key)
            ++it;
        return it;
    }

    /**
     * The entries associated with this map.
     */
    std::array<std::pair<K, V>, count> values;
};

template<typename K, typename V, typename... Entries>
constexpr auto create_cexpr_map(Entries&&... entries) {
    return CexprMap<K, V, sizeof...(entries)>{entries...};
}

template<typename Entry, typename... Rest>
requires std::conjunction_v<std::is_same<Entry, Rest>...>
CexprMap(Entry entry, Rest&&... rest) -> CexprMap<typename Entry::first_type, typename Entry::second_type, 1 + sizeof...(rest)>;
