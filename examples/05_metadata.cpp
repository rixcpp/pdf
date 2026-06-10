/**
 *
 *  @file 05_metadata.cpp
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

int main()
{
  auto pdf = rixlib::pdf::module();

  auto doc = pdf.document();

  doc.set_title("Rix PDF Metadata Example")
      .set_author("Rix")
      .set_subject("PDF metadata")
      .set_keywords("rix,pdf,vix,cpp");

  auto &page = doc.add_page();

  auto y = page.y_top();

  y = page.heading(
      page.x_left(),
      y,
      "Metadata",
      1);

  y -= 10.0F;

  page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "This PDF includes title, author, subject, creator, and keyword metadata.",
      rixlib::pdf::Align::Left);

  auto saved = pdf.save(doc, "metadata.pdf");

  return saved.ok() ? 0 : 1;
}
