/**
 *
 *  @file ColorTests.cpp
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

#include <rix/pdf/core/Color.hpp>

#include <cassert>

int main()
{
  using namespace rixlib::pdf;

  Color black;

  assert(black.red() == 0.0F);
  assert(black.green() == 0.0F);
  assert(black.blue() == 0.0F);

  Color clamped{-1.0F, 0.5F, 2.0F};

  assert(clamped.red() == 0.0F);
  assert(clamped.green() == 0.5F);
  assert(clamped.blue() == 1.0F);

  clamped.set_red(0.25F);
  clamped.set_green(-10.0F);
  clamped.set_blue(10.0F);

  assert(clamped.red() == 0.25F);
  assert(clamped.green() == 0.0F);
  assert(clamped.blue() == 1.0F);

  assert(Color::black() == Color{0.0F, 0.0F, 0.0F});
  assert(Color::white() == Color{1.0F, 1.0F, 1.0F});
  assert(Color::red_color() == Color{1.0F, 0.0F, 0.0F});
  assert(Color::green_color() == Color{0.0F, 0.5F, 0.0F});
  assert(Color::blue_color() == Color{0.0F, 0.0F, 1.0F});
  assert(Color::gray() == Color{0.5F, 0.5F, 0.5F});
  assert(Color::light_gray() == Color{0.85F, 0.85F, 0.85F});

  assert(Color::from_hex(0x000000) == Color::black());
  assert(Color::from_hex(0xFFFFFF) == Color::white());
  assert(Color::from_hex(0xFF0000) == Color::red_color());
  assert(Color::from_hex(0x00FF00) == Color{0.0F, 1.0F, 0.0F});
  assert(Color::from_hex(0x0000FF) == Color::blue_color());

  assert(Color::black() != Color::white());

  return 0;
}
