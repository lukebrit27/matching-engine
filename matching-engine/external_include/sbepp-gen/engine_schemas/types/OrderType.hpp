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
    limit = 0,
    market = 1
};


inline SBEPP_CPP14_CONSTEXPR const char*
    tag_invoke(
        ::sbepp::detail::enum_to_str_tag,
        enum_3 e) noexcept
{
    switch(e)
    {
    
    case enum_3::limit:
        return "limit";

    case enum_3::market:
        return "market";

    default:
        return nullptr;
    }
}


} // namespace types
} // namespace detail

namespace types
{
using OrderType = ::engine_schemas::detail::types::enum_3;
} // namespace types
} // namespace engine_schemas

namespace sbepp
{

template<>
class enum_traits<::engine_schemas::schema::types::OrderType>
{
public:
    static constexpr const char* name() noexcept
    {
        return "OrderType";
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

    
    using value_type = ::engine_schemas::types::OrderType;
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderType::limit>
{
public:
    static constexpr const char* name() noexcept
    {
        return "limit";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderType value() noexcept
    {
        return ::engine_schemas::types::OrderType::limit;
    }
};

template<>
class enum_value_traits<::engine_schemas::schema::types::OrderType::market>
{
public:
    static constexpr const char* name() noexcept
    {
        return "market";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    

    static constexpr ::engine_schemas::types::OrderType value() noexcept
    {
        return ::engine_schemas::types::OrderType::market;
    }
};

}  // namespace sbepp

SBEPP_WARNINGS_ON();
