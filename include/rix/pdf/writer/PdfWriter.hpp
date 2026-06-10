/**
 *
 *  @file PdfWriter.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_PDFWRITER_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_PDFWRITER_HPP_INCLUDED

#include <rix/pdf/core/Result.hpp>
#include <rix/pdf/document/Document.hpp>

#include <string>
#include <string_view>

namespace rixlib::pdf::writer
{
  /**
   * @brief PDF document serializer.
   *
   * PdfWriter converts a Document model into PDF bytes and can save those
   * bytes to disk. It owns no document data and performs serialization as a
   * controlled operation returning PdfResult or PdfStatus.
   */
  class PdfWriter
  {
  public:
    /**
     * @brief Construct a PDF writer.
     */
    PdfWriter() = default;

    /**
     * @brief Serialize a document into PDF bytes.
     *
     * If the document has no pages, a blank default page is generated so the
     * output remains a valid PDF document.
     *
     * @param document Document to serialize.
     * @return PDF byte string on success.
     */
    [[nodiscard]] PdfResult<std::string> write(
        const Document &document) const;

    /**
     * @brief Save a document to a PDF file.
     *
     * @param document Document to serialize.
     * @param path Output file path.
     * @return PdfStatus indicating success or failure.
     */
    [[nodiscard]] PdfStatus save(
        const Document &document,
        std::string_view path) const;
  };
} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_PDFWRITER_HPP_INCLUDED
