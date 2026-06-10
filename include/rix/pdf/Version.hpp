/**
 *
 *  @file Version.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_VERSION_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_VERSION_HPP_INCLUDED

#include <string>

namespace rixlib::pdf
{
  /**
   * @brief Return the rix/pdf package version string.
   *
   * @return Package version string.
   */
  [[nodiscard]] std::string version();

  /**
   * @brief Return the rix/pdf package major version.
   *
   * @return Major version number.
   */
  [[nodiscard]] int version_major() noexcept;

  /**
   * @brief Return the rix/pdf package minor version.
   *
   * @return Minor version number.
   */
  [[nodiscard]] int version_minor() noexcept;

  /**
   * @brief Return the rix/pdf package patch version.
   *
   * @return Patch version number.
   */
  [[nodiscard]] int version_patch() noexcept;

  /**
   * @brief Return the encoded rix/pdf package version number.
   *
   * The encoded format is:
   *
   * @code
   * major * 10000 + minor * 100 + patch
   * @endcode
   *
   * @return Encoded version number.
   */
  [[nodiscard]] int version_number() noexcept;
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_VERSION_HPP_INCLUDED
