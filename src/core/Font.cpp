/**
 *
 *  @file Font.cpp
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

#include <rix/pdf/core/Font.hpp>

namespace rixlib::pdf
{
  Font make_font(FontFamily family, FontStyle style) noexcept
  {
    switch (family)
    {
    case FontFamily::Helvetica:
      switch (style)
      {
      case FontStyle::Bold:
        return Font::HelveticaBold;
      case FontStyle::Italic:
        return Font::HelveticaOblique;
      case FontStyle::BoldItalic:
        return Font::HelveticaBoldOblique;
      case FontStyle::Regular:
        return Font::Helvetica;
      }

      return Font::Helvetica;

    case FontFamily::Times:
      switch (style)
      {
      case FontStyle::Bold:
        return Font::TimesBold;
      case FontStyle::Italic:
        return Font::TimesItalic;
      case FontStyle::BoldItalic:
        return Font::TimesBoldItalic;
      case FontStyle::Regular:
        return Font::Times;
      }

      return Font::Times;

    case FontFamily::Courier:
      switch (style)
      {
      case FontStyle::Bold:
        return Font::CourierBold;
      case FontStyle::Italic:
        return Font::CourierOblique;
      case FontStyle::BoldItalic:
        return Font::CourierBoldOblique;
      case FontStyle::Regular:
        return Font::Courier;
      }

      return Font::Courier;

    case FontFamily::Symbol:
      return Font::Symbol;

    case FontFamily::ZapfDingbats:
      return Font::ZapfDingbats;
    }

    return Font::Helvetica;
  }

  std::string_view base_font_name(Font font) noexcept
  {
    switch (font)
    {
    case Font::Helvetica:
      return "Helvetica";
    case Font::HelveticaBold:
      return "Helvetica-Bold";
    case Font::HelveticaOblique:
      return "Helvetica-Oblique";
    case Font::HelveticaBoldOblique:
      return "Helvetica-BoldOblique";

    case Font::Times:
      return "Times-Roman";
    case Font::TimesBold:
      return "Times-Bold";
    case Font::TimesItalic:
      return "Times-Italic";
    case Font::TimesBoldItalic:
      return "Times-BoldItalic";

    case Font::Courier:
      return "Courier";
    case Font::CourierBold:
      return "Courier-Bold";
    case Font::CourierOblique:
      return "Courier-Oblique";
    case Font::CourierBoldOblique:
      return "Courier-BoldOblique";

    case Font::Symbol:
      return "Symbol";
    case Font::ZapfDingbats:
      return "ZapfDingbats";
    }

    return "Helvetica";
  }

  std::string_view family_name(Font font) noexcept
  {
    switch (font_family(font))
    {
    case FontFamily::Helvetica:
      return "Helvetica";
    case FontFamily::Times:
      return "Times";
    case FontFamily::Courier:
      return "Courier";
    case FontFamily::Symbol:
      return "Symbol";
    case FontFamily::ZapfDingbats:
      return "ZapfDingbats";
    }

    return "Helvetica";
  }

  FontFamily font_family(Font font) noexcept
  {
    switch (font)
    {
    case Font::Helvetica:
    case Font::HelveticaBold:
    case Font::HelveticaOblique:
    case Font::HelveticaBoldOblique:
      return FontFamily::Helvetica;

    case Font::Times:
    case Font::TimesBold:
    case Font::TimesItalic:
    case Font::TimesBoldItalic:
      return FontFamily::Times;

    case Font::Courier:
    case Font::CourierBold:
    case Font::CourierOblique:
    case Font::CourierBoldOblique:
      return FontFamily::Courier;

    case Font::Symbol:
      return FontFamily::Symbol;

    case Font::ZapfDingbats:
      return FontFamily::ZapfDingbats;
    }

    return FontFamily::Helvetica;
  }

  FontStyle font_style(Font font) noexcept
  {
    switch (font)
    {
    case Font::HelveticaBold:
    case Font::TimesBold:
    case Font::CourierBold:
      return FontStyle::Bold;

    case Font::HelveticaOblique:
    case Font::TimesItalic:
    case Font::CourierOblique:
      return FontStyle::Italic;

    case Font::HelveticaBoldOblique:
    case Font::TimesBoldItalic:
    case Font::CourierBoldOblique:
      return FontStyle::BoldItalic;

    case Font::Helvetica:
    case Font::Times:
    case Font::Courier:
    case Font::Symbol:
    case Font::ZapfDingbats:
      return FontStyle::Regular;
    }

    return FontStyle::Regular;
  }

  bool is_bold(Font font) noexcept
  {
    const auto style = font_style(font);

    return style == FontStyle::Bold ||
           style == FontStyle::BoldItalic;
  }

  bool is_italic(Font font) noexcept
  {
    const auto style = font_style(font);

    return style == FontStyle::Italic ||
           style == FontStyle::BoldItalic;
  }

  bool is_monospaced(Font font) noexcept
  {
    return font_family(font) == FontFamily::Courier;
  }

  bool is_standard_font(Font /*font*/) noexcept
  {
    return true;
  }
} // namespace rixlib::pdf
