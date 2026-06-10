/**
 *
 *  @file ObjectWriter.cpp
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

#include <rix/pdf/writer/ObjectWriter.hpp>
#include <rix/pdf/writer/Escape.hpp>
#include <rix/pdf/writer/FloatFormat.hpp>

namespace rixlib::pdf::writer
{
  ObjectWriter::ObjectWriter(
      std::string &output,
      std::vector<std::size_t> &offsets)
      : output_(output),
        offsets_(offsets)
  {
  }

  void ObjectWriter::write_header()
  {
    output_ += "%PDF-1.4\n";
    output_ += "%\xE2\xE3\xCF\xD3\n";
  }

  void ObjectWriter::write_catalog(
      int object_id,
      int pages_object_id)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Type /Catalog /Pages ";
    output_ += std::to_string(pages_object_id);
    output_ += " 0 R >>\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_pages(
      int object_id,
      int first_page_object_id,
      int page_count)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Type /Pages /Kids [";

    for (int index = 0; index < page_count; ++index)
    {
      output_ += std::to_string(first_page_object_id + index);
      output_ += " 0 R ";
    }

    output_ += "] /Count ";
    output_ += std::to_string(page_count);
    output_ += " >>\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_page(
      int object_id,
      int pages_object_id,
      int content_object_id,
      const Page &page,
      const FontRegistry &fonts,
      const ImageRegistry &images)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Type /Page /Parent ";
    output_ += std::to_string(pages_object_id);
    output_ += " 0 R\n";

    output_ += "   /MediaBox [0 0 ";
    output_ += format_point(page.width());
    output_ += " ";
    output_ += format_point(page.height());
    output_ += "]\n";

    output_ += "   /Contents ";
    output_ += std::to_string(content_object_id);
    output_ += " 0 R\n";

    output_ += "   /Resources <<\n";

    if (!page.fonts().empty())
    {
      output_ += "     /Font <<\n";

      for (const auto font : page.fonts())
      {
        output_ += "       /F";
        output_ += std::to_string(FontRegistry::page_font_index(page.fonts(), font));
        output_ += " ";
        output_ += std::to_string(fonts.object_id(font));
        output_ += " 0 R\n";
      }

      output_ += "     >>\n";
    }

    if (!page.images().empty())
    {
      output_ += "     /XObject <<\n";

      for (const auto *image : page.images())
      {
        output_ += "       /Im";
        output_ += std::to_string(ImageRegistry::page_image_index(page.images(), image));
        output_ += " ";
        output_ += std::to_string(images.object_id(image));
        output_ += " 0 R\n";
      }

      output_ += "     >>\n";
    }

    output_ += "   >>\n";
    output_ += ">>\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_content_stream(
      int object_id,
      const Page &page)
  {
    mark_offset(object_id);

    const auto &content = page.content_stream();

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Length ";
    output_ += std::to_string(content.size());
    output_ += " >>\n";
    output_ += "stream\n";
    output_ += content;
    output_ += "\nendstream\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_font(
      int object_id,
      Font font)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Type /Font /Subtype /Type1\n";
    output_ += "   /BaseFont ";
    output_ += name(base_font_name(font));
    output_ += "\n";
    output_ += "   /Encoding /WinAnsiEncoding\n";
    output_ += ">>\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_image(
      int object_id,
      const Image &image)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<< /Type /XObject /Subtype /Image\n";
    output_ += "   /Width ";
    output_ += std::to_string(image.width());
    output_ += "\n";
    output_ += "   /Height ";
    output_ += std::to_string(image.height());
    output_ += "\n";
    output_ += "   /ColorSpace ";
    output_ += name(pdf_color_space_name(image.color_space()));
    output_ += "\n";
    output_ += "   /BitsPerComponent 8\n";
    output_ += "   /Filter /DCTDecode\n";
    output_ += "   /Length ";
    output_ += std::to_string(image.data().size());
    output_ += "\n";
    output_ += ">>\n";
    output_ += "stream\n";
    output_.append(
        reinterpret_cast<const char *>(image.data().data()),
        image.data().size());
    output_ += "\nendstream\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::write_info(
      int object_id,
      const Metadata &metadata)
  {
    mark_offset(object_id);

    output_ += std::to_string(object_id) + " 0 obj\n";
    output_ += "<<\n";

    if (!metadata.title().empty())
    {
      output_ += "  /Title ";
      output_ += literal_string(metadata.title());
      output_ += "\n";
    }

    if (!metadata.author().empty())
    {
      output_ += "  /Author ";
      output_ += literal_string(metadata.author());
      output_ += "\n";
    }

    if (!metadata.subject().empty())
    {
      output_ += "  /Subject ";
      output_ += literal_string(metadata.subject());
      output_ += "\n";
    }

    if (!metadata.creator().empty())
    {
      output_ += "  /Creator ";
      output_ += literal_string(metadata.creator());
      output_ += "\n";
    }

    if (!metadata.keywords().empty())
    {
      output_ += "  /Keywords ";
      output_ += literal_string(metadata.keywords());
      output_ += "\n";
    }

    output_ += ">>\n";
    output_ += "endobj\n";
  }

  void ObjectWriter::mark_offset(int object_id)
  {
    if (object_id >= 0 &&
        static_cast<std::size_t>(object_id) < offsets_.size())
    {
      offsets_[static_cast<std::size_t>(object_id)] = output_.size();
    }
  }
} // namespace rixlib::pdf::writer
