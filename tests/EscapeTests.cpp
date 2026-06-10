/**
 *
 *  @file EscapeTests.cpp
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

#include <rix/pdf/writer/Escape.hpp>

#include <cassert>

int main()
{
  using namespace rixlib::pdf::writer;

  assert(escape_literal_string("Hello") == "Hello");
  assert(escape_literal_string("(Hello)") == "\\(Hello\\)");
  assert(escape_literal_string("a\\b") == "a\\\\b");
  assert(escape_literal_string("line\nnext") == "line\\nnext");
  assert(escape_literal_string("line\rnext") == "line\\rnext");
  assert(escape_literal_string("tab\tnext") == "tab\\tnext");
  assert(escape_literal_string("back\bnext") == "back\\bnext");
  assert(escape_literal_string("form\fnext") == "form\\fnext");

  assert(literal_string("Hello") == "(Hello)");
  assert(literal_string("(Hello)") == "(\\(Hello\\))");

  assert(escape_name("Helvetica") == "Helvetica");
  assert(escape_name("Times-Roman") == "Times-Roman");
  assert(escape_name("A B") == "A#20B");
  assert(escape_name("A/B") == "A#2FB");
  assert(escape_name("A#B") == "A#23B");
  assert(escape_name("(A)") == "#28A#29");

  assert(name("Helvetica") == "/Helvetica");
  assert(name("A B") == "/A#20B");

  return 0;
}
