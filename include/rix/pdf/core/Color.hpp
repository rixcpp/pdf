/**
 *
 *  @file Color.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_COLOR_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_COLOR_HPP_INCLUDED

#include <cstdint>

namespace rixlib::pdf
{
  /**
   * @brief RGB color value.
   *
   * Color stores red, green, and blue channels as floating-point values
   * normalized between 0.0 and 1.0.
   */
  class Color
  {
  public:
    /**
     * @brief Construct black.
     */
    constexpr Color() noexcept = default;

    /**
     * @brief Construct a color from normalized RGB components.
     *
     * Values are clamped to the valid PDF color range [0.0, 1.0].
     *
     * @param red Red component.
     * @param green Green component.
     * @param blue Blue component.
     */
    constexpr Color(float red, float green, float blue) noexcept
        : red_(clamp(red)),
          green_(clamp(green)),
          blue_(clamp(blue))
    {
    }

    /**
     * @brief Return the red component.
     *
     * @return Red component in the range [0.0, 1.0].
     */
    [[nodiscard]] constexpr float red() const noexcept
    {
      return red_;
    }

    /**
     * @brief Return the green component.
     *
     * @return Green component in the range [0.0, 1.0].
     */
    [[nodiscard]] constexpr float green() const noexcept
    {
      return green_;
    }

    /**
     * @brief Return the blue component.
     *
     * @return Blue component in the range [0.0, 1.0].
     */
    [[nodiscard]] constexpr float blue() const noexcept
    {
      return blue_;
    }

    /**
     * @brief Set the red component.
     *
     * @param value Red component.
     */
    constexpr void set_red(float value) noexcept
    {
      red_ = clamp(value);
    }

    /**
     * @brief Set the green component.
     *
     * @param value Green component.
     */
    constexpr void set_green(float value) noexcept
    {
      green_ = clamp(value);
    }

    /**
     * @brief Set the blue component.
     *
     * @param value Blue component.
     */
    constexpr void set_blue(float value) noexcept
    {
      blue_ = clamp(value);
    }

    /**
     * @brief Return black.
     *
     * @return Black color.
     */
    [[nodiscard]] static constexpr Color black() noexcept
    {
      return Color{0.0F, 0.0F, 0.0F};
    }

    /**
     * @brief Return white.
     *
     * @return White color.
     */
    [[nodiscard]] static constexpr Color white() noexcept
    {
      return Color{1.0F, 1.0F, 1.0F};
    }

    /**
     * @brief Return red.
     *
     * @return Red color.
     */
    [[nodiscard]] static constexpr Color red_color() noexcept
    {
      return Color{1.0F, 0.0F, 0.0F};
    }

    /**
     * @brief Return green.
     *
     * @return Green color.
     */
    [[nodiscard]] static constexpr Color green_color() noexcept
    {
      return Color{0.0F, 0.5F, 0.0F};
    }

    /**
     * @brief Return blue.
     *
     * @return Blue color.
     */
    [[nodiscard]] static constexpr Color blue_color() noexcept
    {
      return Color{0.0F, 0.0F, 1.0F};
    }

    /**
     * @brief Return gray.
     *
     * @return Gray color.
     */
    [[nodiscard]] static constexpr Color gray() noexcept
    {
      return Color{0.5F, 0.5F, 0.5F};
    }

    /**
     * @brief Return light gray.
     *
     * @return Light gray color.
     */
    [[nodiscard]] static constexpr Color light_gray() noexcept
    {
      return Color{0.85F, 0.85F, 0.85F};
    }

    /**
     * @brief Create a color from a hexadecimal RGB value.
     *
     * Example:
     *
     * @code
     * auto color = Color::from_hex(0x2C3E50);
     * @endcode
     *
     * @param value Hexadecimal RGB value.
     * @return Color.
     */
    [[nodiscard]] static constexpr Color from_hex(std::uint32_t value) noexcept
    {
      return Color{
          static_cast<float>((value >> 16U) & 0xFFU) / 255.0F,
          static_cast<float>((value >> 8U) & 0xFFU) / 255.0F,
          static_cast<float>(value & 0xFFU) / 255.0F};
    }

    /**
     * @brief Return true when two colors are equal.
     *
     * @param other Other color.
     * @return true if both colors have the same components.
     */
    [[nodiscard]] constexpr bool equals(const Color &other) const noexcept
    {
      return red_ == other.red_ &&
             green_ == other.green_ &&
             blue_ == other.blue_;
    }

  private:
    [[nodiscard]] static constexpr float clamp(float value) noexcept
    {
      if (value < 0.0F)
      {
        return 0.0F;
      }

      if (value > 1.0F)
      {
        return 1.0F;
      }

      return value;
    }

    float red_ = 0.0F;
    float green_ = 0.0F;
    float blue_ = 0.0F;
  };

  /**
   * @brief Compare two colors for equality.
   *
   * @param left Left color.
   * @param right Right color.
   * @return true if both colors are equal.
   */
  [[nodiscard]] constexpr bool operator==(
      const Color &left,
      const Color &right) noexcept
  {
    return left.equals(right);
  }

  /**
   * @brief Compare two colors for inequality.
   *
   * @param left Left color.
   * @param right Right color.
   * @return true if the colors are different.
   */
  [[nodiscard]] constexpr bool operator!=(
      const Color &left,
      const Color &right) noexcept
  {
    return !(left == right);
  }

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_COLOR_HPP_INCLUDED
