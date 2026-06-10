/**
 *
 *  @file 02_text.cpp
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

  doc.set_title("Rix PDF Text Example");
  doc.set_author("Rix");

  auto &page = doc.add_page();

  auto y = page.y_top();

  y = page.heading(
      page.x_left(),
      y,
      "Rix PDF",
      1);

  y -= 10.0F;

  y = page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "rix/pdf is a small PDF generation library for Rix and Vix.cpp applications. "
      "It keeps common PDF workflows simple while the writer internals stay hidden.",
      rixlib::pdf::Align::Left);

  y -= 20.0F;

  page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "This paragraph is centered to show text alignment.",
      rixlib::pdf::Align::Center,
      rixlib::pdf::TextStyle{
          rixlib::pdf::Font::Helvetica,
          12.0F,
          rixlib::pdf::Color::blue_color()});

  auto saved = pdf.save(doc, "text.pdf");

  return saved.ok() ? 0 : 1;
}
