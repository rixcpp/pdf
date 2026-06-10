/**
 *
 *  @file Page.cpp
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

#include <rix/pdf/document/Page.hpp>

#include <rix/pdf/writer/Escape.hpp>
#include <rix/pdf/writer/FloatFormat.hpp>
#include <rix/pdf/writer/FontMetrics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <string>

namespace rixlib::pdf
{
  namespace
  {
    [[nodiscard]] std::string color_command(Color color, bool stroke)
    {
      std::string out;
      out += writer::format_float(color.red());
      out += " ";
      out += writer::format_float(color.green());
      out += " ";
      out += writer::format_float(color.blue());
      out += stroke ? " RG" : " rg";
      return out;
    }

    [[nodiscard]] Point heading_size(int level) noexcept
    {
      static constexpr std::array<Point, 6> sizes{
          24.0F,
          20.0F,
          16.0F,
          14.0F,
          13.0F,
          12.0F};

      const int index = std::clamp(level - 1, 0, 5);
      return sizes[static_cast<std::size_t>(index)];
    }

    [[nodiscard]] Point positive_or_default(Point value, Point fallback) noexcept
    {
      return value > 0.0F ? value : fallback;
    }
  } // namespace

  Page::Page(PageSize size, Margins margins)
      : size_(size),
        margins_(margins)
  {
  }

  const PageSize &Page::size() const noexcept
  {
    return size_;
  }

  const Margins &Page::margins() const noexcept
  {
    return margins_;
  }

  Point Page::width() const noexcept
  {
    return size_.width();
  }

  Point Page::height() const noexcept
  {
    return size_.height();
  }

  Point Page::content_width() const noexcept
  {
    return width() - margins_.horizontal();
  }

  Point Page::content_height() const noexcept
  {
    return height() - margins_.vertical();
  }

  Point Page::x_left() const noexcept
  {
    return margins_.left();
  }

  Point Page::x_right() const noexcept
  {
    return width() - margins_.right();
  }

  Point Page::y_top() const noexcept
  {
    return height() - margins_.top();
  }

  Point Page::y_bottom() const noexcept
  {
    return margins_.bottom();
  }

  Page &Page::text(
      Point x,
      Point y,
      std::string_view value,
      TextStyle style)
  {
    use_font(style.font());

    content_ += "BT\n";
    content_ += color_command(style.color(), false) + "\n";
    content_ += "/F" + std::to_string(font_index(style.font())) + " ";
    content_ += writer::format_point(style.size()) + " Tf\n";
    content_ += writer::format_point(x) + " ";
    content_ += writer::format_point(y) + " Td\n";
    content_ += writer::literal_string(value) + " Tj\n";
    content_ += "ET\n";

    return *this;
  }

  Page &Page::text_aligned(
      Point x,
      Point y,
      Point available_width,
      std::string_view value,
      Align align,
      TextStyle style)
  {
    Point target_x = x;
    const Point measured_width =
        writer::text_width(value, style.font(), style.size());

    if (align == Align::Center)
    {
      target_x = x + ((available_width - measured_width) / 2.0F);
    }
    else if (align == Align::Right)
    {
      target_x = x + available_width - measured_width;
    }

    return text(target_x, y, value, style);
  }

  Point Page::paragraph(
      Point x,
      Point y,
      Point available_width,
      std::string_view value,
      Align align,
      TextStyle style)
  {
    const auto lines = writer::wrap_text(
        value,
        style.font(),
        style.size(),
        available_width);

    Point current_y = y;

    use_font(style.font());

    for (const auto &line : lines)
    {
      if (line.text.empty())
      {
        current_y -= style.line_advance();
        continue;
      }

      if (align == Align::Justify &&
          !line.last_line &&
          line.text.find(' ') != std::string::npos)
      {
        const Point measured_width =
            writer::text_width(line.text, style.font(), style.size());

        const auto spaces = static_cast<int>(
            std::count(line.text.begin(), line.text.end(), ' '));

        const Point word_spacing =
            spaces > 0 ? (available_width - measured_width) / spaces : 0.0F;

        content_ += "BT\n";
        content_ += color_command(style.color(), false) + "\n";
        content_ += "/F" + std::to_string(font_index(style.font())) + " ";
        content_ += writer::format_point(style.size()) + " Tf\n";
        content_ += writer::format_point(word_spacing) + " Tw\n";
        content_ += writer::format_point(x) + " ";
        content_ += writer::format_point(current_y) + " Td\n";
        content_ += writer::literal_string(line.text) + " Tj\n";
        content_ += "0 Tw\n";
        content_ += "ET\n";
      }
      else
      {
        text_aligned(
            x,
            current_y,
            available_width,
            line.text,
            align == Align::Justify ? Align::Left : align,
            style);
      }

      current_y -= style.line_advance();
    }

    return current_y;
  }

  Point Page::heading(
      Point x,
      Point y,
      std::string_view value,
      int level,
      Color color)
  {
    const Point size = heading_size(level);

    text(
        x,
        y,
        value,
        TextStyle{
            Font::HelveticaBold,
            size,
            color,
            1.2F});

    return y - (size * 1.4F);
  }

  Page &Page::line(
      Point x1,
      Point y1,
      Point x2,
      Point y2,
      Point line_width,
      Color color,
      LineStyle style)
  {
    set_line_style(style, positive_or_default(line_width, 1.0F));

    content_ += color_command(color, true) + "\n";
    content_ += writer::format_point(x1) + " ";
    content_ += writer::format_point(y1) + " m\n";
    content_ += writer::format_point(x2) + " ";
    content_ += writer::format_point(y2) + " l\n";
    content_ += "S\n";

    reset_line_style(style);

    return *this;
  }

  Page &Page::rect(
      Point x,
      Point y,
      Point rect_width,
      Point rect_height,
      Point line_width,
      Color color)
  {
    content_ += writer::format_point(positive_or_default(line_width, 1.0F)) + " w\n";
    content_ += color_command(color, true) + "\n";
    content_ += writer::format_point(x) + " ";
    content_ += writer::format_point(y) + " ";
    content_ += writer::format_point(rect_width) + " ";
    content_ += writer::format_point(rect_height) + " re\n";
    content_ += "S\n";

    return *this;
  }

  Page &Page::fill_rect(
      Point x,
      Point y,
      Point rect_width,
      Point rect_height,
      Color color)
  {
    content_ += color_command(color, false) + "\n";
    content_ += writer::format_point(x) + " ";
    content_ += writer::format_point(y) + " ";
    content_ += writer::format_point(rect_width) + " ";
    content_ += writer::format_point(rect_height) + " re\n";
    content_ += "f\n";

    return *this;
  }

  Page &Page::fill_stroke_rect(
      Point x,
      Point y,
      Point rect_width,
      Point rect_height,
      Color fill_color,
      Color stroke_color,
      Point line_width)
  {
    content_ += writer::format_point(positive_or_default(line_width, 1.0F)) + " w\n";
    content_ += color_command(fill_color, false) + "\n";
    content_ += color_command(stroke_color, true) + "\n";
    content_ += writer::format_point(x) + " ";
    content_ += writer::format_point(y) + " ";
    content_ += writer::format_point(rect_width) + " ";
    content_ += writer::format_point(rect_height) + " re\n";
    content_ += "B\n";

    return *this;
  }

  Page &Page::circle(
      Point cx,
      Point cy,
      Point radius,
      Point line_width,
      Color color,
      bool filled)
  {
    if (radius <= 0.0F)
    {
      return *this;
    }

    const Point k = 0.5522847498F * radius;

    content_ += writer::format_point(positive_or_default(line_width, 1.0F)) + " w\n";

    if (filled)
    {
      content_ += color_command(color, false) + "\n";
    }

    content_ += color_command(color, true) + "\n";

    content_ += writer::format_point(cx) + " " +
                writer::format_point(cy + radius) + " m\n";

    content_ += writer::format_point(cx + k) + " " +
                writer::format_point(cy + radius) + " " +
                writer::format_point(cx + radius) + " " +
                writer::format_point(cy + k) + " " +
                writer::format_point(cx + radius) + " " +
                writer::format_point(cy) + " c\n";

    content_ += writer::format_point(cx + radius) + " " +
                writer::format_point(cy - k) + " " +
                writer::format_point(cx + k) + " " +
                writer::format_point(cy - radius) + " " +
                writer::format_point(cx) + " " +
                writer::format_point(cy - radius) + " c\n";

    content_ += writer::format_point(cx - k) + " " +
                writer::format_point(cy - radius) + " " +
                writer::format_point(cx - radius) + " " +
                writer::format_point(cy - k) + " " +
                writer::format_point(cx - radius) + " " +
                writer::format_point(cy) + " c\n";

    content_ += writer::format_point(cx - radius) + " " +
                writer::format_point(cy + k) + " " +
                writer::format_point(cx - k) + " " +
                writer::format_point(cy + radius) + " " +
                writer::format_point(cx) + " " +
                writer::format_point(cy + radius) + " c\n";

    content_ += filled ? "B\n" : "S\n";

    return *this;
  }

  Page &Page::hrule(
      Point y,
      Point x_start,
      Point x_end,
      Point line_width,
      Color color)
  {
    const Point start = x_start < 0.0F ? x_left() : x_start;
    const Point end = x_end < 0.0F ? x_right() : x_end;

    return line(start, y, end, y, line_width, color);
  }

  Page &Page::image(
      const Image &value,
      Point x,
      Point y,
      Point image_width,
      Point image_height)
  {
    if (!value.valid() || image_width <= 0.0F || image_height <= 0.0F)
    {
      return *this;
    }

    const int index = add_image(value);

    content_ += "q\n";
    content_ += writer::format_point(image_width) + " 0 0 ";
    content_ += writer::format_point(image_height) + " ";
    content_ += writer::format_point(x) + " ";
    content_ += writer::format_point(y) + " cm\n";
    content_ += "/Im" + std::to_string(index) + " Do\n";
    content_ += "Q\n";

    return *this;
  }

  Page &Page::image_fit(
      const Image &value,
      Point x,
      Point y,
      Point max_width,
      Point max_height)
  {
    if (!value.valid() || max_width <= 0.0F || max_height <= 0.0F)
    {
      return *this;
    }

    Point image_width = max_width;
    Point image_height = max_width / value.aspect_ratio();

    if (image_height > max_height)
    {
      image_height = max_height;
      image_width = max_height * value.aspect_ratio();
    }

    return image(value, x, y, image_width, image_height);
  }

  Point Page::table(
      Point x,
      Point y,
      const Table &table)
  {
    if (table.empty())
    {
      return y;
    }

    const auto &style = table.style();
    std::vector<Point> column_widths = table.column_widths();

    if (column_widths.empty())
    {
      const auto count = table.column_count();

      if (count == 0)
      {
        return y;
      }

      column_widths.assign(
          count,
          content_width() / static_cast<Point>(count));
    }

    Point current_y = y;

    for (std::size_t row_index = 0; row_index < table.rows().size(); ++row_index)
    {
      const auto &row = table.rows()[row_index];
      const Point row_height =
          row.height() > 0.0F ? row.height() : style.row_height();

      Point current_x = x;

      for (std::size_t column_index = 0; column_index < column_widths.size(); ++column_index)
      {
        if (column_index >= row.cells().size())
        {
          draw_cell_border(
              current_x,
              current_y - row_height,
              column_widths[column_index],
              row_height,
              style.border());

          current_x += column_widths[column_index];
          continue;
        }

        const auto &cell = row.cells()[column_index];

        Point cell_width = column_widths[column_index];

        for (std::size_t span = 1; span < cell.colspan() &&
                                   column_index + span < column_widths.size();
             ++span)
        {
          cell_width += column_widths[column_index + span];
        }

        if (row.header())
        {
          fill_rect(
              current_x,
              current_y - row_height,
              cell_width,
              row_height,
              row.header_background());
        }
        else if (cell.has_background())
        {
          fill_rect(
              current_x,
              current_y - row_height,
              cell_width,
              row_height,
              cell.background_color());
        }
        else if (style.stripe_rows() && row_index % 2 == 1)
        {
          fill_rect(
              current_x,
              current_y - row_height,
              cell_width,
              row_height,
              style.stripe_color());
        }

        draw_cell_border(
            current_x,
            current_y - row_height,
            cell_width,
            row_height,
            style.border());

        const Font font = row.header() ? style.header_font() : style.font();
        const Point font_size = row.header() ? style.header_size() : style.font_size();
        const Color text_color = row.header()
                                     ? row.header_foreground()
                                     : cell.text_color();

        const Point padding = style.cell_padding();
        const Point text_x = current_x + padding;
        const Point text_width = cell_width - (padding * 2.0F);
        const Point text_y = current_y - row_height + ((row_height - font_size) / 2.0F) + 2.0F;

        text_aligned(
            text_x,
            text_y,
            text_width,
            cell.text(),
            cell.align(),
            TextStyle{font, font_size, text_color});

        current_x += cell_width;
        column_index += cell.colspan() - 1;
      }

      current_y -= row_height;
    }

    return current_y;
  }

  Page &Page::page_number(
      int number,
      int total,
      Point y,
      TextStyle style)
  {
    std::string value = std::to_string(number);

    if (total > 0)
    {
      value += " / ";
      value += std::to_string(total);
    }

    const Point target_y = y < 0.0F ? margins_.bottom() / 2.0F : y;
    const Point measured_width =
        writer::text_width(value, style.font(), style.size());
    const Point target_x = (width() - measured_width) / 2.0F;

    return text(target_x, target_y, value, style);
  }

  const std::string &Page::content_stream() const noexcept
  {
    return content_;
  }

  const std::vector<Font> &Page::fonts() const noexcept
  {
    return fonts_;
  }

  const std::vector<const Image *> &Page::images() const noexcept
  {
    return images_;
  }

  int Page::font_index(Font font) const noexcept
  {
    for (int index = 0; index < static_cast<int>(fonts_.size()); ++index)
    {
      if (fonts_[static_cast<std::size_t>(index)] == font)
      {
        return index + 1;
      }
    }

    return 1;
  }

  void Page::use_font(Font font)
  {
    if (std::find(fonts_.begin(), fonts_.end(), font) == fonts_.end())
    {
      fonts_.push_back(font);
    }
  }

  int Page::add_image(const Image &value)
  {
    images_.push_back(&value);
    return static_cast<int>(images_.size());
  }

  void Page::set_line_style(LineStyle style, Point width)
  {
    content_ += writer::format_point(positive_or_default(width, 1.0F)) + " w\n";

    switch (style)
    {
    case LineStyle::Dashed:
      content_ += "[6 3] 0 d\n";
      break;
    case LineStyle::Dotted:
      content_ += "[2 2] 0 d\n";
      break;
    case LineStyle::Solid:
      content_ += "[] 0 d\n";
      break;
    }
  }

  void Page::reset_line_style(LineStyle style)
  {
    if (style != LineStyle::Solid)
    {
      content_ += "[] 0 d\n";
    }
  }

  void Page::draw_cell_border(
      Point x,
      Point y,
      Point cell_width,
      Point cell_height,
      const BorderStyle &border)
  {
    if (!border.visible())
    {
      return;
    }

    set_line_style(border.line_style(), border.width());
    content_ += color_command(border.color(), true) + "\n";

    if (border.left())
    {
      content_ += writer::format_point(x) + " ";
      content_ += writer::format_point(y) + " m ";
      content_ += writer::format_point(x) + " ";
      content_ += writer::format_point(y + cell_height) + " l S\n";
    }

    if (border.right())
    {
      content_ += writer::format_point(x + cell_width) + " ";
      content_ += writer::format_point(y) + " m ";
      content_ += writer::format_point(x + cell_width) + " ";
      content_ += writer::format_point(y + cell_height) + " l S\n";
    }

    if (border.bottom())
    {
      content_ += writer::format_point(x) + " ";
      content_ += writer::format_point(y) + " m ";
      content_ += writer::format_point(x + cell_width) + " ";
      content_ += writer::format_point(y) + " l S\n";
    }

    if (border.top())
    {
      content_ += writer::format_point(x) + " ";
      content_ += writer::format_point(y + cell_height) + " m ";
      content_ += writer::format_point(x + cell_width) + " ";
      content_ += writer::format_point(y + cell_height) + " l S\n";
    }

    reset_line_style(border.line_style());
  }
} // namespace rixlib::pdf
