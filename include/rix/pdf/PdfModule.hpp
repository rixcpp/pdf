/**
 *
 *  @file PdfModule.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_PDFMODULE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_PDFMODULE_HPP_INCLUDED

#include <rix/pdf/Version.hpp>
#include <rix/pdf/core/Error.hpp>
#include <rix/pdf/core/Result.hpp>
#include <rix/pdf/document/Document.hpp>
#include <rix/pdf/document/Image.hpp>
#include <rix/pdf/writer/PdfWriter.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace rixlib::pdf
{
  /**
   * @brief PDF error helpers exposed through rix.pdf.error.
   */
  class PdfErrorModule
  {
  public:
    /**
     * @brief Return a success PDF error value.
     *
     * @return PdfError with PdfErrorCode::None.
     */
    [[nodiscard]] PdfError none() const;

    /**
     * @brief Create a PDF error value.
     *
     * @param code PDF error code.
     * @param message Human-readable error message.
     * @return PDF error value.
     */
    [[nodiscard]] PdfError make(
        PdfErrorCode code,
        std::string message) const;

    /**
     * @brief Convert a PDF error code to a stable string.
     *
     * @param code PDF error code.
     * @return Stable string representation.
     */
    [[nodiscard]] std::string_view to_string(
        PdfErrorCode code) const noexcept;

    /**
     * @brief Convert a PDF error value to a stable string.
     *
     * @param error PDF error value.
     * @return Stable string representation.
     */
    [[nodiscard]] std::string_view to_string(
        const PdfError &error) const noexcept;

    /**
     * @brief Return true when the error is success.
     *
     * @param error PDF error value.
     * @return true if the error code is None.
     */
    [[nodiscard]] bool ok(const PdfError &error) const noexcept;

    /**
     * @brief Return true when the error is failure.
     *
     * @param error PDF error value.
     * @return true if the error code is not None.
     */
    [[nodiscard]] bool failed(const PdfError &error) const noexcept;

    /**
     * @brief Return true when the error has the given code.
     *
     * @param error PDF error value.
     * @param code Expected error code.
     * @return true if the code matches.
     */
    [[nodiscard]] bool is(
        const PdfError &error,
        PdfErrorCode code) const noexcept;
  };

  /**
   * @brief PDF image helpers exposed through rix.pdf.image.
   */
  class PdfImageModule
  {
  public:
    /**
     * @brief Load a JPEG image from a file.
     *
     * @param path Image file path.
     * @return Image on success.
     */
    [[nodiscard]] PdfResult<Image> load_jpeg(
        std::string_view path) const;

    /**
     * @brief Create a JPEG image from encoded bytes.
     *
     * @param bytes JPEG bytes.
     * @return Image on success.
     */
    [[nodiscard]] PdfResult<Image> from_jpeg_bytes(
        std::vector<std::uint8_t> bytes) const;
  };

  /**
   * @brief PDF writer helpers exposed through rix.pdf.writer.
   */
  class PdfWriterModule
  {
  public:
    /**
     * @brief Serialize a document into PDF bytes.
     *
     * @param document Document to serialize.
     * @return PDF byte string on success.
     */
    [[nodiscard]] PdfResult<std::string> write(
        const Document &document) const;

    /**
     * @brief Save a document to a PDF file.
     *
     * @param document Document to save.
     * @param path Output file path.
     * @return Status.
     */
    [[nodiscard]] PdfStatus save(
        const Document &document,
        std::string_view path) const;

    /**
     * @brief Return a standalone PDF writer.
     *
     * @return PDF writer.
     */
    [[nodiscard]] writer::PdfWriter create() const;
  };

  /**
   * @brief High-level PDF facade exposed through rix.pdf.
   *
   * PdfModule is the public entry point used by the global Rix facade.
   * It keeps common PDF workflows simple while keeping writer internals
   * hidden behind explicit Result and Status values.
   */
  class PdfModule
  {
  public:
    /**
     * @brief Error helpers.
     */
    PdfErrorModule error{};

    /**
     * @brief Image helpers.
     */
    PdfImageModule image{};

    /**
     * @brief Writer helpers.
     */
    PdfWriterModule writer{};

    /**
     * @brief Create an empty PDF document.
     *
     * @return Document.
     */
    [[nodiscard]] Document document() const;

    /**
     * @brief Create a PDF document with default page settings.
     *
     * @param page_size Default page size.
     * @param margins Default page margins.
     * @return Document.
     */
    [[nodiscard]] Document document(
        PageSize page_size,
        Margins margins = Margins{}) const;

    /**
     * @brief Serialize a document into PDF bytes.
     *
     * @param document Document to serialize.
     * @return PDF byte string on success.
     */
    [[nodiscard]] PdfResult<std::string> write(
        const Document &document) const;

    /**
     * @brief Save a document to a PDF file.
     *
     * @param document Document to save.
     * @param path Output file path.
     * @return Status.
     */
    [[nodiscard]] PdfStatus save(
        const Document &document,
        std::string_view path) const;

    /**
     * @brief Generate and save a simple text PDF.
     *
     * @param path Output file path.
     * @param content Text content.
     * @param title Optional document title.
     * @return Status.
     */
    [[nodiscard]] PdfStatus make_text(
        std::string_view path,
        std::string_view content,
        std::string_view title = "") const;

    /**
     * @brief Return the package version string.
     *
     * @return Version string.
     */
    [[nodiscard]] std::string version() const;

    /**
     * @brief Return the package major version.
     *
     * @return Major version.
     */
    [[nodiscard]] int version_major() const noexcept;

    /**
     * @brief Return the package minor version.
     *
     * @return Minor version.
     */
    [[nodiscard]] int version_minor() const noexcept;

    /**
     * @brief Return the package patch version.
     *
     * @return Patch version.
     */
    [[nodiscard]] int version_patch() const noexcept;

    /**
     * @brief Return the encoded package version number.
     *
     * @return Encoded version.
     */
    [[nodiscard]] int version_number() const noexcept;
  };
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_PDFMODULE_HPP_INCLUDED
