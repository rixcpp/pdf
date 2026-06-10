/**
 *
 *  @file Version.cpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2026, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/rixcpp/pdf
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Rix
 *
 */

#include <rix/pdf/Version.hpp>

namespace rixlib::pdf
{
  namespace
  {
    constexpr int VERSION_MAJOR = 0;
    constexpr int VERSION_MINOR = 1;
    constexpr int VERSION_PATCH = 0;
  } // namespace

  std::string version()
  {
    return "0.1.0";
  }

  int version_major() noexcept
  {
    return VERSION_MAJOR;
  }

  int version_minor() noexcept
  {
    return VERSION_MINOR;
  }

  int version_patch() noexcept
  {
    return VERSION_PATCH;
  }

  int version_number() noexcept
  {
    return (VERSION_MAJOR * 10000) +
           (VERSION_MINOR * 100) +
           VERSION_PATCH;
  }
} // namespace rixlib::pdf
