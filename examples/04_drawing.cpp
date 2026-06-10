/**
 *
 *  @file 04_drawing.cpp
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

  doc.set_title("Rix PDF Drawing Example");

  auto &page = doc.add_page();

  auto y = page.y_top();

  y = page.heading(
      page.x_left(),
      y,
      "Drawing primitives",
      1);

  y -= 20.0F;

  page.line(
      page.x_left(),
      y,
      page.x_right(),
      y,
      1.5F,
      rixlib::pdf::Color::blue_color());

  y -= 70.0F;

  page.rect(
      page.x_left(),
      y,
      140.0F,
      50.0F,
      1.0F,
      rixlib::pdf::Color::black());

  page.fill_rect(
      page.x_left() + 170.0F,
      y,
      140.0F,
      50.0F,
      rixlib::pdf::Color::light_gray());

  page.fill_stroke_rect(
      page.x_left() + 340.0F,
      y,
      140.0F,
      50.0F,
      rixlib::pdf::Color::white(),
      rixlib::pdf::Color::black(),
      1.0F);

  y -= 100.0F;

  page.circle(
      page.x_left() + 70.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::red_color(),
      false);

  page.circle(
      page.x_left() + 230.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::green_color(),
      true);

  page.circle(
      page.x_left() + 390.0F,
      y,
      35.0F,
      1.0F,
      rixlib::pdf::Color::blue_color(),
      false);

  y -= 80.0F;

  page.hrule(
      y,
      -1.0F,
      -1.0F,
      0.5F,
      rixlib::pdf::Color::gray());

  page.text(
      page.x_left(),
      y - 30.0F,
      "Generated with rix/pdf drawing APIs.");

  auto saved = pdf.save(doc, "drawing.pdf");

  return saved.ok() ? 0 : 1;
}
