/**
 *
 *  @file Table.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TABLE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TABLE_HPP_INCLUDED

#include <rix/pdf/core/Align.hpp>
#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/Units.hpp>
#include <rix/pdf/document/BorderStyle.hpp>

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace rixlib::pdf
{
  /**
   * @brief A single table cell.
   *
   * TableCell stores text and visual options for one table cell.
   */
  class TableCell
  {
  public:
    /**
     * @brief Construct an empty table cell.
     */
    TableCell() = default;

    /**
     * @brief Construct a table cell with text.
     *
     * @param text Cell text.
     */
    explicit TableCell(std::string text);

    /**
     * @brief Construct a table cell with text and alignment.
     *
     * @param text Cell text.
     * @param align Text alignment.
     */
    TableCell(std::string text, Align align);

    /**
     * @brief Return the cell text.
     *
     * @return Cell text.
     */
    [[nodiscard]] const std::string &text() const noexcept;

    /**
     * @brief Set the cell text.
     *
     * @param value Cell text.
     * @return This cell.
     */
    TableCell &set_text(std::string value);

    /**
     * @brief Return the text alignment.
     *
     * @return Text alignment.
     */
    [[nodiscard]] Align align() const noexcept;

    /**
     * @brief Set the text alignment.
     *
     * @param value Text alignment.
     * @return This cell.
     */
    TableCell &set_align(Align value) noexcept;

    /**
     * @brief Return the text color.
     *
     * @return Text color.
     */
    [[nodiscard]] Color text_color() const noexcept;

    /**
     * @brief Set the text color.
     *
     * @param value Text color.
     * @return This cell.
     */
    TableCell &set_text_color(Color value) noexcept;

    /**
     * @brief Return true when the cell has a background color.
     *
     * @return true if a background color is enabled.
     */
    [[nodiscard]] bool has_background() const noexcept;

    /**
     * @brief Return the background color.
     *
     * @return Background color.
     */
    [[nodiscard]] Color background_color() const noexcept;

    /**
     * @brief Set the background color.
     *
     * @param value Background color.
     * @return This cell.
     */
    TableCell &set_background_color(Color value) noexcept;

    /**
     * @brief Clear the background color.
     *
     * @return This cell.
     */
    TableCell &clear_background_color() noexcept;

    /**
     * @brief Return the number of columns spanned by this cell.
     *
     * @return Column span.
     */
    [[nodiscard]] std::size_t colspan() const noexcept;

    /**
     * @brief Set the column span.
     *
     * Values smaller than one are normalized to one.
     *
     * @param value Column span.
     * @return This cell.
     */
    TableCell &set_colspan(std::size_t value) noexcept;

  private:
    std::string text_;
    Align align_ = Align::Left;
    Color text_color_ = Color::black();
    Color background_color_ = Color::white();
    bool has_background_ = false;
    std::size_t colspan_ = 1;
  };

  /**
   * @brief A table row.
   */
  class TableRow
  {
  public:
    /**
     * @brief Construct an empty table row.
     */
    TableRow() = default;

    /**
     * @brief Construct a table row from cells.
     *
     * @param cells Row cells.
     */
    explicit TableRow(std::vector<TableCell> cells);

    /**
     * @brief Return the row cells.
     *
     * @return Row cells.
     */
    [[nodiscard]] const std::vector<TableCell> &cells() const noexcept;

    /**
     * @brief Return the row cells.
     *
     * @return Row cells.
     */
    [[nodiscard]] std::vector<TableCell> &cells() noexcept;

    /**
     * @brief Add a cell to the row.
     *
     * @param cell Cell to add.
     * @return This row.
     */
    TableRow &add_cell(TableCell cell);

    /**
     * @brief Add a text cell to the row.
     *
     * @param text Cell text.
     * @return This row.
     */
    TableRow &add_cell(std::string text);

    /**
     * @brief Return true when this row is a header row.
     *
     * @return true if this is a header row.
     */
    [[nodiscard]] bool header() const noexcept;

    /**
     * @brief Mark this row as a header row or normal row.
     *
     * @param value true for header row.
     * @return This row.
     */
    TableRow &set_header(bool value) noexcept;

    /**
     * @brief Return the row height.
     *
     * A value of zero means the table style decides the height.
     *
     * @return Row height in PDF points.
     */
    [[nodiscard]] Point height() const noexcept;

    /**
     * @brief Set the row height.
     *
     * Negative values are normalized to zero.
     *
     * @param value Row height in PDF points.
     * @return This row.
     */
    TableRow &set_height(Point value) noexcept;

    /**
     * @brief Return the header background color.
     *
     * @return Header background color.
     */
    [[nodiscard]] Color header_background() const noexcept;

    /**
     * @brief Set the header background color.
     *
     * @param value Header background color.
     * @return This row.
     */
    TableRow &set_header_background(Color value) noexcept;

    /**
     * @brief Return the header text color.
     *
     * @return Header text color.
     */
    [[nodiscard]] Color header_foreground() const noexcept;

    /**
     * @brief Set the header text color.
     *
     * @param value Header text color.
     * @return This row.
     */
    TableRow &set_header_foreground(Color value) noexcept;

  private:
    std::vector<TableCell> cells_;
    bool header_ = false;
    Point height_ = 0.0F;
    Color header_background_ = Color::from_hex(0x2C3E50);
    Color header_foreground_ = Color::white();
  };

  /**
   * @brief Table rendering style.
   */
  class TableStyle
  {
  public:
    /**
     * @brief Construct the default table style.
     */
    TableStyle() = default;

    [[nodiscard]] Font font() const noexcept;
    TableStyle &set_font(Font value) noexcept;

    [[nodiscard]] Point font_size() const noexcept;
    TableStyle &set_font_size(Point value) noexcept;

    [[nodiscard]] Font header_font() const noexcept;
    TableStyle &set_header_font(Font value) noexcept;

    [[nodiscard]] Point header_size() const noexcept;
    TableStyle &set_header_size(Point value) noexcept;

    [[nodiscard]] Point row_height() const noexcept;
    TableStyle &set_row_height(Point value) noexcept;

    [[nodiscard]] Point cell_padding() const noexcept;
    TableStyle &set_cell_padding(Point value) noexcept;

    [[nodiscard]] const BorderStyle &border() const noexcept;
    TableStyle &set_border(BorderStyle value) noexcept;

    [[nodiscard]] Color stripe_color() const noexcept;
    TableStyle &set_stripe_color(Color value) noexcept;

    [[nodiscard]] bool stripe_rows() const noexcept;
    TableStyle &set_stripe_rows(bool value) noexcept;

  private:
    [[nodiscard]] static Point normalize_positive(Point value, Point fallback) noexcept;
    [[nodiscard]] static Point normalize_non_negative(Point value) noexcept;

    Font font_ = Font::Helvetica;
    Point font_size_ = 10.0F;
    Font header_font_ = Font::HelveticaBold;
    Point header_size_ = 10.0F;
    Point row_height_ = 20.0F;
    Point cell_padding_ = 4.0F;
    BorderStyle border_;
    Color stripe_color_ = Color::from_hex(0xF2F2F2);
    bool stripe_rows_ = true;
  };

  /**
   * @brief Table data and layout information.
   */
  class Table
  {
  public:
    /**
     * @brief Construct an empty table.
     */
    Table() = default;

    /**
     * @brief Return the column widths.
     *
     * @return Column widths.
     */
    [[nodiscard]] const std::vector<Point> &column_widths() const noexcept;

    /**
     * @brief Set column widths.
     *
     * Negative values are normalized to zero.
     *
     * @param values Column widths in PDF points.
     * @return This table.
     */
    Table &set_column_widths(std::vector<Point> values);

    /**
     * @brief Return the table rows.
     *
     * @return Table rows.
     */
    [[nodiscard]] const std::vector<TableRow> &rows() const noexcept;

    /**
     * @brief Return the table rows.
     *
     * @return Table rows.
     */
    [[nodiscard]] std::vector<TableRow> &rows() noexcept;

    /**
     * @brief Add a row to the table.
     *
     * @param row Row to add.
     * @return This table.
     */
    Table &add_row(TableRow row);

    /**
     * @brief Add a row from text values.
     *
     * @param values Cell text values.
     * @return This table.
     */
    Table &add_row(std::vector<std::string> values);

    /**
     * @brief Add a header row from text values.
     *
     * @param values Header cell text values.
     * @return This table.
     */
    Table &add_header(std::vector<std::string> values);

    /**
     * @brief Return the table style.
     *
     * @return Table style.
     */
    [[nodiscard]] const TableStyle &style() const noexcept;

    /**
     * @brief Return the table style.
     *
     * @return Table style.
     */
    [[nodiscard]] TableStyle &style() noexcept;

    /**
     * @brief Set the table style.
     *
     * @param value Table style.
     * @return This table.
     */
    Table &set_style(TableStyle value) noexcept;

    /**
     * @brief Return true when the table has no rows.
     *
     * @return true if the table is empty.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Return the number of rows.
     *
     * @return Row count.
     */
    [[nodiscard]] std::size_t row_count() const noexcept;

    /**
     * @brief Return the number of columns.
     *
     * @return Column count.
     */
    [[nodiscard]] std::size_t column_count() const noexcept;

  private:
    std::vector<Point> column_widths_;
    std::vector<TableRow> rows_;
    TableStyle style_;
  };
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TABLE_HPP_INCLUDED
