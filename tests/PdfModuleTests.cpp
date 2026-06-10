/**
 *
 *  @file PdfModuleTests.cpp
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

#include <rix/pdf.hpp>

#include <cassert>
#include <string>

int main()
{
  using namespace rixlib::pdf;

  auto pdf = module();

  assert(pdf.version() == "0.1.0");
  assert(pdf.version_major() == 0);
  assert(pdf.version_minor() == 1);
  assert(pdf.version_patch() == 0);
  assert(pdf.version_number() == 100);

  auto ok = pdf.error.none();

  assert(ok.ok());
  assert(pdf.error.ok(ok));
  assert(!pdf.error.failed(ok));
  assert(pdf.error.to_string(ok) == "None");

  auto error = pdf.error.make(
      PdfErrorCode::InvalidInput,
      "invalid input");

  assert(error.has_error());
  assert(pdf.error.failed(error));
  assert(pdf.error.is(error, PdfErrorCode::InvalidInput));
  assert(pdf.error.to_string(error) == "InvalidInput");

  auto doc = pdf.document();

  assert(doc.empty());
  assert(doc.default_page_size() == PageSize::A4());

  auto &page = doc.add_page();

  page.heading(
      page.x_left(),
      page.y_top(),
      "Rix PDF",
      1);

  page.text(
      page.x_left(),
      page.y_top() - 50.0F,
      "Hello from the public PDF module");

  auto data = pdf.write(doc);

  assert(data.ok());

  const std::string &bytes = data.value();

  assert(!bytes.empty());
  assert(bytes.find("%PDF-1.4") != std::string::npos);
  assert(bytes.find("/Type /Catalog") != std::string::npos);
  assert(bytes.find("(Hello from the public PDF module) Tj") != std::string::npos);
  assert(bytes.find("xref") != std::string::npos);
  assert(bytes.find("%%EOF") != std::string::npos);

  auto writer = pdf.writer.create();
  auto writer_data = writer.write(doc);

  assert(writer_data.ok());
  assert(writer_data.value().find("%PDF-1.4") != std::string::npos);

  auto bad_save = pdf.save(doc, "");

  assert(bad_save.failed());
  assert(bad_save.error().is(PdfErrorCode::InvalidInput));

  auto text_status = pdf.make_text(
      "",
      "This should fail because the path is empty.",
      "Rix PDF");

  assert(text_status.failed());
  assert(text_status.error().is(PdfErrorCode::InvalidInput));

  auto image = pdf.image.from_jpeg_bytes({0x00, 0x01, 0x02});

  assert(image.failed());
  assert(image.error().is(PdfErrorCode::InvalidImage));

  return 0;
}
