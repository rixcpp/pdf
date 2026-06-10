/**
 *
 *  @file Align.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ALIGN_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ALIGN_HPP_INCLUDED

#include <cstdint>
#include <string_view>

namespace rixlib::pdf
{
  /**
   * @brief Horizontal alignment mode for text and table cells.
   */
  enum class Align : std::uint8_t
  {
    Left,
    Center,
    Right,
    Justify
  };

  /**
   * @brief Convert an alignment value to a stable string.
   *
   * @param align Alignment value.
   * @return Stable string representation.
   */
  [[nodiscard]] constexpr std::string_view to_string(Align align) noexcept
  {
    switch (align)
    {
    case Align::Left:
      return "Left";
    case Align::Center:
      return "Center";
    case Align::Right:
      return "Right";
    case Align::Justify:
      return "Justify";
    }

    return "Left";
  }

  /**
   * @brief Return true when the alignment is left.
   *
   * @param align Alignment value.
   * @return true if align is Align::Left.
   */
  [[nodiscard]] constexpr bool is_left(Align align) noexcept
  {
    return align == Align::Left;
  }

  /**
   * @brief Return true when the alignment is centered.
   *
   * @param align Alignment value.
   * @return true if align is Align::Center.
   */
  [[nodiscard]] constexpr bool is_center(Align align) noexcept
  {
    return align == Align::Center;
  }

  /**
   * @brief Return true when the alignment is right.
   *
   * @param align Alignment value.
   * @return true if align is Align::Right.
   */
  [[nodiscard]] constexpr bool is_right(Align align) noexcept
  {
    return align == Align::Right;
  }

  /**
   * @brief Return true when the alignment is justified.
   *
   * @param align Alignment value.
   * @return true if align is Align::Justify.
   */
  [[nodiscard]] constexpr bool is_justify(Align align) noexcept
  {
    return align == Align::Justify;
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ALIGN_HPP_INCLUDED
