/**
 *
 *  @file PageSizeTests.cpp
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

#include <rix/pdf/core/PageSize.hpp>
#include <rix/pdf/core/Units.hpp>

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

  PageSize default_size;

  assert(default_size.valid());
  assert(near(default_size.width(), 595.28F));
  assert(near(default_size.height(), 841.89F));
  assert(default_size.portrait());
  assert(!default_size.landscape());

  PageSize a4 = PageSize::A4();
  PageSize a3 = PageSize::A3();
  PageSize letter = PageSize::Letter();
  PageSize legal = PageSize::Legal();

  assert(near(a4.width(), 595.28F));
  assert(near(a4.height(), 841.89F));

  assert(near(a3.width(), 841.89F));
  assert(near(a3.height(), 1190.55F));

  assert(near(letter.width(), 612.0F));
  assert(near(letter.height(), 792.0F));

  assert(near(legal.width(), 612.0F));
  assert(near(legal.height(), 1008.0F));

  PageSize custom = PageSize::custom(100.0F, 200.0F);

  assert(custom.width() == 100.0F);
  assert(custom.height() == 200.0F);
  assert(custom.valid());
  assert(custom.portrait());

  PageSize landscape = custom.as_landscape();

  assert(landscape.landscape());
  assert(landscape.width() == 200.0F);
  assert(landscape.height() == 100.0F);

  PageSize portrait = landscape.as_portrait();

  assert(portrait.portrait());
  assert(portrait.width() == 100.0F);
  assert(portrait.height() == 200.0F);

  PageSize from_inches = PageSize::from_inches(8.5F, 11.0F);

  assert(near(from_inches.width(), inches(8.5F)));
  assert(near(from_inches.height(), inches(11.0F)));

  PageSize from_mm = PageSize::from_millimeters(210.0F, 297.0F);

  assert(near(from_mm.width(), millimeters(210.0F)));
  assert(near(from_mm.height(), millimeters(297.0F)));

  PageSize invalid{-10.0F, 0.0F};

  assert(invalid.width() == 0.0F);
  assert(invalid.height() == 0.0F);
  assert(!invalid.valid());

  invalid.set_width(300.0F);
  invalid.set_height(400.0F);

  assert(invalid.width() == 300.0F);
  assert(invalid.height() == 400.0F);
  assert(invalid.valid());

  assert(PageSize::A4() == default_size);
  assert(PageSize::A4() != PageSize::Letter());

  return 0;
}
