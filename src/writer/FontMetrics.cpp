/**
 *
 *  @file FontMetrics.cpp
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

#include <algorithm>
#include <array>
#include <string>

namespace rixlib::pdf::writer
{
  namespace
  {
    static constexpr std::array<int, 96> HELVETICA_WIDTHS = {
        278, 278, 355, 556, 556, 889, 667, 191,
        333, 333, 389, 584, 278, 333, 278, 278,
        556, 556, 556, 556, 556, 556, 556, 556,
        556, 556, 278, 278, 584, 584, 584, 556,
        1015, 667, 667, 722, 722, 667, 611, 778,
        722, 278, 500, 667, 556, 833, 722, 778,
        667, 778, 722, 667, 611, 722, 667, 944,
        667, 667, 611, 278, 278, 278, 469, 556,
        333, 556, 556, 500, 556, 556, 278, 556,
        556, 222, 222, 500, 222, 833, 556, 556,
        556, 556, 333, 500, 278, 556, 500, 722,
        500, 500, 500, 334, 260, 334, 584, 350};

    static constexpr std::array<int, 96> HELVETICA_BOLD_WIDTHS = {
        278, 333, 474, 556, 556, 889, 722, 238,
        333, 333, 389, 584, 278, 333, 278, 278,
        556, 556, 556, 556, 556, 556, 556, 556,
        556, 556, 333, 333, 584, 584, 584, 611,
        975, 722, 722, 722, 722, 667, 611, 778,
        722, 278, 556, 722, 611, 833, 722, 778,
        667, 778, 722, 667, 611, 722, 667, 944,
        667, 667, 611, 333, 278, 333, 584, 556,
        333, 556, 611, 556, 611, 556, 333, 611,
        611, 278, 278, 556, 278, 889, 611, 611,
        611, 611, 389, 556, 333, 611, 556, 778,
        556, 556, 500, 389, 280, 389, 584, 350};

    static constexpr std::array<int, 96> COURIER_WIDTHS = {
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600,
        600, 600, 600, 600, 600, 600, 600, 600};

    static constexpr std::array<int, 96> TIMES_WIDTHS = {
        250, 333, 408, 500, 500, 833, 778, 180,
        333, 333, 500, 564, 250, 333, 250, 278,
        500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 278, 278, 564, 564, 564, 444,
        921, 722, 667, 667, 722, 611, 556, 722,
        722, 333, 389, 722, 611, 889, 722, 722,
        556, 722, 667, 556, 611, 722, 722, 944,
        722, 722, 611, 333, 278, 333, 469, 500,
        333, 444, 500, 444, 500, 444, 333, 500,
        500, 278, 278, 500, 278, 778, 500, 500,
        500, 500, 333, 389, 278, 500, 500, 722,
        500, 500, 444, 480, 200, 480, 541, 350};

    [[nodiscard]] const std::array<int, 96> &width_table(Font font) noexcept
    {
      switch (font)
      {
      case Font::HelveticaBold:
      case Font::HelveticaBoldOblique:
        return HELVETICA_BOLD_WIDTHS;

      case Font::Courier:
      case Font::CourierBold:
      case Font::CourierOblique:
      case Font::CourierBoldOblique:
        return COURIER_WIDTHS;

      case Font::Times:
      case Font::TimesBold:
      case Font::TimesItalic:
      case Font::TimesBoldItalic:
        return TIMES_WIDTHS;

      case Font::Helvetica:
      case Font::HelveticaOblique:
      case Font::Symbol:
      case Font::ZapfDingbats:
        return HELVETICA_WIDTHS;
      }

      return HELVETICA_WIDTHS;
    }
  } // namespace

  int character_width(Font font, unsigned char character) noexcept
  {
    if (character >= 32 && character < 128)
    {
      return width_table(font)[static_cast<std::size_t>(character - 32)];
    }

    return 600;
  }

  Point text_width(
      std::string_view text,
      Font font,
      Point size) noexcept
  {
    int total = 0;

    for (unsigned char character : text)
    {
      total += character_width(font, character);
    }

    return static_cast<Point>(total) * size / 1000.0F;
  }

  std::vector<WrappedLine> wrap_text(
      std::string_view text,
      Font font,
      Point size,
      Point max_width)
  {
    std::vector<WrappedLine> lines;

    if (text.empty())
    {
      return lines;
    }

    if (max_width <= 0.0F)
    {
      lines.push_back({std::string(text), true});
      return lines;
    }

    std::string current;
    std::string word;

    auto flush_word = [&]()
    {
      if (word.empty())
      {
        return;
      }

      const std::string candidate =
          current.empty() ? word : current + " " + word;

      if (text_width(candidate, font, size) <= max_width)
      {
        current = candidate;
      }
      else
      {
        if (!current.empty())
        {
          lines.push_back({current, false});
          current = word;
        }
        else
        {
          lines.push_back({word, false});
          current.clear();
        }
      }

      word.clear();
    };

    for (char character : text)
    {
      if (character == '\n')
      {
        flush_word();

        if (!current.empty())
        {
          lines.push_back({current, true});
          current.clear();
        }
        else
        {
          lines.push_back({"", true});
        }
      }
      else if (character == ' ' || character == '\t')
      {
        flush_word();
      }
      else
      {
        word.push_back(character);
      }
    }

    flush_word();

    if (!current.empty())
    {
      lines.push_back({current, true});
    }
    else if (!lines.empty())
    {
      lines.back().last_line = true;
    }

    return lines;
  }
} // namespace rixlib::pdf::writer
