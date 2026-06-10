/**
 *
 *  @file Escape.cpp
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

#include <rix/pdf/writer/Escape.hpp>

#include <cctype>
#include <iomanip>
#include <sstream>

namespace rixlib::pdf::writer
{
  namespace
  {
    [[nodiscard]] char hex_digit(unsigned value) noexcept
    {
      return static_cast<char>(value < 10U ? ('0' + value) : ('A' + (value - 10U)));
    }

    [[nodiscard]] std::string hex_escape(unsigned char value)
    {
      std::string out;
      out.reserve(3);

      out.push_back('#');
      out.push_back(hex_digit((value >> 4U) & 0x0FU));
      out.push_back(hex_digit(value & 0x0FU));

      return out;
    }

    [[nodiscard]] bool is_regular_name_char(unsigned char value) noexcept
    {
      if (value <= 0x20 || value >= 0x7F)
      {
        return false;
      }

      switch (value)
      {
      case '#':
      case '%':
      case '(':
      case ')':
      case '<':
      case '>':
      case '[':
      case ']':
      case '{':
      case '}':
      case '/':
        return false;
      default:
        return true;
      }
    }
  } // namespace

  std::string escape_literal_string(std::string_view value)
  {
    std::string out;
    out.reserve(value.size());

    for (unsigned char ch : value)
    {
      switch (ch)
      {
      case '(':
        out += "\\(";
        break;
      case ')':
        out += "\\)";
        break;
      case '\\':
        out += "\\\\";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\r':
        out += "\\r";
        break;
      case '\t':
        out += "\\t";
        break;
      case '\b':
        out += "\\b";
        break;
      case '\f':
        out += "\\f";
        break;
      default:
        out.push_back(static_cast<char>(ch));
        break;
      }
    }

    return out;
  }

  std::string literal_string(std::string_view value)
  {
    std::string out;
    out.reserve(value.size() + 2);

    out.push_back('(');
    out += escape_literal_string(value);
    out.push_back(')');

    return out;
  }

  std::string escape_name(std::string_view value)
  {
    std::string out;
    out.reserve(value.size());

    for (unsigned char ch : value)
    {
      if (is_regular_name_char(ch))
      {
        out.push_back(static_cast<char>(ch));
      }
      else
      {
        out += hex_escape(ch);
      }
    }

    return out;
  }

  std::string name(std::string_view value)
  {
    std::string out;
    out.reserve(value.size() + 1);

    out.push_back('/');
    out += escape_name(value);

    return out;
  }
} // namespace rixlib::pdf::writer
