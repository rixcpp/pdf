/**
 *
 *  @file DocumentTests.cpp
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

#include <rix/pdf/document/Document.hpp>

#include <cassert>

int main()
{
  using namespace rixlib::pdf;

  Document doc;

  assert(doc.empty());
  assert(doc.page_count() == 0);
  assert(doc.default_page_size() == PageSize::A4());
  assert(doc.default_margins() == Margins{});
  assert(doc.metadata().creator() == "rix/pdf");

  doc.set_title("Rix PDF")
      .set_author("Gaspard Kirira")
      .set_subject("PDF document model")
      .set_creator("test")
      .set_keywords("pdf,document,test");

  assert(doc.metadata().title() == "Rix PDF");
  assert(doc.metadata().author() == "Gaspard Kirira");
  assert(doc.metadata().subject() == "PDF document model");
  assert(doc.metadata().creator() == "test");
  assert(doc.metadata().keywords() == "pdf,document,test");

  auto &page1 = doc.add_page();

  assert(!doc.empty());
  assert(doc.page_count() == 1);
  assert(&doc.page(0) == &page1);
  assert(doc.page(0).size() == PageSize::A4());

  auto &page2 = doc.add_page(PageSize::Letter());

  assert(doc.page_count() == 2);
  assert(&doc.page(1) == &page2);
  assert(doc.page(1).size() == PageSize::Letter());

  auto margins = Margins::none();
  auto &page3 = doc.add_page(PageSize::Legal(), margins);

  assert(doc.page_count() == 3);
  assert(&doc.page(2) == &page3);
  assert(doc.page(2).size() == PageSize::Legal());
  assert(doc.page(2).margins() == margins);

  doc.set_default_page_size(PageSize::A3());
  doc.set_default_margins(Margins::none());

  auto &page4 = doc.add_page();

  assert(doc.page_count() == 4);
  assert(&doc.page(3) == &page4);
  assert(doc.page(3).size() == PageSize::A3());
  assert(doc.page(3).margins() == Margins::none());

  Metadata metadata;
  metadata.set_title("Metadata object");

  doc.set_metadata(metadata);

  assert(doc.metadata().title() == "Metadata object");
  assert(doc.metadata().creator() == "rix/pdf");

  doc.clear_pages();

  assert(doc.empty());
  assert(doc.page_count() == 0);

  return 0;
}
