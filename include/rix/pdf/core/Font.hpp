/**
 *
 *  @file Font.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_FONT_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_FONT_HPP_INCLUDED

#include <cstdint>
#include <string_view>

namespace rixlib::pdf
{
  /**
   * @brief Standard PDF font family.
   */
  enum class FontFamily : std::uint8_t
  {
    Helvetica,
    Times,
    Courier,
    Symbol,
    ZapfDingbats
  };

  /**
   * @brief Standard PDF font style.
   */
  enum class FontStyle : std::uint8_t
  {
    Regular,
    Bold,
    Italic,
    BoldItalic
  };

  /**
   * @brief Standard PDF Type 1 font.
   *
   * PDF readers are expected to provide the 14 standard fonts, so these fonts
   * can be referenced without embedding external font files.
   */
  enum class Font : std::uint8_t
  {
    Helvetica,
    HelveticaBold,
    HelveticaOblique,
    HelveticaBoldOblique,

    Times,
    TimesBold,
    TimesItalic,
    TimesBoldItalic,

    Courier,
    CourierBold,
    CourierOblique,
    CourierBoldOblique,

    Symbol,
    ZapfDingbats
  };

  /**
   * @brief Return a standard font from a family and style.
   *
   * Symbol and ZapfDingbats ignore style because PDF exposes them as single
   * standard fonts.
   *
   * @param family Font family.
   * @param style Font style.
   * @return Standard PDF font.
   */
  [[nodiscard]] Font make_font(
      FontFamily family,
      FontStyle style = FontStyle::Regular) noexcept;

  /**
   * @brief Return the PDF BaseFont name for a standard font.
   *
   * @param font Standard PDF font.
   * @return PDF BaseFont name.
   */
  [[nodiscard]] std::string_view base_font_name(Font font) noexcept;

  /**
   * @brief Return the public family name for a standard font.
   *
   * @param font Standard PDF font.
   * @return Font family name.
   */
  [[nodiscard]] std::string_view family_name(Font font) noexcept;

  /**
   * @brief Return the family of a standard font.
   *
   * @param font Standard PDF font.
   * @return Font family.
   */
  [[nodiscard]] FontFamily font_family(Font font) noexcept;

  /**
   * @brief Return the style of a standard font.
   *
   * @param font Standard PDF font.
   * @return Font style.
   */
  [[nodiscard]] FontStyle font_style(Font font) noexcept;

  /**
   * @brief Return true when the font is bold.
   *
   * @param font Standard PDF font.
   * @return true if the font uses a bold style.
   */
  [[nodiscard]] bool is_bold(Font font) noexcept;

  /**
   * @brief Return true when the font is italic or oblique.
   *
   * @param font Standard PDF font.
   * @return true if the font uses an italic-style variant.
   */
  [[nodiscard]] bool is_italic(Font font) noexcept;

  /**
   * @brief Return true when the font is monospaced.
   *
   * @param font Standard PDF font.
   * @return true if the font belongs to the Courier family.
   */
  [[nodiscard]] bool is_monospaced(Font font) noexcept;

  /**
   * @brief Return true when the font belongs to the 14 standard PDF fonts.
   *
   * @param font Standard PDF font.
   * @return true for all values of Font.
   */
  [[nodiscard]] bool is_standard_font(Font font) noexcept;

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_FONT_HPP_INCLUDED
