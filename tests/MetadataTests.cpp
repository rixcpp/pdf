/**
 *
 *  @file MetadataTests.cpp
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

#include <rix/pdf/document/Metadata.hpp>

#include <cassert>

int main()
{
  using namespace rixlib::pdf;

  Metadata metadata;

  assert(metadata.empty());
  assert(metadata.title().empty());
  assert(metadata.author().empty());
  assert(metadata.subject().empty());
  assert(metadata.creator() == "rix/pdf");
  assert(metadata.keywords().empty());

  metadata.set_title("Rix PDF");
  metadata.set_author("Gaspard Kirira");
  metadata.set_subject("PDF generation");
  metadata.set_creator("custom creator");
  metadata.set_keywords("pdf, rix, vix");

  assert(!metadata.empty());
  assert(metadata.title() == "Rix PDF");
  assert(metadata.author() == "Gaspard Kirira");
  assert(metadata.subject() == "PDF generation");
  assert(metadata.creator() == "custom creator");
  assert(metadata.keywords() == "pdf, rix, vix");

  metadata.set_creator("");

  assert(metadata.creator() == "rix/pdf");

  metadata.clear();

  assert(metadata.empty());
  assert(metadata.title().empty());
  assert(metadata.author().empty());
  assert(metadata.subject().empty());
  assert(metadata.creator() == "rix/pdf");
  assert(metadata.keywords().empty());

  return 0;
}
