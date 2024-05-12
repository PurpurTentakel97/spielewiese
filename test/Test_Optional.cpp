//
// Purpur Tentakel
// cpp 23
// 12.05.24
//


#include <spielewiese/Optional.hpp>
#include <gtest/gtest.h>

enum class Entry {
    default_entry,
    other_entry,
};

TEST(Optional, OK) {
    spw::Optional<Entry> constexpr optional = Entry::default_entry;

    ASSERT_TRUE(optional.ok());
    ASSERT_EQ(optional.unwrap(), Entry::default_entry);
    ASSERT_EQ(optional.unwrap_or(Entry::other_entry), Entry::default_entry);
    ASSERT_EQ(optional.unwrap_or_else([]() { return Entry::other_entry; }), Entry::default_entry);
    ASSERT_EQ(optional.unwrap_or_default(), Entry::default_entry);
}

TEST(Optional, Empty) {
    spw::Optional<Entry> constexpr optional = {};

    ASSERT_FALSE(optional.ok());
    ASSERT_THROW([optional]() { [[maybe_unused]] auto const o = optional.unwrap(); }(), spw::BadOptionalAccess);
    ASSERT_EQ(optional.unwrap_or(Entry::other_entry), Entry::other_entry);
    ASSERT_EQ(optional.unwrap_or_else([]() { return Entry::other_entry; }), Entry::other_entry);
    ASSERT_EQ(optional.unwrap_or_default(), Entry::default_entry);
}
