/**
 *
 *  @file PdfCoreTests.cpp
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

#include <rix/pdf/core/Align.hpp>
#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/LineStyle.hpp>
#include <rix/pdf/core/Margins.hpp>
#include <rix/pdf/core/PageSize.hpp>
#include <rix/pdf/core/Units.hpp>
#include <rix/pdf/Version.hpp>

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

  assert(version() == "0.1.0");
  assert(version_major() == 0);
  assert(version_minor() == 1);
  assert(version_patch() == 0);
  assert(version_number() == 100);

  assert(near(inches(1.0F), 72.0F));
  assert(near(points_to_inches(72.0F), 1.0F));
  assert(near(centimeters(2.54F), 72.0F));
  assert(near(points_to_centimeters(72.0F), 2.54F));
  assert(is_positive(1.0F));
  assert(!is_positive(0.0F));
  assert(is_non_negative(0.0F));
  assert(clamp_non_negative(-10.0F) == 0.0F);

  Color color{-1.0F, 0.5F, 2.0F};

  assert(color.red() == 0.0F);
  assert(color.green() == 0.5F);
  assert(color.blue() == 1.0F);
  assert(Color::black() == Color{0.0F, 0.0F, 0.0F});
  assert(Color::white() == Color{1.0F, 1.0F, 1.0F});
  assert(Color::from_hex(0xFF0000) == Color::red_color());
  assert(Color::from_hex(0x0000FF) == Color::blue_color());

  assert(make_font(FontFamily::Helvetica) == Font::Helvetica);
  assert(make_font(FontFamily::Helvetica, FontStyle::Bold) == Font::HelveticaBold);
  assert(make_font(FontFamily::Helvetica, FontStyle::Italic) == Font::HelveticaOblique);
  assert(make_font(FontFamily::Helvetica, FontStyle::BoldItalic) == Font::HelveticaBoldOblique);

  assert(make_font(FontFamily::Times) == Font::Times);
  assert(make_font(FontFamily::Times, FontStyle::Bold) == Font::TimesBold);
  assert(make_font(FontFamily::Times, FontStyle::Italic) == Font::TimesItalic);
  assert(make_font(FontFamily::Times, FontStyle::BoldItalic) == Font::TimesBoldItalic);

  assert(make_font(FontFamily::Courier) == Font::Courier);
  assert(make_font(FontFamily::Courier, FontStyle::Bold) == Font::CourierBold);
  assert(make_font(FontFamily::Courier, FontStyle::Italic) == Font::CourierOblique);
  assert(make_font(FontFamily::Courier, FontStyle::BoldItalic) == Font::CourierBoldOblique);

  assert(base_font_name(Font::Helvetica) == "Helvetica");
  assert(base_font_name(Font::Times) == "Times-Roman");
  assert(base_font_name(Font::CourierBold) == "Courier-Bold");

  assert(font_family(Font::HelveticaBold) == FontFamily::Helvetica);
  assert(font_family(Font::TimesItalic) == FontFamily::Times);
  assert(font_family(Font::CourierOblique) == FontFamily::Courier);

  assert(font_style(Font::Helvetica) == FontStyle::Regular);
  assert(font_style(Font::HelveticaBold) == FontStyle::Bold);
  assert(font_style(Font::TimesItalic) == FontStyle::Italic);
  assert(font_style(Font::CourierBoldOblique) == FontStyle::BoldItalic);

  assert(is_bold(Font::HelveticaBold));
  assert(!is_bold(Font::Helvetica));
  assert(is_italic(Font::TimesItalic));
  assert(!is_italic(Font::Times));
  assert(is_monospaced(Font::Courier));
  assert(!is_monospaced(Font::Helvetica));
  assert(is_standard_font(Font::ZapfDingbats));

  assert(to_string(Align::Left) == "Left");
  assert(to_string(Align::Center) == "Center");
  assert(to_string(Align::Right) == "Right");
  assert(to_string(Align::Justify) == "Justify");
  assert(is_left(Align::Left));
  assert(is_center(Align::Center));
  assert(is_right(Align::Right));
  assert(is_justify(Align::Justify));

  assert(to_string(LineStyle::Solid) == "Solid");
  assert(to_string(LineStyle::Dashed) == "Dashed");
  assert(to_string(LineStyle::Dotted) == "Dotted");
  assert(is_solid(LineStyle::Solid));
  assert(is_dashed(LineStyle::Dashed));
  assert(is_dotted(LineStyle::Dotted));

  PageSize a4 = PageSize::A4();

  assert(a4.valid());
  assert(a4.portrait());
  assert(!a4.landscape());
  assert(a4.as_landscape().landscape());
  assert(a4.as_portrait().portrait());

  PageSize custom{-10.0F, 100.0F};

  assert(custom.width() == 0.0F);
  assert(custom.height() == 100.0F);
  assert(!custom.valid());

  Margins margins;

  assert(near(margins.top(), 72.0F));
  assert(near(margins.bottom(), 72.0F));
  assert(near(margins.left(), 72.0F));
  assert(near(margins.right(), 72.0F));
  assert(near(margins.horizontal(), 144.0F));
  assert(near(margins.vertical(), 144.0F));
  assert(!margins.empty());

  Margins none = Margins::none();

  assert(none.empty());
  assert(none.horizontal() == 0.0F);
  assert(none.vertical() == 0.0F);

  Margins clamped{-1.0F, -2.0F, 10.0F, 20.0F};

  assert(clamped.top() == 0.0F);
  assert(clamped.bottom() == 0.0F);
  assert(clamped.left() == 10.0F);
  assert(clamped.right() == 20.0F);

  return 0;
}
