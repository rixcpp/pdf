/**
 *
 *  @file XrefTable.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_XREFTABLE_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_XREFTABLE_HPP_INCLUDED

#include <cstddef>
#include <string>
#include <vector>

namespace rixlib::pdf::writer
{
  /**
   * @brief PDF cross-reference table writer.
   *
   * XrefTable writes the xref section and trailer from the object offsets
   * collected while writing PDF objects.
   */
  class XrefTable
  {
  public:
    /**
     * @brief Construct a cross-reference table writer.
     *
     * @param offsets Object offsets indexed by object id.
     */
    explicit XrefTable(const std::vector<std::size_t> &offsets);

    /**
     * @brief Write the xref table, trailer, startxref, and EOF marker.
     *
     * @param output Output PDF buffer.
     * @param root_object_id Catalog object id.
     * @param info_object_id Info dictionary object id.
     */
    void write(
        std::string &output,
        int root_object_id,
        int info_object_id) const;

  private:
    const std::vector<std::size_t> &offsets_;
  };
} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_XREFTABLE_HPP_INCLUDED
