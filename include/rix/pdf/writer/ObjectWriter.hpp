/**
 *
 *  @file ObjectWriter.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_OBJECTWRITER_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_OBJECTWRITER_HPP_INCLUDED

#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/document/Image.hpp>
#include <rix/pdf/document/Metadata.hpp>
#include <rix/pdf/document/Page.hpp>
#include <rix/pdf/writer/FontRegistry.hpp>
#include <rix/pdf/writer/ImageRegistry.hpp>

#include <cstddef>
#include <string>

namespace rixlib::pdf::writer
{
  /**
   * @brief Low-level PDF object writer.
   *
   * ObjectWriter appends valid PDF objects to an output string and records
   * object offsets for the cross-reference table.
   */
  class ObjectWriter
  {
  public:
    /**
     * @brief Construct an object writer.
     *
     * @param output Output PDF buffer.
     * @param offsets Object offset table.
     */
    ObjectWriter(
        std::string &output,
        std::vector<std::size_t> &offsets);

    /**
     * @brief Write the PDF header.
     */
    void write_header();

    /**
     * @brief Write the catalog object.
     *
     * @param object_id Catalog object id.
     * @param pages_object_id Pages tree object id.
     */
    void write_catalog(
        int object_id,
        int pages_object_id);

    /**
     * @brief Write the pages tree object.
     *
     * @param object_id Pages object id.
     * @param first_page_object_id First page object id.
     * @param page_count Number of pages.
     */
    void write_pages(
        int object_id,
        int first_page_object_id,
        int page_count);

    /**
     * @brief Write a page object.
     *
     * @param object_id Page object id.
     * @param pages_object_id Parent pages object id.
     * @param content_object_id Page content stream object id.
     * @param page Page model.
     * @param fonts Font registry.
     * @param images Image registry.
     */
    void write_page(
        int object_id,
        int pages_object_id,
        int content_object_id,
        const Page &page,
        const FontRegistry &fonts,
        const ImageRegistry &images);

    /**
     * @brief Write a page content stream object.
     *
     * @param object_id Content stream object id.
     * @param page Page model.
     */
    void write_content_stream(
        int object_id,
        const Page &page);

    /**
     * @brief Write a standard Type 1 font object.
     *
     * @param object_id Font object id.
     * @param font Standard PDF font.
     */
    void write_font(
        int object_id,
        Font font);

    /**
     * @brief Write a JPEG image XObject.
     *
     * @param object_id Image object id.
     * @param image Image data.
     */
    void write_image(
        int object_id,
        const Image &image);

    /**
     * @brief Write the PDF info dictionary.
     *
     * @param object_id Info object id.
     * @param metadata Document metadata.
     */
    void write_info(
        int object_id,
        const Metadata &metadata);

  private:
    void mark_offset(int object_id);

    std::string &output_;
    std::vector<std::size_t> &offsets_;
  };
} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_OBJECTWRITER_HPP_INCLUDED
