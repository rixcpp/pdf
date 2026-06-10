/**
 *
 *  @file PdfErrorTests.cpp
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
#include <rix/pdf/core/Result.hpp>

#include <cassert>
#include <string>

int main()
{
  using namespace rixlib::pdf;

  PdfError ok;

  assert(ok.ok());
  assert(!ok.has_error());
  assert(ok.code() == PdfErrorCode::None);
  assert(ok.message().empty());
  assert(ok.is(PdfErrorCode::None));

  auto error = make_pdf_error(
      PdfErrorCode::InvalidImage,
      "Invalid image.");

  assert(!error.ok());
  assert(error.has_error());
  assert(error.code() == PdfErrorCode::InvalidImage);
  assert(error.message() == "Invalid image.");
  assert(error.is(PdfErrorCode::InvalidImage));
  assert(!error.is(PdfErrorCode::InvalidInput));

  assert(to_string(PdfErrorCode::None) == "None");
  assert(to_string(PdfErrorCode::InvalidInput) == "InvalidInput");
  assert(to_string(PdfErrorCode::InvalidState) == "InvalidState");
  assert(to_string(PdfErrorCode::InvalidPageSize) == "InvalidPageSize");
  assert(to_string(PdfErrorCode::InvalidMargins) == "InvalidMargins");
  assert(to_string(PdfErrorCode::InvalidText) == "InvalidText");
  assert(to_string(PdfErrorCode::InvalidImage) == "InvalidImage");
  assert(to_string(PdfErrorCode::InvalidTable) == "InvalidTable");
  assert(to_string(PdfErrorCode::UnsupportedImageFormat) == "UnsupportedImageFormat");
  assert(to_string(PdfErrorCode::FileOpenFailed) == "FileOpenFailed");
  assert(to_string(PdfErrorCode::FileReadFailed) == "FileReadFailed");
  assert(to_string(PdfErrorCode::FileWriteFailed) == "FileWriteFailed");
  assert(to_string(PdfErrorCode::SerializationFailed) == "SerializationFailed");
  assert(to_string(PdfErrorCode::WriterError) == "WriterError");
  assert(to_string(PdfErrorCode::Unknown) == "Unknown");

  auto result = PdfResult<std::string>::success("hello");

  assert(result.ok());
  assert(!result.failed());
  assert(result.value() == "hello");
  assert(result.error().ok());

  auto failed = PdfResult<std::string>::failure(
      make_pdf_error(
          PdfErrorCode::WriterError,
          "writer failed"));

  assert(!failed.ok());
  assert(failed.failed());
  assert(failed.error().is(PdfErrorCode::WriterError));

  auto status = PdfStatus::success();

  assert(status.ok());
  assert(!status.failed());
  assert(status.error().ok());

  auto failed_status = PdfStatus::failure(
      make_pdf_error(
          PdfErrorCode::FileWriteFailed,
          "write failed"));

  assert(!failed_status.ok());
  assert(failed_status.failed());
  assert(failed_status.error().is(PdfErrorCode::FileWriteFailed));

  return 0;
}
