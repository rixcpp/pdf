/**
 *
 *  @file 03_table.cpp
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

  doc.set_title("Rix PDF Table Example");

  auto &page = doc.add_page();

  auto y = page.y_top();

  y = page.heading(
      page.x_left(),
      y,
      "Project table",
      1);

  y -= 20.0F;

  rixlib::pdf::Table table;

  table.set_column_widths({160.0F,
                           160.0F,
                           160.0F});

  table.add_header({"Name",
                    "Language",
                    "Project"});

  table.add_row({"Ada",
                 "C++",
                 "Rix"});

  table.add_row({"Gaspard",
                 "C++",
                 "Vix.cpp"});

  table.add_row({"Grace",
                 "Systems",
                 "PDF"});

  page.table(
      page.x_left(),
      y,
      table);

  auto saved = pdf.save(doc, "table.pdf");

  return saved.ok() ? 0 : 1;
}
