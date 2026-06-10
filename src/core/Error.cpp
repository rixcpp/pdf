/**
 *
 *  @file Error.cpp
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

#include <rix/pdf/core/Error.hpp>
#include <utility>

namespace rixlib::pdf
{
  PdfError::PdfError(PdfErrorCode code, std::string message)
      : code_(code),
        message_(std::move(message))
  {
  }

  bool PdfError::ok() const noexcept
  {
    return code_ == PdfErrorCode::None;
  }

  bool PdfError::has_error() const noexcept
  {
    return !ok();
  }

  PdfErrorCode PdfError::code() const noexcept
  {
    return code_;
  }

  const std::string &PdfError::message() const noexcept
  {
    return message_;
  }

  bool PdfError::is(PdfErrorCode code) const noexcept
  {
    return code_ == code;
  }

  std::string_view to_string(PdfErrorCode code) noexcept
  {
    switch (code)
    {
    case PdfErrorCode::None:
      return "None";

    case PdfErrorCode::InvalidInput:
      return "InvalidInput";
    case PdfErrorCode::InvalidState:
      return "InvalidState";
    case PdfErrorCode::InvalidPageSize:
      return "InvalidPageSize";
    case PdfErrorCode::InvalidMargins:
      return "InvalidMargins";
    case PdfErrorCode::InvalidText:
      return "InvalidText";
    case PdfErrorCode::InvalidImage:
      return "InvalidImage";
    case PdfErrorCode::InvalidTable:
      return "InvalidTable";

    case PdfErrorCode::UnsupportedImageFormat:
      return "UnsupportedImageFormat";
    case PdfErrorCode::FileOpenFailed:
      return "FileOpenFailed";
    case PdfErrorCode::FileReadFailed:
      return "FileReadFailed";
    case PdfErrorCode::FileWriteFailed:
      return "FileWriteFailed";

    case PdfErrorCode::SerializationFailed:
      return "SerializationFailed";
    case PdfErrorCode::WriterError:
      return "WriterError";

    case PdfErrorCode::Unknown:
      return "Unknown";
    }

    return "Unknown";
  }

  PdfError make_pdf_ok()
  {
    return PdfError{};
  }

  PdfError make_pdf_error(
      PdfErrorCode code,
      std::string message)
  {
    return PdfError{code, std::move(message)};
  }
} // namespace rixlib::pdf
