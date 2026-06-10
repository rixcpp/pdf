/**
 *
 *  @file Image.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_IMAGE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_IMAGE_HPP_INCLUDED

#include <rix/pdf/core/Result.hpp>
#include <rix/pdf/core/Units.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace rixlib::pdf
{
  /**
   * @brief Supported image format.
   */
  enum class ImageFormat : std::uint8_t
  {
    Jpeg
  };

  /**
   * @brief PDF image color space.
   */
  enum class ImageColorSpace : std::uint8_t
  {
    DeviceGray,
    DeviceRGB,
    DeviceCMYK
  };

  /**
   * @brief Image data that can be embedded in a PDF document.
   *
   * The first implementation supports JPEG images. Image loading returns
   * PdfResult instead of throwing exceptions so applications can handle
   * errors explicitly.
   */
  class Image
  {
  public:
    /**
     * @brief Construct an empty image.
     */
    Image() = default;

    /**
     * @brief Construct an image from validated data.
     *
     * @param format Image format.
     * @param data Encoded image bytes.
     * @param width Image width in pixels.
     * @param height Image height in pixels.
     * @param components Number of color components.
     */
    Image(
        ImageFormat format,
        std::vector<std::uint8_t> data,
        int width,
        int height,
        int components);

    /**
     * @brief Load a JPEG image from a file.
     *
     * @param path File path.
     * @return Image on success, PdfError on failure.
     */
    [[nodiscard]] static PdfResult<Image> load_jpeg(
        std::string_view path);

    /**
     * @brief Create a JPEG image from encoded bytes.
     *
     * @param bytes JPEG bytes.
     * @return Image on success, PdfError on failure.
     */
    [[nodiscard]] static PdfResult<Image> from_jpeg_bytes(
        std::vector<std::uint8_t> bytes);

    /**
     * @brief Return true when this image contains usable data.
     *
     * @return true if the image has bytes and positive dimensions.
     */
    [[nodiscard]] bool valid() const noexcept;

    /**
     * @brief Return the image format.
     *
     * @return Image format.
     */
    [[nodiscard]] ImageFormat format() const noexcept;

    /**
     * @brief Return the encoded image bytes.
     *
     * @return Image bytes.
     */
    [[nodiscard]] const std::vector<std::uint8_t> &data() const noexcept;

    /**
     * @brief Return the image width in pixels.
     *
     * @return Image width.
     */
    [[nodiscard]] int width() const noexcept;

    /**
     * @brief Return the image height in pixels.
     *
     * @return Image height.
     */
    [[nodiscard]] int height() const noexcept;

    /**
     * @brief Return the number of color components.
     *
     * Common values are 1 for gray, 3 for RGB, and 4 for CMYK.
     *
     * @return Component count.
     */
    [[nodiscard]] int components() const noexcept;

    /**
     * @brief Return the PDF color space for this image.
     *
     * @return PDF image color space.
     */
    [[nodiscard]] ImageColorSpace color_space() const noexcept;

    /**
     * @brief Return the image aspect ratio.
     *
     * @return width divided by height, or 0 for invalid dimensions.
     */
    [[nodiscard]] float aspect_ratio() const noexcept;

    /**
     * @brief Return true when this image is grayscale.
     *
     * @return true if components is 1.
     */
    [[nodiscard]] bool grayscale() const noexcept;

    /**
     * @brief Return true when this image is RGB.
     *
     * @return true if components is 3.
     */
    [[nodiscard]] bool rgb() const noexcept;

    /**
     * @brief Return true when this image is CMYK.
     *
     * @return true if components is 4.
     */
    [[nodiscard]] bool cmyk() const noexcept;

  private:
    struct JpegInfo
    {
      int width = 0;
      int height = 0;
      int components = 0;
    };

    [[nodiscard]] static PdfResult<JpegInfo> parse_jpeg_info(
        const std::vector<std::uint8_t> &data);

    ImageFormat format_ = ImageFormat::Jpeg;
    std::vector<std::uint8_t> data_;
    int width_ = 0;
    int height_ = 0;
    int components_ = 0;
  };

  /**
   * @brief Convert an image format to a stable string.
   *
   * @param format Image format.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(ImageFormat format) noexcept;

  /**
   * @brief Convert an image color space to a PDF color space name.
   *
   * @param color_space Image color space.
   * @return PDF color space name.
   */
  [[nodiscard]] std::string_view pdf_color_space_name(
      ImageColorSpace color_space) noexcept;

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_IMAGE_HPP_INCLUDED
