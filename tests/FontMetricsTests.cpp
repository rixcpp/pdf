/**
 *
 *  @file FontMetricsTests.cpp
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

#include <rix/pdf/writer/FontMetrics.hpp>

#include <cassert>
#include <cmath>

namespace
{
  bool near(float left, float right)
  {
    return std::fabs(left - right) < 0.01F;
  }
}

int main()
{
  using namespace rixlib::pdf;
  using namespace rixlib::pdf::writer;

  assert(character_width(Font::Helvetica, 'A') == 667);
  assert(character_width(Font::HelveticaBold, 'A') == 722);
  assert(character_width(Font::Courier, 'A') == 600);
  assert(character_width(Font::Times, 'A') == 722);
  assert(character_width(Font::Helvetica, '\n') == 600);

  assert(near(text_width("A", Font::Helvetica, 10.0F), 6.67F));
  assert(near(text_width("AA", Font::Helvetica, 10.0F), 13.34F));
  assert(near(text_width("A", Font::Courier, 10.0F), 6.0F));

  auto simple = wrap_text(
      "hello world",
      Font::Helvetica,
      12.0F,
      200.0F);

  assert(simple.size() == 1);
  assert(simple[0].text == "hello world");
  assert(simple[0].last_line);

  auto wrapped = wrap_text(
      "hello world from rix pdf",
      Font::Helvetica,
      12.0F,
      40.0F);

  assert(wrapped.size() > 1);
  assert(wrapped.back().last_line);

  auto newline = wrap_text(
      "first\nsecond",
      Font::Helvetica,
      12.0F,
      200.0F);

  assert(newline.size() == 2);
  assert(newline[0].text == "first");
  assert(newline[0].last_line);
  assert(newline[1].text == "second");
  assert(newline[1].last_line);

  auto empty = wrap_text(
      "",
      Font::Helvetica,
      12.0F,
      200.0F);

  assert(empty.empty());

  auto no_width = wrap_text(
      "hello world",
      Font::Helvetica,
      12.0F,
      0.0F);

  assert(no_width.size() == 1);
  assert(no_width[0].text == "hello world");
  assert(no_width[0].last_line);

  return 0;
}
