//
// Purpur Tentakel
// cpp 23
// 11.05.24
//

#pragma once
#include <concepts>
#include <stdexcept>
#include <variant>

namespace spw {
    class BadResultAccess : public std::logic_error {
    public:
        explicit BadResultAccess(char const* message) : std::logic_error{ message } { }
    };

    class BadResultAccessResult final : public BadResultAccess {
    public:
        BadResultAccessResult() : BadResultAccess{ "trying to access result of bad result" } { }
    };

    class BadResultAccessError final : public BadResultAccess {
    public:
        BadResultAccessError() : BadResultAccess{ "trying to access error of good result" } { }
    };


    template<typename E>
    struct Err final {
    private:
        E m_value;

    public:
        explicit constexpr Err(E value) : m_value{ std::move(value) } { }

        [[nodiscard]] constexpr E value() const {
            return m_value;
        }
    };

    template<typename T, typename E>
    class Result final {
    private:
        std::variant<T, E> m_value;

    public:
        constexpr Result(T&& value) : m_value{ std::in_place_index<0>, std::forward<T>(value) } { }
        constexpr Result(Err<E>&& value) : m_value{ std::in_place_index<1>, std::forward<E>(value.value()) } { }

        [[nodiscard]] constexpr bool ok() const {
            return m_value.index() == 0;
        }

        [[nodiscard]] constexpr bool err() const {
            return not ok();
        }

        [[nodiscard]] constexpr T const& unwrap() const {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw BadResultAccessResult();
        }

        [[nodiscard]] constexpr T& unwrap() {
            if (ok()) {
                return std::get<0>(m_value);
            }
            throw BadResultAccessResult();
        }

        [[nodiscard]] constexpr E const& unwrap_err() const {
            if (err()) {
                return std::get<1>(m_value);
            }
            throw BadResultAccessError();
        }

        [[nodiscard]] constexpr E& unwrap_err() {
            if (err()) {
                return std::get<1>(m_value);
            }
            throw BadResultAccessError();
        }

        [[nodiscard]] constexpr T const& unwrap_or(T const& other) const {
            return ok() ? unwrap() : other;
        }

        [[nodiscard]] constexpr T& unwrap_or(T const& other) {
            return ok() ? unwrap() : other;
        }

        template<std::invocable F>
        [[nodiscard]] constexpr T unwarp_or_else(F const& func) const
            requires(std::copyable<T> or std::movable<T>)
        {
            return ok() ? unwrap() : func();
        }

        [[nodiscard]] constexpr T unwrap_or_default() const
            requires(std::default_initializable<T>)
        {
            return ok() ? unwrap() : T();
        }
    };
} // namespace cpt
