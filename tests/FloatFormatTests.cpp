/**
 *
 *  @file FloatFormatTests.cpp
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

#include <cassert>
#include <limits>

int main()
{
  using namespace rixlib::pdf;
  using namespace rixlib::pdf::writer;

  assert(format_float(0.0F) == "0");
  assert(format_float(-0.0F) == "0");
  assert(format_float(0.000001F) == "0");
  assert(format_float(-0.000001F) == "0");

  assert(format_float(1.0F) == "1");
  assert(format_float(-1.0F) == "-1");

  assert(format_float(1.25F) == "1.25");
  assert(format_float(-1.25F) == "-1.25");

  assert(format_float(12.3400F) == "12.34");
  assert(format_float(12.3456F) == "12.3456");

  assert(format_float(std::numeric_limits<float>::infinity()) == "0");
  assert(format_float(-std::numeric_limits<float>::infinity()) == "0");
  assert(format_float(std::numeric_limits<float>::quiet_NaN()) == "0");

  assert(format_point(72.0F) == "72");
  assert(format_point(inches(1.0F)) == "72");

  return 0;
}
