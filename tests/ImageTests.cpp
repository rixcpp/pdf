/**
 *
 *  @file ImageTests.cpp
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

#include <cassert>
#include <cstdint>
#include <vector>

namespace
{
  std::vector<std::uint8_t> minimal_jpeg()
  {
    return {
        0xFF, 0xD8,

        0xFF, 0xC0,
        0x00, 0x11,
        0x08,
        0x00, 0x10,
        0x00, 0x20,
        0x03,
        0x01, 0x11, 0x00,
        0x02, 0x11, 0x00,
        0x03, 0x11, 0x00,

        0xFF, 0xD9};
  }
}

int main()
{
  using namespace rixlib::pdf;

  Image empty;

  assert(!empty.valid());
  assert(empty.format() == ImageFormat::Jpeg);
  assert(empty.width() == 0);
  assert(empty.height() == 0);
  assert(empty.components() == 0);
  assert(empty.color_space() == ImageColorSpace::DeviceRGB);
  assert(empty.aspect_ratio() == 0.0F);

  auto image = Image::from_jpeg_bytes(minimal_jpeg());

  assert(image.ok());
  assert(image.value().valid());
  assert(image.value().format() == ImageFormat::Jpeg);
  assert(image.value().width() == 32);
  assert(image.value().height() == 16);
  assert(image.value().components() == 3);
  assert(image.value().rgb());
  assert(!image.value().grayscale());
  assert(!image.value().cmyk());
  assert(image.value().color_space() == ImageColorSpace::DeviceRGB);
  assert(image.value().aspect_ratio() == 2.0F);
  assert(!image.value().data().empty());

  auto invalid = Image::from_jpeg_bytes({0x00, 0x01, 0x02});

  assert(invalid.failed());
  assert(invalid.error().is(PdfErrorCode::InvalidImage));

  auto not_jpeg = Image::from_jpeg_bytes({0x00, 0x01, 0x02, 0x03});

  assert(not_jpeg.failed());
  assert(not_jpeg.error().is(PdfErrorCode::UnsupportedImageFormat));

  auto missing = Image::load_jpeg("");

  assert(missing.failed());
  assert(missing.error().is(PdfErrorCode::InvalidImage));

  assert(to_string(ImageFormat::Jpeg) == "Jpeg");
  assert(pdf_color_space_name(ImageColorSpace::DeviceGray) == "DeviceGray");
  assert(pdf_color_space_name(ImageColorSpace::DeviceRGB) == "DeviceRGB");
  assert(pdf_color_space_name(ImageColorSpace::DeviceCMYK) == "DeviceCMYK");

  return 0;
}
