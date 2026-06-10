/**
 *
 *  @file Document.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_DOCUMENT_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_DOCUMENT_HPP_INCLUDED

#include <rix/pdf/core/Margins.hpp>
#include <rix/pdf/core/PageSize.hpp>
#include <rix/pdf/document/Metadata.hpp>
#include <rix/pdf/document/Page.hpp>

#include <cstddef>
#include <vector>

namespace rixlib::pdf
{
  /**
   * @brief PDF document model.
   *
   * Document owns pages and metadata. It does not directly serialize itself.
   * Serialization is handled by the writer layer so the document model stays
   * simple and reusable.
   */
  class Document
  {
  public:
    /**
     * @brief Construct a document with A4 pages and default margins.
     */
    Document();

    /**
     * @brief Construct a document with default page settings.
     *
     * @param default_size Default page size.
     * @param default_margins Default page margins.
     */
    explicit Document(
        PageSize default_size,
        Margins default_margins = Margins{});

    /**
     * @brief Return the default page size.
     *
     * @return Default page size.
     */
    [[nodiscard]] const PageSize &default_page_size() const noexcept;

    /**
     * @brief Set the default page size.
     *
     * @param value Default page size.
     * @return This document.
     */
    Document &set_default_page_size(PageSize value) noexcept;

    /**
     * @brief Return the default page margins.
     *
     * @return Default page margins.
     */
    [[nodiscard]] const Margins &default_margins() const noexcept;

    /**
     * @brief Set the default page margins.
     *
     * @param value Default page margins.
     * @return This document.
     */
    Document &set_default_margins(Margins value) noexcept;

    /**
     * @brief Add a page using the document defaults.
     *
     * @return Created page.
     */
    Page &add_page();

    /**
     * @brief Add a page with a custom size.
     *
     * @param size Page size.
     * @return Created page.
     */
    Page &add_page(PageSize size);

    /**
     * @brief Add a page with custom size and margins.
     *
     * @param size Page size.
     * @param margins Page margins.
     * @return Created page.
     */
    Page &add_page(PageSize size, Margins margins);

    /**
     * @brief Return the page at the given index.
     *
     * @param index Page index.
     * @return Page.
     */
    [[nodiscard]] Page &page(std::size_t index);

    /**
     * @brief Return the page at the given index.
     *
     * @param index Page index.
     * @return Page.
     */
    [[nodiscard]] const Page &page(std::size_t index) const;

    /**
     * @brief Return all pages.
     *
     * @return Pages.
     */
    [[nodiscard]] const std::vector<Page> &pages() const noexcept;

    /**
     * @brief Return all pages.
     *
     * @return Pages.
     */
    [[nodiscard]] std::vector<Page> &pages() noexcept;

    /**
     * @brief Return the number of pages.
     *
     * @return Page count.
     */
    [[nodiscard]] std::size_t page_count() const noexcept;

    /**
     * @brief Return true when the document has no pages.
     *
     * @return true if no pages are stored.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Remove all pages.
     */
    void clear_pages();

    /**
     * @brief Return document metadata.
     *
     * @return Metadata.
     */
    [[nodiscard]] const Metadata &metadata() const noexcept;

    /**
     * @brief Return document metadata.
     *
     * @return Metadata.
     */
    [[nodiscard]] Metadata &metadata() noexcept;

    /**
     * @brief Set document metadata.
     *
     * @param value Metadata.
     * @return This document.
     */
    Document &set_metadata(Metadata value) noexcept;

    /**
     * @brief Set the document title.
     *
     * @param value Title.
     * @return This document.
     */
    Document &set_title(std::string value);

    /**
     * @brief Set the document author.
     *
     * @param value Author.
     * @return This document.
     */
    Document &set_author(std::string value);

    /**
     * @brief Set the document subject.
     *
     * @param value Subject.
     * @return This document.
     */
    Document &set_subject(std::string value);

    /**
     * @brief Set the document creator.
     *
     * @param value Creator.
     * @return This document.
     */
    Document &set_creator(std::string value);

    /**
     * @brief Set the document keywords.
     *
     * @param value Keywords.
     * @return This document.
     */
    Document &set_keywords(std::string value);

  private:
    PageSize default_size_;
    Margins default_margins_;
    std::vector<Page> pages_;
    Metadata metadata_;
  };
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_DOCUMENT_HPP_INCLUDED
