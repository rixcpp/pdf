/**
 *
 *  @file FloatFormat.cpp
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

#include <rix/pdf/writer/FloatFormat.hpp>

#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>

namespace rixlib::pdf::writer
{
  namespace
  {
    [[nodiscard]] bool close_to_zero(float value) noexcept
    {
      return std::fabs(value) < 0.00005F;
    }
  } // namespace

  std::string format_float(float value)
  {
    if (!std::isfinite(value) || close_to_zero(value))
    {
      return "0";
    }

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(4) << value;

    std::string out = stream.str();

    const auto dot = out.find('.');

    if (dot == std::string::npos)
    {
      return out;
    }

    while (!out.empty() && out.back() == '0')
    {
      out.pop_back();
    }

    if (!out.empty() && out.back() == '.')
    {
      out.pop_back();
    }

    if (out == "-0")
    {
      return "0";
    }

    return out;
  }

  std::string format_point(Point value)
  {
    return format_float(value);
  }
} // namespace rixlib::pdf::writer
