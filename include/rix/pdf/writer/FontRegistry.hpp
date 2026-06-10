/**
 *
 *  @file FontRegistry.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTREGISTRY_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTREGISTRY_HPP_INCLUDED

#include <rix/pdf/core/Font.hpp>

#include <cstddef>
#include <map>
#include <vector>

namespace rixlib::pdf::writer
{
  /**
   * @brief Registry for fonts used by a PDF document.
   *
   * FontRegistry keeps one object id per font and provides stable resource
   * names for page resource dictionaries.
   */
  class FontRegistry
  {
  public:
    /**
     * @brief Construct an empty font registry.
     */
    FontRegistry() = default;

    /**
     * @brief Register a font if it is not already registered.
     *
     * @param font Font to register.
     */
    void add(Font font);

    /**
     * @brief Register all fonts from a range.
     *
     * @param fonts Fonts to register.
     */
    void add_all(const std::vector<Font> &fonts);

    /**
     * @brief Return true when the font is already registered.
     *
     * @param font Font to check.
     * @return true if the font is registered.
     */
    [[nodiscard]] bool contains(Font font) const noexcept;

    /**
     * @brief Return the number of registered fonts.
     *
     * @return Font count.
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief Return true when no fonts are registered.
     *
     * @return true if the registry is empty.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Assign PDF object ids to registered fonts.
     *
     * Object ids are assigned in the order fonts were registered.
     *
     * @param first_object_id First available PDF object id.
     * @return Next available PDF object id after assignment.
     */
    int assign_object_ids(int first_object_id);

    /**
     * @brief Return the PDF object id for a font.
     *
     * @param font Font to query.
     * @return Object id, or 0 if not assigned.
     */
    [[nodiscard]] int object_id(Font font) const noexcept;

    /**
     * @brief Return the page-local font resource index.
     *
     * Page-local font indexes are one-based and depend on the page font list.
     *
     * @param page_fonts Fonts used by a page.
     * @param font Font to query.
     * @return One-based index, or 1 as safe fallback.
     */
    [[nodiscard]] static int page_font_index(
        const std::vector<Font> &page_fonts,
        Font font) noexcept;

    /**
     * @brief Return all registered fonts in stable order.
     *
     * @return Registered fonts.
     */
    [[nodiscard]] const std::vector<Font> &fonts() const noexcept;

  private:
    std::vector<Font> fonts_;
    std::map<Font, int> object_ids_;
  };
} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_FONTREGISTRY_HPP_INCLUDED
