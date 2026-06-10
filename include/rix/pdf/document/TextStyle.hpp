/**
 *
 *  @file TextStyle.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TEXTSTYLE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TEXTSTYLE_HPP_INCLUDED

#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/Units.hpp>

namespace rixlib::pdf
{
  /**
   * @brief Text rendering style.
   *
   * TextStyle controls the font, font size, color, and line height used by
   * text drawing operations.
   */
  class TextStyle
  {
  public:
    /**
     * @brief Construct the default text style.
     *
     * The default style uses Helvetica, 12pt, black color, and a 1.2 line
     * height multiplier.
     */
    constexpr TextStyle() noexcept = default;

    /**
     * @brief Construct a text style.
     *
     * Invalid size and line-height values are normalized to safe defaults.
     *
     * @param font Text font.
     * @param size Font size in PDF points.
     * @param color Text color.
     * @param line_height Line height multiplier.
     */
    constexpr TextStyle(
        Font font,
        Point size,
        Color color = Color::black(),
        float line_height = 1.2F) noexcept
        : font_(font),
          size_(normalize_size(size)),
          color_(color),
          line_height_(normalize_line_height(line_height))
    {
    }

    /**
     * @brief Return the text font.
     *
     * @return Text font.
     */
    [[nodiscard]] constexpr Font font() const noexcept
    {
      return font_;
    }

    /**
     * @brief Set the text font.
     *
     * @param value Text font.
     */
    constexpr void set_font(Font value) noexcept
    {
      font_ = value;
    }

    /**
     * @brief Return the font size.
     *
     * @return Font size in PDF points.
     */
    [[nodiscard]] constexpr Point size() const noexcept
    {
      return size_;
    }

    /**
     * @brief Set the font size.
     *
     * Non-positive values are normalized to 12pt.
     *
     * @param value Font size in PDF points.
     */
    constexpr void set_size(Point value) noexcept
    {
      size_ = normalize_size(value);
    }

    /**
     * @brief Return the text color.
     *
     * @return Text color.
     */
    [[nodiscard]] constexpr Color color() const noexcept
    {
      return color_;
    }

    /**
     * @brief Set the text color.
     *
     * @param value Text color.
     */
    constexpr void set_color(Color value) noexcept
    {
      color_ = value;
    }

    /**
     * @brief Return the line height multiplier.
     *
     * @return Line height multiplier.
     */
    [[nodiscard]] constexpr float line_height() const noexcept
    {
      return line_height_;
    }

    /**
     * @brief Set the line height multiplier.
     *
     * Non-positive values are normalized to 1.2.
     *
     * @param value Line height multiplier.
     */
    constexpr void set_line_height(float value) noexcept
    {
      line_height_ = normalize_line_height(value);
    }

    /**
     * @brief Return the computed line advance.
     *
     * @return Font size multiplied by line height.
     */
    [[nodiscard]] constexpr Point line_advance() const noexcept
    {
      return size_ * line_height_;
    }

    /**
     * @brief Return a copy with a different font.
     *
     * @param value Text font.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr TextStyle with_font(Font value) const noexcept
    {
      auto copy = *this;
      copy.set_font(value);
      return copy;
    }

    /**
     * @brief Return a copy with a different font size.
     *
     * @param value Font size in PDF points.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr TextStyle with_size(Point value) const noexcept
    {
      auto copy = *this;
      copy.set_size(value);
      return copy;
    }

    /**
     * @brief Return a copy with a different color.
     *
     * @param value Text color.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr TextStyle with_color(Color value) const noexcept
    {
      auto copy = *this;
      copy.set_color(value);
      return copy;
    }

    /**
     * @brief Return a copy with a different line height.
     *
     * @param value Line height multiplier.
     * @return Updated copy.
     */
    [[nodiscard]] constexpr TextStyle with_line_height(float value) const noexcept
    {
      auto copy = *this;
      copy.set_line_height(value);
      return copy;
    }

    /**
     * @brief Return the default text style.
     *
     * @return Default text style.
     */
    [[nodiscard]] static constexpr TextStyle normal() noexcept
    {
      return TextStyle{};
    }

    /**
     * @brief Return a heading style.
     *
     * @return Heading text style.
     */
    [[nodiscard]] static constexpr TextStyle heading() noexcept
    {
      return TextStyle{
          Font::HelveticaBold,
          24.0F,
          Color::black(),
          1.2F};
    }

    /**
     * @brief Return a small text style.
     *
     * @return Small text style.
     */
    [[nodiscard]] static constexpr TextStyle small() noexcept
    {
      return TextStyle{
          Font::Helvetica,
          9.0F,
          Color::black(),
          1.2F};
    }

    /**
     * @brief Return true when two text styles are equal.
     *
     * @param other Other text style.
     * @return true if all style values match.
     */
    [[nodiscard]] constexpr bool equals(const TextStyle &other) const noexcept
    {
      return font_ == other.font_ &&
             size_ == other.size_ &&
             color_ == other.color_ &&
             line_height_ == other.line_height_;
    }

  private:
    [[nodiscard]] static constexpr Point normalize_size(Point value) noexcept
    {
      return value > 0.0F ? value : 12.0F;
    }

    [[nodiscard]] static constexpr float normalize_line_height(float value) noexcept
    {
      return value > 0.0F ? value : 1.2F;
    }

    Font font_ = Font::Helvetica;
    Point size_ = 12.0F;
    Color color_ = Color::black();
    float line_height_ = 1.2F;
  };

  /**
   * @brief Compare two text styles for equality.
   *
   * @param left Left text style.
   * @param right Right text style.
   * @return true if both text styles are equal.
   */
  [[nodiscard]] constexpr bool operator==(
      const TextStyle &left,
      const TextStyle &right) noexcept
  {
    return left.equals(right);
  }

  /**
   * @brief Compare two text styles for inequality.
   *
   * @param left Left text style.
   * @param right Right text style.
   * @return true if the text styles are different.
   */
  [[nodiscard]] constexpr bool operator!=(
      const TextStyle &left,
      const TextStyle &right) noexcept
  {
    return !(left == right);
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_TEXTSTYLE_HPP_INCLUDED
