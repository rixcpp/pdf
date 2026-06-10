/**
 *
 *  @file PdfWriter.cpp
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

#include <rix/pdf/writer/PdfWriter.hpp>

#include <rix/pdf/writer/FontRegistry.hpp>
#include <rix/pdf/writer/ImageRegistry.hpp>
#include <rix/pdf/writer/ObjectWriter.hpp>
#include <rix/pdf/writer/XrefTable.hpp>

#include <fstream>
#include <utility>
#include <vector>

namespace rixlib::pdf::writer
{
  namespace
  {
    [[nodiscard]] PdfError invalid_input_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::InvalidInput,
          std::move(message));
    }

    [[nodiscard]] PdfError file_open_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::FileOpenFailed,
          std::move(message));
    }

    [[nodiscard]] PdfError file_write_error(std::string message)
    {
      return make_pdf_error(
          PdfErrorCode::FileWriteFailed,
          std::move(message));
    }

    [[nodiscard]] FontRegistry collect_fonts(const Document &document)
    {
      FontRegistry registry;

      for (const auto &page : document.pages())
      {
        registry.add_all(page.fonts());
      }

      return registry;
    }

    [[nodiscard]] ImageRegistry collect_images(const Document &document)
    {
      ImageRegistry registry;

      for (const auto &page : document.pages())
      {
        registry.add_all(page.images());
      }

      return registry;
    }
  } // namespace

  PdfResult<std::string> PdfWriter::write(
      const Document &document) const
  {
    Document output_document = document;

    if (output_document.empty())
    {
      output_document.add_page();
    }

    FontRegistry fonts = collect_fonts(output_document);
    ImageRegistry images = collect_images(output_document);

    const int page_count = static_cast<int>(output_document.page_count());

    constexpr int catalog_object_id = 1;
    constexpr int pages_object_id = 2;

    const int page_object_start = 3;
    const int content_object_start = page_object_start + page_count;

    int next_object_id = content_object_start + page_count;

    next_object_id = fonts.assign_object_ids(next_object_id);
    next_object_id = images.assign_object_ids(next_object_id);

    const int info_object_id = next_object_id;
    ++next_object_id;

    const int object_count = next_object_id;

    std::string output;
    output.reserve(65536);

    std::vector<std::size_t> offsets(
        static_cast<std::size_t>(object_count),
        0);

    ObjectWriter objects{output, offsets};

    objects.write_header();

    objects.write_catalog(
        catalog_object_id,
        pages_object_id);

    objects.write_pages(
        pages_object_id,
        page_object_start,
        page_count);

    for (int index = 0; index < page_count; ++index)
    {
      const auto &page = output_document.pages()[static_cast<std::size_t>(index)];

      objects.write_page(
          page_object_start + index,
          pages_object_id,
          content_object_start + index,
          page,
          fonts,
          images);
    }

    for (int index = 0; index < page_count; ++index)
    {
      const auto &page = output_document.pages()[static_cast<std::size_t>(index)];

      objects.write_content_stream(
          content_object_start + index,
          page);
    }

    for (const auto font : fonts.fonts())
    {
      const int object_id = fonts.object_id(font);

      if (object_id <= 0)
      {
        return PdfResult<std::string>::failure(
            invalid_input_error("Font object id was not assigned."));
      }

      objects.write_font(object_id, font);
    }

    for (const auto *image : images.images())
    {
      const int object_id = images.object_id(image);

      if (image == nullptr || object_id <= 0)
      {
        return PdfResult<std::string>::failure(
            invalid_input_error("Image object id was not assigned."));
      }

      objects.write_image(object_id, *image);
    }

    objects.write_info(
        info_object_id,
        output_document.metadata());

    XrefTable xref{offsets};

    xref.write(
        output,
        catalog_object_id,
        info_object_id);

    return PdfResult<std::string>::success(std::move(output));
  }

  PdfStatus PdfWriter::save(
      const Document &document,
      std::string_view path) const
  {
    if (path.empty())
    {
      return PdfStatus::failure(
          invalid_input_error("Output PDF path cannot be empty."));
    }

    auto data = write(document);

    if (data.failed())
    {
      return PdfStatus::failure(data.error());
    }

    std::ofstream file{
        std::string(path),
        std::ios::binary};

    if (!file)
    {
      return PdfStatus::failure(
          file_open_error("Cannot open PDF file for writing."));
    }

    const auto &bytes = data.value();

    file.write(
        bytes.data(),
        static_cast<std::streamsize>(bytes.size()));

    if (!file)
    {
      return PdfStatus::failure(
          file_write_error("Failed to write PDF file."));
    }

    return PdfStatus::success();
  }
} // namespace rixlib::pdf::writer
