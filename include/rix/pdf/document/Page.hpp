/**
 *
 *  @file Page.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_PAGE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_PAGE_HPP_INCLUDED

#include <rix/pdf/core/Align.hpp>
#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/LineStyle.hpp>
#include <rix/pdf/core/Margins.hpp>
#include <rix/pdf/core/PageSize.hpp>
#include <rix/pdf/core/Units.hpp>
#include <rix/pdf/document/Image.hpp>
#include <rix/pdf/document/Table.hpp>
#include <rix/pdf/document/TextStyle.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace rixlib::pdf
{
  /**
   * @brief A single PDF page.
   *
   * Page is the public drawing surface used by applications.
   * It records PDF drawing commands while keeping serialization details inside
   * the writer layer.
   */
  class Page
  {
  public:
    /**
     * @brief Construct a page.
     *
     * @param size Page size.
     * @param margins Page margins.
     */
    explicit Page(
        PageSize size = PageSize::A4(),
        Margins margins = Margins{});

    /**
     * @brief Return the page size.
     *
     * @return Page size.
     */
    [[nodiscard]] const PageSize &size() const noexcept;

    /**
     * @brief Return the page margins.
     *
     * @return Page margins.
     */
    [[nodiscard]] const Margins &margins() const noexcept;

    /**
     * @brief Return the page width.
     *
     * @return Page width in PDF points.
     */
    [[nodiscard]] Point width() const noexcept;

    /**
     * @brief Return the page height.
     *
     * @return Page height in PDF points.
     */
    [[nodiscard]] Point height() const noexcept;

    /**
     * @brief Return the content width inside margins.
     *
     * @return Content width in PDF points.
     */
    [[nodiscard]] Point content_width() const noexcept;

    /**
     * @brief Return the content height inside margins.
     *
     * @return Content height in PDF points.
     */
    [[nodiscard]] Point content_height() const noexcept;

    /**
     * @brief Return the left content X position.
     *
     * @return Left X position.
     */
    [[nodiscard]] Point x_left() const noexcept;

    /**
     * @brief Return the right content X position.
     *
     * @return Right X position.
     */
    [[nodiscard]] Point x_right() const noexcept;

    /**
     * @brief Return the top content Y position.
     *
     * @return Top Y position.
     */
    [[nodiscard]] Point y_top() const noexcept;

    /**
     * @brief Return the bottom content Y position.
     *
     * @return Bottom Y position.
     */
    [[nodiscard]] Point y_bottom() const noexcept;

    /**
     * @brief Draw one line of text.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param value Text value.
     * @param style Text style.
     * @return This page.
     */
    Page &text(
        Point x,
        Point y,
        std::string_view value,
        TextStyle style = TextStyle{});

    /**
     * @brief Draw one line of aligned text inside a width.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param width Available width.
     * @param value Text value.
     * @param align Text alignment.
     * @param style Text style.
     * @return This page.
     */
    Page &text_aligned(
        Point x,
        Point y,
        Point width,
        std::string_view value,
        Align align = Align::Left,
        TextStyle style = TextStyle{});

    /**
     * @brief Draw a wrapped paragraph.
     *
     * @param x X coordinate.
     * @param y Starting Y coordinate.
     * @param width Available width.
     * @param value Paragraph text.
     * @param align Text alignment.
     * @param style Text style.
     * @return Y position after the paragraph.
     */
    Point paragraph(
        Point x,
        Point y,
        Point width,
        std::string_view value,
        Align align = Align::Left,
        TextStyle style = TextStyle{});

    /**
     * @brief Draw a heading.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param value Heading text.
     * @param level Heading level from 1 to 6.
     * @param color Heading color.
     * @return Y position after the heading.
     */
    Point heading(
        Point x,
        Point y,
        std::string_view value,
        int level = 1,
        Color color = Color::black());

    /**
     * @brief Draw a straight line.
     *
     * @return This page.
     */
    Page &line(
        Point x1,
        Point y1,
        Point x2,
        Point y2,
        Point width = 1.0F,
        Color color = Color::black(),
        LineStyle style = LineStyle::Solid);

    /**
     * @brief Draw a stroked rectangle.
     *
     * @return This page.
     */
    Page &rect(
        Point x,
        Point y,
        Point width,
        Point height,
        Point line_width = 1.0F,
        Color color = Color::black());

    /**
     * @brief Draw a filled rectangle.
     *
     * @return This page.
     */
    Page &fill_rect(
        Point x,
        Point y,
        Point width,
        Point height,
        Color color);

    /**
     * @brief Draw a filled and stroked rectangle.
     *
     * @return This page.
     */
    Page &fill_stroke_rect(
        Point x,
        Point y,
        Point width,
        Point height,
        Color fill_color,
        Color stroke_color,
        Point line_width = 1.0F);

    /**
     * @brief Draw a circle.
     *
     * @return This page.
     */
    Page &circle(
        Point cx,
        Point cy,
        Point radius,
        Point line_width = 1.0F,
        Color color = Color::black(),
        bool filled = false);

    /**
     * @brief Draw a horizontal rule.
     *
     * @return This page.
     */
    Page &hrule(
        Point y,
        Point x_start = -1.0F,
        Point x_end = -1.0F,
        Point width = 0.5F,
        Color color = Color::gray());

    /**
     * @brief Place an image.
     *
     * @return This page.
     */
    Page &image(
        const Image &image,
        Point x,
        Point y,
        Point width,
        Point height);

    /**
     * @brief Place an image while preserving aspect ratio.
     *
     * @return This page.
     */
    Page &image_fit(
        const Image &image,
        Point x,
        Point y,
        Point max_width,
        Point max_height);

    /**
     * @brief Draw a table.
     *
     * @param x X coordinate.
     * @param y Starting Y coordinate.
     * @param table Table to draw.
     * @return Y position below the table.
     */
    Point table(
        Point x,
        Point y,
        const Table &table);

    /**
     * @brief Draw a page number.
     *
     * @return This page.
     */
    Page &page_number(
        int number,
        int total = -1,
        Point y = -1.0F,
        TextStyle style = TextStyle::small());

    /**
     * @brief Return the internal PDF content stream.
     *
     * @return Content stream.
     */
    [[nodiscard]] const std::string &content_stream() const noexcept;

    /**
     * @brief Return fonts used by this page.
     *
     * @return Used fonts.
     */
    [[nodiscard]] const std::vector<Font> &fonts() const noexcept;

    /**
     * @brief Return images used by this page.
     *
     * @return Used images.
     */
    [[nodiscard]] const std::vector<const Image *> &images() const noexcept;

    /**
     * @brief Return the local font resource index.
     *
     * @param font Font.
     * @return One-based font index.
     */
    [[nodiscard]] int font_index(Font font) const noexcept;

  private:
    void use_font(Font font);
    int add_image(const Image &image);

    void set_line_style(LineStyle style, Point width);
    void reset_line_style(LineStyle style);

    void draw_cell_border(
        Point x,
        Point y,
        Point width,
        Point height,
        const BorderStyle &border);

    PageSize size_;
    Margins margins_;
    std::string content_;
    std::vector<Font> fonts_;
    std::vector<const Image *> images_;
  };
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_PAGE_HPP_INCLUDED
