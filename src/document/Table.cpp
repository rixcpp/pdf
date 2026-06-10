/**
 *
 *  @file Table.cpp
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

#include <rix/pdf/document/Table.hpp>

#include <algorithm>
#include <utility>

namespace rixlib::pdf
{
  TableCell::TableCell(std::string text)
      : text_(std::move(text))
  {
  }

  TableCell::TableCell(std::string text, Align align)
      : text_(std::move(text)),
        align_(align)
  {
  }

  const std::string &TableCell::text() const noexcept
  {
    return text_;
  }

  TableCell &TableCell::set_text(std::string value)
  {
    text_ = std::move(value);
    return *this;
  }

  Align TableCell::align() const noexcept
  {
    return align_;
  }

  TableCell &TableCell::set_align(Align value) noexcept
  {
    align_ = value;
    return *this;
  }

  Color TableCell::text_color() const noexcept
  {
    return text_color_;
  }

  TableCell &TableCell::set_text_color(Color value) noexcept
  {
    text_color_ = value;
    return *this;
  }

  bool TableCell::has_background() const noexcept
  {
    return has_background_;
  }

  Color TableCell::background_color() const noexcept
  {
    return background_color_;
  }

  TableCell &TableCell::set_background_color(Color value) noexcept
  {
    background_color_ = value;
    has_background_ = true;
    return *this;
  }

  TableCell &TableCell::clear_background_color() noexcept
  {
    background_color_ = Color::white();
    has_background_ = false;
    return *this;
  }

  std::size_t TableCell::colspan() const noexcept
  {
    return colspan_;
  }

  TableCell &TableCell::set_colspan(std::size_t value) noexcept
  {
    colspan_ = std::max<std::size_t>(1, value);
    return *this;
  }

  TableRow::TableRow(std::vector<TableCell> cells)
      : cells_(std::move(cells))
  {
  }

  const std::vector<TableCell> &TableRow::cells() const noexcept
  {
    return cells_;
  }

  std::vector<TableCell> &TableRow::cells() noexcept
  {
    return cells_;
  }

  TableRow &TableRow::add_cell(TableCell cell)
  {
    cells_.push_back(std::move(cell));
    return *this;
  }

  TableRow &TableRow::add_cell(std::string text)
  {
    cells_.emplace_back(std::move(text));
    return *this;
  }

  bool TableRow::header() const noexcept
  {
    return header_;
  }

  TableRow &TableRow::set_header(bool value) noexcept
  {
    header_ = value;
    return *this;
  }

  Point TableRow::height() const noexcept
  {
    return height_;
  }

  TableRow &TableRow::set_height(Point value) noexcept
  {
    height_ = value < 0.0F ? 0.0F : value;
    return *this;
  }

  Color TableRow::header_background() const noexcept
  {
    return header_background_;
  }

  TableRow &TableRow::set_header_background(Color value) noexcept
  {
    header_background_ = value;
    return *this;
  }

  Color TableRow::header_foreground() const noexcept
  {
    return header_foreground_;
  }

  TableRow &TableRow::set_header_foreground(Color value) noexcept
  {
    header_foreground_ = value;
    return *this;
  }

  Point TableStyle::normalize_positive(Point value, Point fallback) noexcept
  {
    return value > 0.0F ? value : fallback;
  }

  Point TableStyle::normalize_non_negative(Point value) noexcept
  {
    return value < 0.0F ? 0.0F : value;
  }

  Font TableStyle::font() const noexcept
  {
    return font_;
  }

  TableStyle &TableStyle::set_font(Font value) noexcept
  {
    font_ = value;
    return *this;
  }

  Point TableStyle::font_size() const noexcept
  {
    return font_size_;
  }

  TableStyle &TableStyle::set_font_size(Point value) noexcept
  {
    font_size_ = normalize_positive(value, 10.0F);
    return *this;
  }

  Font TableStyle::header_font() const noexcept
  {
    return header_font_;
  }

  TableStyle &TableStyle::set_header_font(Font value) noexcept
  {
    header_font_ = value;
    return *this;
  }

  Point TableStyle::header_size() const noexcept
  {
    return header_size_;
  }

  TableStyle &TableStyle::set_header_size(Point value) noexcept
  {
    header_size_ = normalize_positive(value, 10.0F);
    return *this;
  }

  Point TableStyle::row_height() const noexcept
  {
    return row_height_;
  }

  TableStyle &TableStyle::set_row_height(Point value) noexcept
  {
    row_height_ = normalize_positive(value, 20.0F);
    return *this;
  }

  Point TableStyle::cell_padding() const noexcept
  {
    return cell_padding_;
  }

  TableStyle &TableStyle::set_cell_padding(Point value) noexcept
  {
    cell_padding_ = normalize_non_negative(value);
    return *this;
  }

  const BorderStyle &TableStyle::border() const noexcept
  {
    return border_;
  }

  TableStyle &TableStyle::set_border(BorderStyle value) noexcept
  {
    border_ = value;
    return *this;
  }

  Color TableStyle::stripe_color() const noexcept
  {
    return stripe_color_;
  }

  TableStyle &TableStyle::set_stripe_color(Color value) noexcept
  {
    stripe_color_ = value;
    return *this;
  }

  bool TableStyle::stripe_rows() const noexcept
  {
    return stripe_rows_;
  }

  TableStyle &TableStyle::set_stripe_rows(bool value) noexcept
  {
    stripe_rows_ = value;
    return *this;
  }

  const std::vector<Point> &Table::column_widths() const noexcept
  {
    return column_widths_;
  }

  Table &Table::set_column_widths(std::vector<Point> values)
  {
    for (auto &value : values)
    {
      if (value < 0.0F)
      {
        value = 0.0F;
      }
    }

    column_widths_ = std::move(values);
    return *this;
  }

  const std::vector<TableRow> &Table::rows() const noexcept
  {
    return rows_;
  }

  std::vector<TableRow> &Table::rows() noexcept
  {
    return rows_;
  }

  Table &Table::add_row(TableRow row)
  {
    rows_.push_back(std::move(row));
    return *this;
  }

  Table &Table::add_row(std::vector<std::string> values)
  {
    TableRow row;

    for (auto &value : values)
    {
      row.add_cell(std::move(value));
    }

    return add_row(std::move(row));
  }

  Table &Table::add_header(std::vector<std::string> values)
  {
    TableRow row;
    row.set_header(true);

    for (auto &value : values)
    {
      row.add_cell(std::move(value));
    }

    return add_row(std::move(row));
  }

  const TableStyle &Table::style() const noexcept
  {
    return style_;
  }

  TableStyle &Table::style() noexcept
  {
    return style_;
  }

  Table &Table::set_style(TableStyle value) noexcept
  {
    style_ = value;
    return *this;
  }

  bool Table::empty() const noexcept
  {
    return rows_.empty();
  }

  std::size_t Table::row_count() const noexcept
  {
    return rows_.size();
  }

  std::size_t Table::column_count() const noexcept
  {
    if (!column_widths_.empty())
    {
      return column_widths_.size();
    }

    std::size_t count = 0;

    for (const auto &row : rows_)
    {
      count = std::max(count, row.cells().size());
    }

    return count;
  }
} // namespace rixlib::pdf
