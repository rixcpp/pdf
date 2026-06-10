/**
 *
 *  @file FontRegistry.cpp
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

#include <rix/pdf/writer/FontRegistry.hpp>

#include <algorithm>

namespace rixlib::pdf::writer
{
  void FontRegistry::add(Font font)
  {
    if (!contains(font))
    {
      fonts_.push_back(font);
    }
  }

  void FontRegistry::add_all(const std::vector<Font> &fonts)
  {
    for (const auto font : fonts)
    {
      add(font);
    }
  }

  bool FontRegistry::contains(Font font) const noexcept
  {
    return std::find(fonts_.begin(), fonts_.end(), font) != fonts_.end();
  }

  std::size_t FontRegistry::size() const noexcept
  {
    return fonts_.size();
  }

  bool FontRegistry::empty() const noexcept
  {
    return fonts_.empty();
  }

  int FontRegistry::assign_object_ids(int first_object_id)
  {
    object_ids_.clear();

    int next_object_id = first_object_id;

    for (const auto font : fonts_)
    {
      object_ids_[font] = next_object_id;
      ++next_object_id;
    }

    return next_object_id;
  }

  int FontRegistry::object_id(Font font) const noexcept
  {
    const auto found = object_ids_.find(font);

    if (found == object_ids_.end())
    {
      return 0;
    }

    return found->second;
  }

  int FontRegistry::page_font_index(
      const std::vector<Font> &page_fonts,
      Font font) noexcept
  {
    for (int index = 0; index < static_cast<int>(page_fonts.size()); ++index)
    {
      if (page_fonts[static_cast<std::size_t>(index)] == font)
      {
        return index + 1;
      }
    }

    return 1;
  }

  const std::vector<Font> &FontRegistry::fonts() const noexcept
  {
    return fonts_;
  }
} // namespace rixlib::pdf::writer
