/**
 *
 *  @file FontMetrics.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTMETRICS_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTMETRICS_HPP_INCLUDED

#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/Units.hpp>

#include <string_view>
#include <string>
#include <vector>

namespace rixlib::pdf::writer
{
  /**
   * @brief A wrapped text line.
   *
   * The last_line flag is used by justified text rendering so the last line of
   * a paragraph is not stretched.
   */
  struct WrappedLine
  {
    std::string text;
    bool last_line = false;
  };

  /**
   * @brief Return the approximate width of a character.
   *
   * The value is expressed in 1/1000 font units, matching standard PDF font
   * metrics.
   *
   * @param font Standard PDF font.
   * @param character Character value.
   * @return Character width in 1/1000 font units.
   */
  [[nodiscard]] int character_width(
      Font font,
      unsigned char character) noexcept;

  /**
   * @brief Compute the width of text in PDF points.
   *
   * @param text Text value.
   * @param font Standard PDF font.
   * @param size Font size in PDF points.
   * @return Text width in PDF points.
   */
  [[nodiscard]] Point text_width(
      std::string_view text,
      Font font,
      Point size) noexcept;

  /**
   * @brief Wrap text to fit inside a maximum width.
   *
   * Existing newline characters are treated as paragraph breaks.
   *
   * @param text Text value.
   * @param font Standard PDF font.
   * @param size Font size in PDF points.
   * @param max_width Maximum line width in PDF points.
   * @return Wrapped lines.
   */
  [[nodiscard]] std::vector<WrappedLine> wrap_text(
      std::string_view text,
      Font font,
      Point size,
      Point max_width);

} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTMETRICS_HPP_INCLUDED
