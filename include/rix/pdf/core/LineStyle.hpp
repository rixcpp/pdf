/**
 *
 *  @file LineStyle.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_LINESTYLE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_LINESTYLE_HPP_INCLUDED

#include <cstdint>
#include <string_view>

namespace rixlib::pdf
{
  /**
   * @brief Stroke pattern used when drawing lines and borders.
   */
  enum class LineStyle : std::uint8_t
  {
    Solid,
    Dashed,
    Dotted
  };

  /**
   * @brief Convert a line style to a stable string.
   *
   * @param style Line style.
   * @return Stable string representation.
   */
  [[nodiscard]] constexpr std::string_view to_string(LineStyle style) noexcept
  {
    switch (style)
    {
    case LineStyle::Solid:
      return "Solid";
    case LineStyle::Dashed:
      return "Dashed";
    case LineStyle::Dotted:
      return "Dotted";
    }

    return "Solid";
  }

  /**
   * @brief Return true when the line style is solid.
   *
   * @param style Line style.
   * @return true if style is LineStyle::Solid.
   */
  [[nodiscard]] constexpr bool is_solid(LineStyle style) noexcept
  {
    return style == LineStyle::Solid;
  }

  /**
   * @brief Return true when the line style is dashed.
   *
   * @param style Line style.
   * @return true if style is LineStyle::Dashed.
   */
  [[nodiscard]] constexpr bool is_dashed(LineStyle style) noexcept
  {
    return style == LineStyle::Dashed;
  }

  /**
   * @brief Return true when the line style is dotted.
   *
   * @param style Line style.
   * @return true if style is LineStyle::Dotted.
   */
  [[nodiscard]] constexpr bool is_dotted(LineStyle style) noexcept
  {
    return style == LineStyle::Dotted;
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_LINESTYLE_HPP_INCLUDED
