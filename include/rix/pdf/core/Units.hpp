/**
 *
 *  @file Units.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_UNITS_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_UNITS_HPP_INCLUDED

namespace rixlib::pdf
{
  /**
   * @brief PDF point value.
   *
   * PDF coordinates are expressed in points.
   * One point is 1/72 inch.
   */
  using Point = float;

  /**
   * @brief Number of PDF points per inch.
   */
  inline constexpr Point POINTS_PER_INCH = 72.0F;

  /**
   * @brief Number of millimeters per inch.
   */
  inline constexpr float MILLIMETERS_PER_INCH = 25.4F;

  /**
   * @brief Convert inches to PDF points.
   *
   * @param value Value in inches.
   * @return Value in PDF points.
   */
  [[nodiscard]] constexpr Point inches(float value) noexcept
  {
    return value * POINTS_PER_INCH;
  }

  /**
   * @brief Convert millimeters to PDF points.
   *
   * @param value Value in millimeters.
   * @return Value in PDF points.
   */
  [[nodiscard]] constexpr Point millimeters(float value) noexcept
  {
    return value * POINTS_PER_INCH / MILLIMETERS_PER_INCH;
  }

  /**
   * @brief Convert centimeters to PDF points.
   *
   * @param value Value in centimeters.
   * @return Value in PDF points.
   */
  [[nodiscard]] constexpr Point centimeters(float value) noexcept
  {
    return millimeters(value * 10.0F);
  }

  /**
   * @brief Convert PDF points to inches.
   *
   * @param value Value in PDF points.
   * @return Value in inches.
   */
  [[nodiscard]] constexpr float points_to_inches(Point value) noexcept
  {
    return value / POINTS_PER_INCH;
  }

  /**
   * @brief Convert PDF points to millimeters.
   *
   * @param value Value in PDF points.
   * @return Value in millimeters.
   */
  [[nodiscard]] constexpr float points_to_millimeters(Point value) noexcept
  {
    return value * MILLIMETERS_PER_INCH / POINTS_PER_INCH;
  }

  /**
   * @brief Convert PDF points to centimeters.
   *
   * @param value Value in PDF points.
   * @return Value in centimeters.
   */
  [[nodiscard]] constexpr float points_to_centimeters(Point value) noexcept
  {
    return points_to_millimeters(value) / 10.0F;
  }

  /**
   * @brief Return true when a point value is positive.
   *
   * @param value Point value.
   * @return true if value is greater than zero.
   */
  [[nodiscard]] constexpr bool is_positive(Point value) noexcept
  {
    return value > 0.0F;
  }

  /**
   * @brief Return true when a point value is zero or positive.
   *
   * @param value Point value.
   * @return true if value is greater than or equal to zero.
   */
  [[nodiscard]] constexpr bool is_non_negative(Point value) noexcept
  {
    return value >= 0.0F;
  }

  /**
   * @brief Clamp a point value to zero when it is negative.
   *
   * @param value Point value.
   * @return Non-negative point value.
   */
  [[nodiscard]] constexpr Point clamp_non_negative(Point value) noexcept
  {
    return value < 0.0F ? 0.0F : value;
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_UNITS_HPP_INCLUDED
