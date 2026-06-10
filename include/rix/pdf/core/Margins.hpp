/**
 *
 *  @file Margins.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_MARGINS_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_MARGINS_HPP_INCLUDED

#include <rix/pdf/core/Units.hpp>

namespace rixlib::pdf
{
  /**
   * @brief Page margin values.
   *
   * Margins are expressed in PDF points.
   * One point is 1/72 inch.
   */
  class Margins
  {
  public:
    /**
     * @brief Construct default margins.
     *
     * The default margin is one inch on every side.
     */
    constexpr Margins() noexcept = default;

    /**
     * @brief Construct margins using the same value for every side.
     *
     * @param value Margin value in PDF points.
     */
    explicit constexpr Margins(Point value) noexcept
        : top_(clamp(value)),
          bottom_(clamp(value)),
          left_(clamp(value)),
          right_(clamp(value))
    {
    }

    /**
     * @brief Construct margins from explicit side values.
     *
     * Negative values are clamped to zero.
     *
     * @param top Top margin in PDF points.
     * @param bottom Bottom margin in PDF points.
     * @param left Left margin in PDF points.
     * @param right Right margin in PDF points.
     */
    constexpr Margins(
        Point top,
        Point bottom,
        Point left,
        Point right) noexcept
        : top_(clamp(top)),
          bottom_(clamp(bottom)),
          left_(clamp(left)),
          right_(clamp(right))
    {
    }

    /**
     * @brief Return the top margin.
     *
     * @return Top margin in PDF points.
     */
    [[nodiscard]] constexpr Point top() const noexcept
    {
      return top_;
    }

    /**
     * @brief Return the bottom margin.
     *
     * @return Bottom margin in PDF points.
     */
    [[nodiscard]] constexpr Point bottom() const noexcept
    {
      return bottom_;
    }

    /**
     * @brief Return the left margin.
     *
     * @return Left margin in PDF points.
     */
    [[nodiscard]] constexpr Point left() const noexcept
    {
      return left_;
    }

    /**
     * @brief Return the right margin.
     *
     * @return Right margin in PDF points.
     */
    [[nodiscard]] constexpr Point right() const noexcept
    {
      return right_;
    }

    /**
     * @brief Set the top margin.
     *
     * @param value Top margin in PDF points.
     */
    constexpr void set_top(Point value) noexcept
    {
      top_ = clamp(value);
    }

    /**
     * @brief Set the bottom margin.
     *
     * @param value Bottom margin in PDF points.
     */
    constexpr void set_bottom(Point value) noexcept
    {
      bottom_ = clamp(value);
    }

    /**
     * @brief Set the left margin.
     *
     * @param value Left margin in PDF points.
     */
    constexpr void set_left(Point value) noexcept
    {
      left_ = clamp(value);
    }

    /**
     * @brief Set the right margin.
     *
     * @param value Right margin in PDF points.
     */
    constexpr void set_right(Point value) noexcept
    {
      right_ = clamp(value);
    }

    /**
     * @brief Return default one-inch margins.
     *
     * @return Margins with one inch on every side.
     */
    [[nodiscard]] static constexpr Margins one_inch() noexcept
    {
      return Margins{inches(1.0F)};
    }

    /**
     * @brief Return zero margins.
     *
     * @return Margins with every side set to zero.
     */
    [[nodiscard]] static constexpr Margins none() noexcept
    {
      return Margins{0.0F};
    }

    /**
     * @brief Return margins from inch values.
     *
     * @param top Top margin in inches.
     * @param bottom Bottom margin in inches.
     * @param left Left margin in inches.
     * @param right Right margin in inches.
     * @return Margins converted to PDF points.
     */
    [[nodiscard]] static constexpr Margins from_inches(
        float top,
        float bottom,
        float left,
        float right) noexcept
    {
      return Margins{
          inches(top),
          inches(bottom),
          inches(left),
          inches(right)};
    }

    /**
     * @brief Return margins from millimeter values.
     *
     * @param top Top margin in millimeters.
     * @param bottom Bottom margin in millimeters.
     * @param left Left margin in millimeters.
     * @param right Right margin in millimeters.
     * @return Margins converted to PDF points.
     */
    [[nodiscard]] static constexpr Margins from_millimeters(
        float top,
        float bottom,
        float left,
        float right) noexcept
    {
      return Margins{
          millimeters(top),
          millimeters(bottom),
          millimeters(left),
          millimeters(right)};
    }

    /**
     * @brief Return true when all margins are zero.
     *
     * @return true if every side is zero.
     */
    [[nodiscard]] constexpr bool empty() const noexcept
    {
      return top_ == 0.0F &&
             bottom_ == 0.0F &&
             left_ == 0.0F &&
             right_ == 0.0F;
    }

    /**
     * @brief Return the total horizontal margin.
     *
     * @return Left margin plus right margin.
     */
    [[nodiscard]] constexpr Point horizontal() const noexcept
    {
      return left_ + right_;
    }

    /**
     * @brief Return the total vertical margin.
     *
     * @return Top margin plus bottom margin.
     */
    [[nodiscard]] constexpr Point vertical() const noexcept
    {
      return top_ + bottom_;
    }

    /**
     * @brief Return true when two margin values are equal.
     *
     * @param other Other margins.
     * @return true if all sides match.
     */
    [[nodiscard]] constexpr bool equals(const Margins &other) const noexcept
    {
      return top_ == other.top_ &&
             bottom_ == other.bottom_ &&
             left_ == other.left_ &&
             right_ == other.right_;
    }

  private:
    [[nodiscard]] static constexpr Point clamp(Point value) noexcept
    {
      return clamp_non_negative(value);
    }

    Point top_ = inches(1.0F);
    Point bottom_ = inches(1.0F);
    Point left_ = inches(1.0F);
    Point right_ = inches(1.0F);
  };

  /**
   * @brief Compare two margins for equality.
   *
   * @param left Left margins.
   * @param right Right margins.
   * @return true if both margins are equal.
   */
  [[nodiscard]] constexpr bool operator==(
      const Margins &left,
      const Margins &right) noexcept
  {
    return left.equals(right);
  }

  /**
   * @brief Compare two margins for inequality.
   *
   * @param left Left margins.
   * @param right Right margins.
   * @return true if the margins are different.
   */
  [[nodiscard]] constexpr bool operator!=(
      const Margins &left,
      const Margins &right) noexcept
  {
    return !(left == right);
  }

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_MARGINS_HPP_INCLUDED
