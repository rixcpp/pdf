/**
 *
 *  @file pdf.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_HPP_INCLUDED

#include <rix/pdf/PdfModule.hpp>
#include <rix/pdf/Version.hpp>

#include <rix/pdf/core/Align.hpp>
#include <rix/pdf/core/Color.hpp>
#include <rix/pdf/core/Error.hpp>
#include <rix/pdf/core/Font.hpp>
#include <rix/pdf/core/LineStyle.hpp>
#include <rix/pdf/core/Margins.hpp>
#include <rix/pdf/core/PageSize.hpp>
#include <rix/pdf/core/Result.hpp>
#include <rix/pdf/core/Units.hpp>

#include <rix/pdf/document/BorderStyle.hpp>
#include <rix/pdf/document/Document.hpp>
#include <rix/pdf/document/Image.hpp>
#include <rix/pdf/document/Metadata.hpp>
#include <rix/pdf/document/Page.hpp>
#include <rix/pdf/document/Table.hpp>
#include <rix/pdf/document/TextStyle.hpp>

#include <rix/pdf/writer/Escape.hpp>
#include <rix/pdf/writer/FloatFormat.hpp>
#include <rix/pdf/writer/FontMetrics.hpp>
#include <rix/pdf/writer/FontRegistry.hpp>
#include <rix/pdf/writer/ImageRegistry.hpp>
#include <rix/pdf/writer/ObjectWriter.hpp>
#include <rix/pdf/writer/PdfWriter.hpp>
#include <rix/pdf/writer/XrefTable.hpp>

namespace rixlib::pdf
{
  /**
   * @brief Return the public PDF module facade.
   *
   * This helper is useful when using rix/pdf independently from the unified
   * rix facade package.
   *
   * @return PDF module facade.
   */
  [[nodiscard]] inline constexpr PdfModule module() noexcept
  {
    return PdfModule{};
  }
} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_HPP_INCLUDED
