/**
 *
 *  @file FloatFormat.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FLOATFORMAT_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FLOATFORMAT_HPP_INCLUDED

#include <rix/pdf/core/Units.hpp>

#include <string>

namespace rixlib::pdf::writer
{
  /**
   * @brief Format a floating-point value for PDF content streams.
   *
   * The output is compact, stable, and avoids unnecessary trailing zeros.
   *
   * @param value Floating-point value.
   * @return Formatted PDF number.
   */
  [[nodiscard]] std::string format_float(float value);

  /**
   * @brief Format a PDF point value for PDF content streams.
   *
   * @param value Point value.
   * @return Formatted PDF number.
   */
  [[nodiscard]] std::string format_point(Point value);

} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FLOATFORMAT_HPP_INCLUDED
