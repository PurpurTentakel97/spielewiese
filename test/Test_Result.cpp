//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#include <spielewiese/Result.hpp>
#include <gtest/gtest.h>

enum class Error {
    default_error,
    other_error,
};

class Value {
private:
    int m_value;

public:
    explicit Value(int value) : m_value{ value } { }
    Value() = default;

    [[nodiscard]] int value() const {
        return m_value;
    }

    friend bool operator==(Value const& lhs, Value const& rhs) {
        return lhs.m_value == rhs.m_value;
    }
};


TEST(Result, OK) {
    spw::Result<Value, Error> const result = Value(1);

    ASSERT_TRUE(result.ok());
    ASSERT_FALSE(result.err());
    ASSERT_EQ(result.unwrap(), Value(1));
    ASSERT_THROW([result]() { [[maybe_unused]] auto const r = result.unwrap_err(); }(), spw::BadResultAccessError);
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(1));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(1));
    ASSERT_EQ(result.unwrap_or_default(), Value(1));
}

TEST(Result, Error) {
    spw::Result<Value, Error> constexpr result = spw::Err{ Error::default_error };

    ASSERT_TRUE(result.err());
    ASSERT_FALSE(result.ok());
    ASSERT_EQ(result.unwrap_err(), Error::default_error);
    ASSERT_THROW([result]() { [[maybe_unused]] auto const r = result.unwrap(); }(), spw::BadResultAccessResult);
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(2));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(2));
    ASSERT_EQ(result.unwrap_or_default(), Value(0));
}

TEST(Result, OK_Same_Type) {
    spw::Result<Value, Value> const result = Value(1);

    ASSERT_TRUE(result.ok());
    ASSERT_FALSE(result.err());
    ASSERT_EQ(result.unwrap(), Value(1));
    ASSERT_THROW([result]() { [[maybe_unused]] auto const r = result.unwrap_err(); }(), spw::BadResultAccessError);
    ASSERT_EQ(result.unwrap_or(Value(2)), Value(1));
    ASSERT_EQ(result.unwarp_or_else([]() { return Value(2); }), Value(1));
    ASSERT_EQ(result.unwrap_or_default(), Value(1));
}

TEST(Result, Error_Same_Type) {
    spw::Result<Error, Error> constexpr result = spw::Err{ Error::default_error };

    ASSERT_TRUE(result.err());
    ASSERT_FALSE(result.ok());
    ASSERT_EQ(result.unwrap_err(), Error::default_error);
    ASSERT_THROW([result]() { [[maybe_unused]] auto const r = result.unwrap(); }(), spw::BadResultAccessResult);
    ASSERT_EQ(result.unwrap_or(Error::other_error), Error::other_error);
    ASSERT_EQ(result.unwarp_or_else([]() { return Error::other_error; }), Error::other_error);
    ASSERT_EQ(result.unwrap_or_default(), Error::default_error);
}
