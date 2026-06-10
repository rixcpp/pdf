/**
 *
 *  @file Error.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ERROR_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ERROR_HPP_INCLUDED

#include <string>
#include <string_view>

namespace rixlib::pdf
{
  /**
   * @brief Stable PDF error codes.
   *
   * These codes are part of the public rix/pdf API. They describe
   * PDF-domain failures without exposing low-level writer details.
   */
  enum class PdfErrorCode
  {
    None,

    InvalidInput,
    InvalidState,
    InvalidPageSize,
    InvalidMargins,
    InvalidText,
    InvalidImage,
    InvalidTable,

    UnsupportedImageFormat,
    FileOpenFailed,
    FileReadFailed,
    FileWriteFailed,

    SerializationFailed,
    WriterError,

    Unknown
  };

  /**
   * @brief PDF error value.
   *
   * PdfError stores a stable error code and a human-readable message.
   * The code is intended for programmatic decisions. The message is intended
   * for logs, diagnostics, and developer feedback.
   */
  class PdfError
  {
  public:
    /**
     * @brief Construct a success error value.
     */
    PdfError() = default;

    /**
     * @brief Construct a PDF error.
     *
     * @param code Stable PDF error code.
     * @param message Human-readable error message.
     */
    PdfError(PdfErrorCode code, std::string message);

    /**
     * @brief Return true when this value represents success.
     *
     * @return true if code is PdfErrorCode::None.
     */
    [[nodiscard]] bool ok() const noexcept;

    /**
     * @brief Return true when this value represents failure.
     *
     * @return true if code is not PdfErrorCode::None.
     */
    [[nodiscard]] bool has_error() const noexcept;

    /**
     * @brief Return the stable error code.
     *
     * @return PDF error code.
     */
    [[nodiscard]] PdfErrorCode code() const noexcept;

    /**
     * @brief Return the human-readable error message.
     *
     * @return Error message.
     */
    [[nodiscard]] const std::string &message() const noexcept;

    /**
     * @brief Return true when the error code equals the given code.
     *
     * @param code Error code to compare.
     * @return true if the stored code matches.
     */
    [[nodiscard]] bool is(PdfErrorCode code) const noexcept;

  private:
    PdfErrorCode code_ = PdfErrorCode::None;
    std::string message_;
  };

  /**
   * @brief Convert a PDF error code to a stable string.
   *
   * @param code Error code.
   * @return Stable string representation.
   */
  [[nodiscard]] std::string_view to_string(PdfErrorCode code) noexcept;

  /**
   * @brief Create a success PDF error value.
   *
   * @return PdfError with PdfErrorCode::None.
   */
  [[nodiscard]] PdfError make_pdf_ok();

  /**
   * @brief Create a PDF error.
   *
   * @param code Stable PDF error code.
   * @param message Human-readable error message.
   * @return PdfError value.
   */
  [[nodiscard]] PdfError make_pdf_error(
      PdfErrorCode code,
      std::string message);

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_ERROR_HPP_INCLUDED
