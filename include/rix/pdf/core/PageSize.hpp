/**
 *
 *  @file PageSize.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_PAGESIZE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_PAGESIZE_HPP_INCLUDED

#include <rix/pdf/core/Units.hpp>

namespace rixlib::pdf
{
  /**
   * @brief PDF page size.
   *
   * Page sizes are expressed in PDF points.
   * One point is 1/72 inch.
   */
  class PageSize
  {
  public:
    /**
     * @brief Construct an A4 page size.
     */
    constexpr PageSize() noexcept = default;

    /**
     * @brief Construct a custom page size.
     *
     * Negative values are clamped to zero.
     *
     * @param width Page width in PDF points.
     * @param height Page height in PDF points.
     */
    constexpr PageSize(Point width, Point height) noexcept
        : width_(clamp(width)),
          height_(clamp(height))
    {
    }

    /**
     * @brief Return the page width.
     *
     * @return Width in PDF points.
     */
    [[nodiscard]] constexpr Point width() const noexcept
    {
      return width_;
    }

    /**
     * @brief Return the page height.
     *
     * @return Height in PDF points.
     */
    [[nodiscard]] constexpr Point height() const noexcept
    {
      return height_;
    }

    /**
     * @brief Set the page width.
     *
     * Negative values are clamped to zero.
     *
     * @param value Width in PDF points.
     */
    constexpr void set_width(Point value) noexcept
    {
      width_ = clamp(value);
    }

    /**
     * @brief Set the page height.
     *
     * Negative values are clamped to zero.
     *
     * @param value Height in PDF points.
     */
    constexpr void set_height(Point value) noexcept
    {
      height_ = clamp(value);
    }

    /**
     * @brief Return true when the page size has positive width and height.
     *
     * @return true if width and height are greater than zero.
     */
    [[nodiscard]] constexpr bool valid() const noexcept
    {
      return width_ > 0.0F && height_ > 0.0F;
    }

    /**
     * @brief Return true when the page is landscape.
     *
     * @return true if width is greater than height.
     */
    [[nodiscard]] constexpr bool landscape() const noexcept
    {
      return width_ > height_;
    }

    /**
     * @brief Return true when the page is portrait.
     *
     * @return true if height is greater than or equal to width.
     */
    [[nodiscard]] constexpr bool portrait() const noexcept
    {
      return !landscape();
    }

    /**
     * @brief Return a landscape version of the page size.
     *
     * @return Landscape page size.
     */
    [[nodiscard]] constexpr PageSize as_landscape() const noexcept
    {
      return width_ >= height_
                 ? *this
                 : PageSize{height_, width_};
    }

    /**
     * @brief Return a portrait version of the page size.
     *
     * @return Portrait page size.
     */
    [[nodiscard]] constexpr PageSize as_portrait() const noexcept
    {
      return height_ >= width_
                 ? *this
                 : PageSize{height_, width_};
    }

    /**
     * @brief Return true when two page sizes are equal.
     *
     * @param other Other page size.
     * @return true if both width and height match.
     */
    [[nodiscard]] constexpr bool equals(const PageSize &other) const noexcept
    {
      return width_ == other.width_ &&
             height_ == other.height_;
    }

    /**
     * @brief Return the A4 page size.
     *
     * @return A4 page size.
     */
    [[nodiscard]] static constexpr PageSize A4() noexcept
    {
      return PageSize{595.28F, 841.89F};
    }

    /**
     * @brief Return the A3 page size.
     *
     * @return A3 page size.
     */
    [[nodiscard]] static constexpr PageSize A3() noexcept
    {
      return PageSize{841.89F, 1190.55F};
    }

    /**
     * @brief Return the Letter page size.
     *
     * @return Letter page size.
     */
    [[nodiscard]] static constexpr PageSize Letter() noexcept
    {
      return PageSize{612.0F, 792.0F};
    }

    /**
     * @brief Return the Legal page size.
     *
     * @return Legal page size.
     */
    [[nodiscard]] static constexpr PageSize Legal() noexcept
    {
      return PageSize{612.0F, 1008.0F};
    }

    /**
     * @brief Return a custom page size.
     *
     * @param width Page width in PDF points.
     * @param height Page height in PDF points.
     * @return Custom page size.
     */
    [[nodiscard]] static constexpr PageSize custom(
        Point width,
        Point height) noexcept
    {
      return PageSize{width, height};
    }

    /**
     * @brief Return a custom page size from inch values.
     *
     * @param width Width in inches.
     * @param height Height in inches.
     * @return Custom page size converted to PDF points.
     */
    [[nodiscard]] static constexpr PageSize from_inches(
        float width,
        float height) noexcept
    {
      return PageSize{
          inches(width),
          inches(height)};
    }

    /**
     * @brief Return a custom page size from millimeter values.
     *
     * @param width Width in millimeters.
     * @param height Height in millimeters.
     * @return Custom page size converted to PDF points.
     */
    [[nodiscard]] static constexpr PageSize from_millimeters(
        float width,
        float height) noexcept
    {
      return PageSize{
          millimeters(width),
          millimeters(height)};
    }

  private:
    [[nodiscard]] static constexpr Point clamp(Point value) noexcept
    {
      return clamp_non_negative(value);
    }

    Point width_ = 595.28F;
    Point height_ = 841.89F;
  };

  /**
   * @brief Compare two page sizes for equality.
   *
   * @param left Left page size.
   * @param right Right page size.
   * @return true if both page sizes are equal.
   */
  [[nodiscard]] constexpr bool operator==(
      const PageSize &left,
      const PageSize &right) noexcept
  {
    return left.equals(right);
  }

  /**
   * @brief Compare two page sizes for inequality.
   *
   * @param left Left page size.
   * @param right Right page size.
   * @return true if the page sizes are different.
   */
  [[nodiscard]] constexpr bool operator!=(
      const PageSize &left,
      const PageSize &right) noexcept
  {
    return !(left == right);
  }

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_PAGESIZE_HPP_INCLUDED
