/**
 *
 *  @file Metadata.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_METADATA_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_METADATA_HPP_INCLUDED

#include <string>
#include <string_view>

namespace rixlib::pdf
{
  /**
   * @brief PDF document metadata.
   *
   * Metadata stores optional information written to the PDF info dictionary,
   * such as title, author, subject, creator, and keywords.
   */
  class Metadata
  {
  public:
    /**
     * @brief Construct empty metadata.
     *
     * The creator field defaults to "rix/pdf".
     */
    Metadata();

    /**
     * @brief Return the document title.
     *
     * @return Document title.
     */
    [[nodiscard]] const std::string &title() const noexcept;

    /**
     * @brief Set the document title.
     *
     * @param value Document title.
     */
    void set_title(std::string value);

    /**
     * @brief Return the document author.
     *
     * @return Document author.
     */
    [[nodiscard]] const std::string &author() const noexcept;

    /**
     * @brief Set the document author.
     *
     * @param value Document author.
     */
    void set_author(std::string value);

    /**
     * @brief Return the document subject.
     *
     * @return Document subject.
     */
    [[nodiscard]] const std::string &subject() const noexcept;

    /**
     * @brief Set the document subject.
     *
     * @param value Document subject.
     */
    void set_subject(std::string value);

    /**
     * @brief Return the document creator.
     *
     * @return Document creator.
     */
    [[nodiscard]] const std::string &creator() const noexcept;

    /**
     * @brief Set the document creator.
     *
     * Empty creator values are normalized back to "rix/pdf".
     *
     * @param value Document creator.
     */
    void set_creator(std::string value);

    /**
     * @brief Return the document keywords.
     *
     * @return Document keywords.
     */
    [[nodiscard]] const std::string &keywords() const noexcept;

    /**
     * @brief Set the document keywords.
     *
     * @param value Document keywords.
     */
    void set_keywords(std::string value);

    /**
     * @brief Clear all user-provided metadata.
     *
     * The creator field is reset to "rix/pdf".
     */
    void clear();

    /**
     * @brief Return true when no user-provided metadata is set.
     *
     * The default creator value does not make the metadata non-empty.
     *
     * @return true if title, author, subject, and keywords are empty.
     */
    [[nodiscard]] bool empty() const noexcept;

  private:
    std::string title_;
    std::string author_;
    std::string subject_;
    std::string creator_;
    std::string keywords_;
  };
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_DOCUMENT_METADATA_HPP_INCLUDED
