/**
 *
 *  @file Image.cpp
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

#include <rix/pdf/document/Image.hpp>

#include <fstream>
#include <iterator>
#include <string>
#include <utility>

namespace rixlib::pdf
{
  namespace
  {
    [[nodiscard]] PdfError invalid_image_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::InvalidImage,
          std::move(message));
    }

    [[nodiscard]] PdfError unsupported_image_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::UnsupportedImageFormat,
          std::move(message));
    }

    [[nodiscard]] PdfError file_open_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::FileOpenFailed,
          std::move(message));
    }

    [[nodiscard]] bool is_standalone_jpeg_marker(std::uint8_t marker) noexcept
    {
      return marker == 0x01 ||
             (marker >= 0xD0 && marker <= 0xD9);
    }

    [[nodiscard]] bool is_jpeg_start_of_frame(std::uint8_t marker) noexcept
    {
      return (marker >= 0xC0 && marker <= 0xC3) ||
             (marker >= 0xC5 && marker <= 0xC7) ||
             (marker >= 0xC9 && marker <= 0xCB) ||
             (marker >= 0xCD && marker <= 0xCF);
    }

    [[nodiscard]] std::uint16_t read_be_u16(
        const std::vector<std::uint8_t> &data,
        std::size_t offset) noexcept
    {
      return static_cast<std::uint16_t>(
          (static_cast<std::uint16_t>(data[offset]) << 8U) |
          static_cast<std::uint16_t>(data[offset + 1U]));
    }
  } // namespace

  Image::Image(
      ImageFormat format,
      std::vector<std::uint8_t> data,
      int width,
      int height,
      int components)
      : format_(format),
        data_(std::move(data)),
        width_(width),
        height_(height),
        components_(components)
  {
  }

  PdfResult<Image> Image::load_jpeg(std::string_view path)
  {
    if (path.empty())
    {
      return PdfResult<Image>::failure(
          invalid_image_error("Image path cannot be empty."));
    }

    std::ifstream file(std::string(path), std::ios::binary);

    if (!file)
    {
      return PdfResult<Image>::failure(
          file_open_error("Cannot open image file."));
    }

    std::vector<std::uint8_t> bytes{
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()};

    return from_jpeg_bytes(std::move(bytes));
  }

  PdfResult<Image> Image::from_jpeg_bytes(std::vector<std::uint8_t> bytes)
  {
    auto info = parse_jpeg_info(bytes);

    if (info.failed())
    {
      return PdfResult<Image>::failure(info.error());
    }

    return PdfResult<Image>::success(
        Image{
            ImageFormat::Jpeg,
            std::move(bytes),
            info.value().width,
            info.value().height,
            info.value().components});
  }

  bool Image::valid() const noexcept
  {
    return !data_.empty() &&
           width_ > 0 &&
           height_ > 0 &&
           components_ > 0;
  }

  ImageFormat Image::format() const noexcept
  {
    return format_;
  }

  const std::vector<std::uint8_t> &Image::data() const noexcept
  {
    return data_;
  }

  int Image::width() const noexcept
  {
    return width_;
  }

  int Image::height() const noexcept
  {
    return height_;
  }

  int Image::components() const noexcept
  {
    return components_;
  }

  ImageColorSpace Image::color_space() const noexcept
  {
    if (components_ == 1)
    {
      return ImageColorSpace::DeviceGray;
    }

    if (components_ == 4)
    {
      return ImageColorSpace::DeviceCMYK;
    }

    return ImageColorSpace::DeviceRGB;
  }

  float Image::aspect_ratio() const noexcept
  {
    if (width_ <= 0 || height_ <= 0)
    {
      return 0.0F;
    }

    return static_cast<float>(width_) / static_cast<float>(height_);
  }

  bool Image::grayscale() const noexcept
  {
    return components_ == 1;
  }

  bool Image::rgb() const noexcept
  {
    return components_ == 3;
  }

  bool Image::cmyk() const noexcept
  {
    return components_ == 4;
  }

  PdfResult<Image::JpegInfo> Image::parse_jpeg_info(
      const std::vector<std::uint8_t> &data)
  {
    if (data.size() < 4)
    {
      return PdfResult<JpegInfo>::failure(
          invalid_image_error("JPEG data is too small."));
    }

    if (data[0] != 0xFF || data[1] != 0xD8)
    {
      return PdfResult<JpegInfo>::failure(
          unsupported_image_error("Image data is not a JPEG file."));
    }

    std::size_t offset = 2;

    while (offset + 1 < data.size())
    {
      if (data[offset] != 0xFF)
      {
        ++offset;
        continue;
      }

      while (offset < data.size() && data[offset] == 0xFF)
      {
        ++offset;
      }

      if (offset >= data.size())
      {
        break;
      }

      const std::uint8_t marker = data[offset++];

      if (marker == 0xD9 || marker == 0xDA)
      {
        break;
      }

      if (is_standalone_jpeg_marker(marker))
      {
        continue;
      }

      if (offset + 1 >= data.size())
      {
        return PdfResult<JpegInfo>::failure(
            invalid_image_error("JPEG marker length is truncated."));
      }

      const std::uint16_t segment_length = read_be_u16(data, offset);

      if (segment_length < 2)
      {
        return PdfResult<JpegInfo>::failure(
            invalid_image_error("JPEG segment length is invalid."));
      }

      if (offset + segment_length > data.size())
      {
        return PdfResult<JpegInfo>::failure(
            invalid_image_error("JPEG segment is truncated."));
      }

      if (is_jpeg_start_of_frame(marker))
      {
        if (segment_length < 8)
        {
          return PdfResult<JpegInfo>::failure(
              invalid_image_error("JPEG frame header is truncated."));
        }

        const std::size_t frame = offset + 2;

        JpegInfo info;
        info.height = static_cast<int>(read_be_u16(data, frame + 1));
        info.width = static_cast<int>(read_be_u16(data, frame + 3));
        info.components = static_cast<int>(data[frame + 5]);

        if (info.width <= 0 || info.height <= 0)
        {
          return PdfResult<JpegInfo>::failure(
              invalid_image_error("JPEG dimensions are invalid."));
        }

        if (info.components != 1 &&
            info.components != 3 &&
            info.components != 4)
        {
          return PdfResult<JpegInfo>::failure(
              invalid_image_error("JPEG color component count is unsupported."));
        }

        return PdfResult<JpegInfo>::success(info);
      }

      offset += segment_length;
    }

    return PdfResult<JpegInfo>::failure(
        invalid_image_error("Could not find JPEG dimensions."));
  }

  std::string_view to_string(ImageFormat format) noexcept
  {
    switch (format)
    {
    case ImageFormat::Jpeg:
      return "Jpeg";
    }

    return "Jpeg";
  }

  std::string_view pdf_color_space_name(
      ImageColorSpace color_space) noexcept
  {
    switch (color_space)
    {
    case ImageColorSpace::DeviceGray:
      return "DeviceGray";
    case ImageColorSpace::DeviceRGB:
      return "DeviceRGB";
    case ImageColorSpace::DeviceCMYK:
      return "DeviceCMYK";
    }

    return "DeviceRGB";
  }
} // namespace rixlib::pdf
