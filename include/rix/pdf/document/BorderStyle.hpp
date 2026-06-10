/**
 *
 *  @file BorderStyle.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_BORDERSTYLE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_BORDERSTYLE_HPP_INCLUDED

#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/LineStyle.hpp>
#include <rix/pdf/core/Units.hpp>

namespace rixlib::pdf
{
  /**
   * @brief Border rendering style.
   *
   * BorderStyle controls which sides are visible, the stroke width, stroke
   * color, and line style used by table cells and other bordered elements.
   */
  class BorderStyle
  {
  public:
    /**
     * @brief Construct the default border style.
     *
     * The default border enables all sides with a thin black solid line.
     */
    constexpr BorderStyle() noexcept = default;

    /**
     * @brief Construct a border style.
     *
     * Non-positive width values are normalized to 0.5pt.
     *
     * @param width Border width in PDF points.
     * @param color Border color.
     * @param line_style Border line style.
     */
    constexpr BorderStyle(
        Point width,
        Color color = Color::black(),
        LineStyle line_style = LineStyle::Solid) noexcept
        : width_(normalize_width(width)),
          color_(color),
          line_style_(line_style)
    {
    }

    /**
     * @brief Return true when the top border is enabled.
     *
     * @return true if the top border is enabled.
     */
    [[nodiscard]] constexpr bool top() const noexcept
    {
      return top_;
    }

    /**
     * @brief Enable or disable the top border.
     *
     * @param value true to enable the top border.
     */
    constexpr void set_top(bool value) noexcept
    {
      top_ = value;
    }

    /**
     * @brief Return true when the bottom border is enabled.
     *
     * @return true if the bottom border is enabled.
     */
    [[nodiscard]] constexpr bool bottom() const noexcept
    {
      return bottom_;
    }

    /**
     * @brief Enable or disable the bottom border.
     *
     * @param value true to enable the bottom border.
     */
    constexpr void set_bottom(bool value) noexcept
    {
      bottom_ = value;
    }

    /**
     * @brief Return true when the left border is enabled.
     *
     * @return true if the left border is enabled.
     */
    [[nodiscard]] constexpr bool left() const noexcept
    {
      return left_;
    }

    /**
     * @brief Enable or disable the left border.
     *
     * @param value true to enable the left border.
     */
    constexpr void set_left(bool value) noexcept
    {
      left_ = value;
    }

    /**
     * @brief Return true when the right border is enabled.
     *
     * @return true if the right border is enabled.
     */
    [[nodiscard]] constexpr bool right() const noexcept
    {
      return right_;
    }

    /**
     * @brief Enable or disable the right border.
     *
     * @param value true to enable the right border.
     */
    constexpr void set_right(bool value) noexcept
    {
      right_ = value;
    }

    /**
     * @brief Return the border width.
     *
     * @return Border width in PDF points.
     */
    [[nodiscard]] constexpr Point width() const noexcept
    {
      return width_;
    }

    /**
     * @brief Set the border width.
     *
     * Non-positive values are normalized to 0.5pt.
     *
     * @param value Border width in PDF points.
     */
    constexpr void set_width(Point value) noexcept
    {
      width_ = normalize_width(value);
    }

    /**
     * @brief Return the border color.
     *
     * @return Border color.
     */
    [[nodiscard]] constexpr Color color() const noexcept
    {
      return color_;
    }

    /**
     * @brief Set the border color.
     *
     * @param value Border color.
     */
    constexpr void set_color(Color value) noexcept
    {
      color_ = value;
    }

    /**
     * @brief Return the border line style.
     *
     * @return Border line style.
     */
    [[nodiscard]] constexpr LineStyle line_style() const noexcept
    {
      return line_style_;
    }

    /**
     * @brief Set the border line style.
     *
     * @param value Border line style.
     */
    constexpr void set_line_style(LineStyle value) noexcept
    {
      line_style_ = value;
    }

    /**
     * @brief Return true when at least one border side is enabled.
     *
     * @return true if any side is enabled.
     */
    [[nodiscard]] constexpr bool visible() const noexcept
    {
      return top_ || bottom_ || left_ || right_;
    }

    /**
     * @brief Return true when all border sides are enabled.
     *
     * @return true if every side is enabled.
     */
    [[nodiscard]] constexpr bool all_sides() const noexcept
    {
      return top_ && bottom_ && left_ && right_;
    }

    /**
     * @brief Enable all border sides.
     *
     * @return This border style.
     */
    constexpr BorderStyle &enable_all() noexcept
    {
      top_ = true;
      bottom_ = true;
      left_ = true;
      right_ = true;
      return *this;
    }

    /**
     * @brief Disable all border sides.
     *
     * @return This border style.
     */
    constexpr BorderStyle &disable_all() noexcept
    {
      top_ = false;
      bottom_ = false;
      left_ = false;
      right_ = false;
      return *this;
    }

    /**
     * @brief Return a copy with all sides enabled.
     *
     * @return Updated copy.
     */
    [[nodiscard]] constexpr BorderStyle with_all_sides() const noexcept
    {
      auto copy = *this;
      copy.enable_all();
      return copy;
    }

    /**
     * @brief Return a copy with all sides disabled.
     *
     * @return Updated copy.
     */
    [[nodiscard]] constexpr BorderStyle with_no_sides() const noexcept
    {
      auto copy = *this;
      copy.disable_all();
      return copy;
    }

    /**
     * @brief Return a copy with a different width.
     *
     * @param value Border width in PDF points.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr BorderStyle with_width(Point value) const noexcept
    {
      auto copy = *this;
      copy.set_width(value);
      return copy;
    }

    /**
     * @brief Return a copy with a different color.
     *
     * @param value Border color.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr BorderStyle with_color(Color value) const noexcept
    {
      auto copy = *this;
      copy.set_color(value);
      return copy;
    }

    /**
     * @brief Return a copy with a different line style.
     *
     * @param value Border line style.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr BorderStyle with_line_style(
        LineStyle value) const noexcept
    {
      auto copy = *this;
      copy.set_line_style(value);
      return copy;
    }

    /**
     * @brief Return the default thin border.
     *
     * @return Default border style.
     */
    [[nodiscard]] static constexpr BorderStyle thin() noexcept
    {
      return BorderStyle{};
    }

    /**
     * @brief Return a border with no visible sides.
     *
     * @return Border style with all sides disabled.
     */
    [[nodiscard]] static constexpr BorderStyle none() noexcept
    {
      BorderStyle style;
      style.disable_all();
      return style;
    }

    /**
     * @brief Return true when two border styles are equal.
     *
     * @param other Other border style.
     * @return true if all values match.
     */
    [[nodiscard]] constexpr bool equals(
        const BorderStyle &other) const noexcept
    {
      return top_ == other.top_ &&
             bottom_ == other.bottom_ &&
             left_ == other.left_ &&
             right_ == other.right_ &&
             width_ == other.width_ &&
             color_ == other.color_ &&
             line_style_ == other.line_style_;
    }

  private:
    [[nodiscard]] static constexpr Point normalize_width(Point value) noexcept
    {
      return value > 0.0F ? value : 0.5F;
    }

    bool top_ = true;
    bool bottom_ = true;
    bool left_ = true;
    bool right_ = true;

    Point width_ = 0.5F;
    Color color_ = Color::black();
    LineStyle line_style_ = LineStyle::Solid;
  };

  /**
   * @brief Compare two border styles for equality.
   *
   * @param left Left border style.
   * @param right Right border style.
   * @return true if both border styles are equal.
   */
  [[nodiscard]] constexpr bool operator==(
      const BorderStyle &left,
      const BorderStyle &right) noexcept
  {
    return left.equals(right);
  }

  /**
   * @brief Compare two border styles for inequality.
   *
   * @param left Left border style.
   * @param right Right border style.
   * @return true if the border styles are different.
   */
  [[nodiscard]] constexpr bool operator!=(
      const BorderStyle &left,
      const BorderStyle &right) noexcept
  {
    return !(left == right);
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_BORDERSTYLE_HPP_INCLUDED
