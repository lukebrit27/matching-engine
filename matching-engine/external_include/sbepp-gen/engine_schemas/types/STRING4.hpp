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

template<typename Byte>
using type_3 = ::sbepp::detail::static_array_ref<
    Byte, char, 4>;

} // namespace types
} // namespace detail

namespace types
{

    template<typename Byte>
    using STRING4 = ::engine_schemas::detail::types::type_3<Byte>;

} // namespace types
} // namespace engine_schemas

namespace sbepp
{

template<>
class type_traits<::engine_schemas::schema::types::STRING4>
{
public:
    static constexpr const char* name() noexcept
    {
        return "STRING4";
    }

    static constexpr const char* description() noexcept
    {
        return "";
    }

    static constexpr field_presence presence() noexcept
    {
        return ::sbepp::field_presence::required;
    }

    using primitive_type = char;
    
    
    static constexpr length_t length() noexcept
    {
        return 4;
    }
    
    
    
    static constexpr const char* semantic_type() noexcept
    {
        return "";
    }
    
    static constexpr version_t since_version() noexcept
    {
        return 0;
    }

    static constexpr const char* character_encoding() noexcept
    {
        return "";
    }

    
    
    template<typename Byte>
    using value_type = ::engine_schemas::types::STRING4<Byte>;

};

}  // namespace sbepp

SBEPP_WARNINGS_ON();
