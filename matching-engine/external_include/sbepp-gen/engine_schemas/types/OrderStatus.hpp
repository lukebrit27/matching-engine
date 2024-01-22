// SPDX-License-Identifier: MIT
// Copyright (c) 2023, Oleksandr Koval

// This file was generated by sbeppc 1.1.0
#pragma once

#include <sbepp/sbepp.hpp>

SBEPP_WARNINGS_OFF();

#include "../schema/schema.hpp"


namespace engine_schemas
{
namespace detail
{
namespace types
{

enum class enum_3 : ::std::uint8_t
{
    newo = 0,
    cancelled = 1,
    partiallyFilled = 2,
    filled = 3
};


inline SBEPP_CPP14_CONSTEXPR const char*
    tag_invoke(
        ::sbepp::detail::enum_to_str_tag,
        enum_3 e) noexcept
{
    switch(e)
    {
    
    case enum_3::newo:
        return "newo";

    case enum_3::cancelled:
        return "cancelled";

    case enum_3::partiallyFilled:
        return "partiallyFilled";

    case enum_3::filled:
        return "filled";

    default:
        return nullptr;
    }
}


} // namespace types
} // namespace detail

namespace types
{
using OrderStatus = ::engine_schemas::detail::types::enum_3;
} // namespace types
} // namespace engine_schemas

namespace sbepp
{

template<>
class enum_traits<::engine_schemas::schema::types::OrderStatus>
{
public:
    static constexpr const char* name() noexcept
    {
        return "OrderStatus";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }

    using encoding_type = ::std::uint8_t;
    
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    
    using value_type = ::engine_schemas::types::OrderStatus;
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderStatus::newo>
{
public:
    static constexpr const char* name() noexcept
    {
        return "newo";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderStatus value() noexcept
    {
        return ::engine_schemas::types::OrderStatus::newo;
    }
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderStatus::cancelled>
{
public:
    static constexpr const char* name() noexcept
    {
        return "cancelled";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderStatus value() noexcept
    {
        return ::engine_schemas::types::OrderStatus::cancelled;
    }
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderStatus::partiallyFilled>
{
public:
    static constexpr const char* name() noexcept
    {
        return "partiallyFilled";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderStatus value() noexcept
    {
        return ::engine_schemas::types::OrderStatus::partiallyFilled;
    }
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderStatus::filled>
{
public:
    static constexpr const char* name() noexcept
    {
        return "filled";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderStatus value() noexcept
    {
        return ::engine_schemas::types::OrderStatus::filled;
    }
};

}  // namespace sbepp

SBEPP_WARNINGS_ON();