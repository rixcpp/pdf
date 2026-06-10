/**
 *
 *  @file Escape.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_ESCAPE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_ESCAPE_HPP_INCLUDED

#include <string>
#include <string_view>

namespace rixlib::pdf::writer
{
  /**
   * @brief Escape a string for a PDF literal string.
   *
   * This escapes characters that have special meaning inside PDF literal
   * strings, including parentheses, backslashes, and common control
   * characters.
   *
   * @param value Input string.
   * @return Escaped PDF string content without surrounding parentheses.
   */
  [[nodiscard]] std::string escape_literal_string(std::string_view value);

  /**
   * @brief Wrap a string as a PDF literal string.
   *
   * This returns the escaped value surrounded by parentheses.
   *
   * @param value Input string.
   * @return PDF literal string.
   */
  [[nodiscard]] std::string literal_string(std::string_view value);

  /**
   * @brief Escape a PDF name value.
   *
   * PDF names are introduced by slash in the writer. This function returns
   * only the escaped name content without the leading slash.
   *
   * @param value Input name.
   * @return Escaped PDF name content.
   */
  [[nodiscard]] std::string escape_name(std::string_view value);

  /**
   * @brief Wrap a value as a PDF name.
   *
   * This returns the escaped name with a leading slash.
   *
   * @param value Input name.
   * @return PDF name.
   */
  [[nodiscard]] std::string name(std::string_view value);

} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_ESCAPE_HPP_INCLUDED
