/**
 *
 *  @file 01_basic.cpp
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

  auto &page = doc.add_page();

  page.text(
      page.x_left(),
      page.y_top(),
      "Hello from rix/pdf");

  page.text(
      page.x_left(),
      page.y_top() - 30.0F,
      "This PDF was generated from C++.");

  auto saved = pdf.save(doc, "basic.pdf");

  if (saved.failed())
  {
    return 1;
  }

  return 0;
}
