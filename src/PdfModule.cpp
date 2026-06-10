/**
 *
 *  @file PdfModule.cpp
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

#include <rix/pdf/PdfModule.hpp>

#include <utility>

namespace rixlib::pdf
{
  PdfError PdfErrorModule::none() const
  {
    return make_pdf_ok();
  }

  PdfError PdfErrorModule::make(
      PdfErrorCode code,
      std::string message) const
  {
    return make_pdf_error(
        code,
        std::move(message));
  }

  std::string_view PdfErrorModule::to_string(
      PdfErrorCode code) const noexcept
  {
    return rixlib::pdf::to_string(code);
  }

  std::string_view PdfErrorModule::to_string(
      const PdfError &error) const noexcept
  {
    return rixlib::pdf::to_string(error.code());
  }

  bool PdfErrorModule::ok(const PdfError &error) const noexcept
  {
    return error.ok();
  }

  bool PdfErrorModule::failed(const PdfError &error) const noexcept
  {
    return error.has_error();
  }

  bool PdfErrorModule::is(
      const PdfError &error,
      PdfErrorCode code) const noexcept
  {
    return error.is(code);
  }

  PdfResult<Image> PdfImageModule::load_jpeg(
      std::string_view path) const
  {
    return Image::load_jpeg(path);
  }

  PdfResult<Image> PdfImageModule::from_jpeg_bytes(
      std::vector<std::uint8_t> bytes) const
  {
    return Image::from_jpeg_bytes(std::move(bytes));
  }

  PdfResult<std::string> PdfWriterModule::write(
      const Document &document) const
  {
    writer::PdfWriter pdf_writer;
    return pdf_writer.write(document);
  }

  PdfStatus PdfWriterModule::save(
      const Document &document,
      std::string_view path) const
  {
    writer::PdfWriter pdf_writer;
    return pdf_writer.save(document, path);
  }

  writer::PdfWriter PdfWriterModule::create() const
  {
    return writer::PdfWriter{};
  }

  Document PdfModule::document() const
  {
    return Document{};
  }

  Document PdfModule::document(
      PageSize page_size,
      Margins margins) const
  {
    return Document{
        page_size,
        margins};
  }

  PdfResult<std::string> PdfModule::write(
      const Document &document) const
  {
    return writer.write(document);
  }

  PdfStatus PdfModule::save(
      const Document &document,
      std::string_view path) const
  {
    return writer.save(document, path);
  }

  PdfStatus PdfModule::make_text(
      std::string_view path,
      std::string_view content,
      std::string_view title) const
  {
    auto doc = document();

    if (!title.empty())
    {
      doc.set_title(std::string(title));
    }

    auto &page = doc.add_page();

    auto y = page.y_top();

    if (!title.empty())
    {
      y = page.heading(
          page.x_left(),
          y,
          title,
          1);

      y -= 10.0F;
    }

    page.paragraph(
        page.x_left(),
        y,
        page.content_width(),
        content);

    return save(doc, path);
  }

  std::string PdfModule::version() const
  {
    return rixlib::pdf::version();
  }

  int PdfModule::version_major() const noexcept
  {
    return rixlib::pdf::version_major();
  }

  int PdfModule::version_minor() const noexcept
  {
    return rixlib::pdf::version_minor();
  }

  int PdfModule::version_patch() const noexcept
  {
    return rixlib::pdf::version_patch();
  }

  int PdfModule::version_number() const noexcept
  {
    return rixlib::pdf::version_number();
  }
} // namespace rixlib::pdf
