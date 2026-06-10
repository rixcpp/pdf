/**
 *
 *  @file PageTests.cpp
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

#include <rix/pdf/document/Page.hpp>

#include <cassert>
#include <string>

int main()
{
  using namespace rixlib::pdf;

  Page page;

  assert(page.width() == PageSize::A4().width());
  assert(page.height() == PageSize::A4().height());
  assert(page.content_width() > 0.0F);
  assert(page.content_height() > 0.0F);
  assert(page.x_left() == page.margins().left());
  assert(page.x_right() == page.width() - page.margins().right());
  assert(page.y_top() == page.height() - page.margins().top());
  assert(page.y_bottom() == page.margins().bottom());
  assert(page.content_stream().empty());
  assert(page.fonts().empty());
  assert(page.images().empty());

  page.text(
      72.0F,
      720.0F,
      "Hello PDF");

  assert(!page.content_stream().empty());
  assert(page.content_stream().find("BT") != std::string::npos);
  assert(page.content_stream().find("(Hello PDF) Tj") != std::string::npos);
  assert(page.fonts().size() == 1);
  assert(page.fonts()[0] == Font::Helvetica);
  assert(page.font_index(Font::Helvetica) == 1);

  page.text(
      72.0F,
      700.0F,
      "Bold",
      TextStyle{Font::HelveticaBold, 14.0F});

  assert(page.fonts().size() == 2);
  assert(page.font_index(Font::HelveticaBold) == 2);

  page.text_aligned(
      72.0F,
      680.0F,
      200.0F,
      "Centered",
      Align::Center);

  page.paragraph(
      72.0F,
      650.0F,
      150.0F,
      "This is a wrapped paragraph rendered by rix/pdf.",
      Align::Left);

  page.heading(
      72.0F,
      600.0F,
      "Heading",
      1);

  page.line(
      72.0F,
      580.0F,
      200.0F,
      580.0F);

  page.rect(
      72.0F,
      500.0F,
      100.0F,
      50.0F);

  page.fill_rect(
      200.0F,
      500.0F,
      100.0F,
      50.0F,
      Color::light_gray());

  page.fill_stroke_rect(
      320.0F,
      500.0F,
      100.0F,
      50.0F,
      Color::white(),
      Color::black());

  page.circle(
      450.0F,
      525.0F,
      25.0F);

  page.hrule(480.0F);

  page.page_number(1, 10);

  assert(page.content_stream().find(" m\n") != std::string::npos);
  assert(page.content_stream().find(" l\n") != std::string::npos);
  assert(page.content_stream().find(" re\n") != std::string::npos);
  assert(page.content_stream().find("S\n") != std::string::npos);

  Table table;
  table.set_column_widths({100.0F, 100.0F});
  table.add_header({"Name", "Project"});
  table.add_row({"Ada", "Rix"});
  table.add_row({"Gaspard", "Vix.cpp"});

  const auto after_table = page.table(
      72.0F,
      450.0F,
      table);

  assert(after_table < 450.0F);
  assert(page.content_stream().find("Name") != std::string::npos);
  assert(page.content_stream().find("Gaspard") != std::string::npos);

  return 0;
}
