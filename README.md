# rix/pdf

`rix/pdf` is the PDF generation package for Rix and Vix.cpp applications.

It provides a small production-oriented C++20 PDF writer with explicit error handling, a clean document model, and a high-level public facade.

The goal is simple:

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();
  auto doc = pdf.document();
  auto &page = doc.add_page();
  page.text(page.x_left(),page.y_top(), "Hello from rix/pdf");
  auto saved = pdf.save(doc, "hello.pdf");
  return saved.ok() ? 0 : 1;
}
```

## Design

`rix/pdf` is built around three layers.

```txt
core      -> stable primitive types
document  -> document model and user-facing drawing API
writer    -> internal PDF serialization
```

The public API stays simple.

The PDF writing complexity stays inside the writer layer.

## Features

- PDF 1.4 generation
- Multi-page documents
- A4, A3, Letter, Legal, and custom page sizes
- Margins
- Text drawing
- Paragraph wrapping
- Text alignment
- Headings
- Tables
- Lines
- Rectangles
- Filled rectangles
- Circles
- JPEG image embedding
- Document metadata
- Explicit `PdfResult<T>` and `PdfStatus` error handling

## Install

```bash
vix add @rix/pdf
vix install
```

## Basic usage

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();
  auto doc = pdf.document();
  auto &page = doc.add_page();

  page.text(page.x_left(),page.y_top(), "Hello from rix/pdf");
  page.text(page.x_left(),page.y_top() - 30.0F,"This PDF was generated from C++.");

  auto saved = pdf.save(doc, "basic.pdf");

  return saved.ok() ? 0 : 1;
}
```

## Error handling

`rix/pdf` does not require users to catch exceptions for normal PDF failures.

Most operations return either:

```cpp
rixlib::pdf::PdfResult<T>
```

or:

```cpp
rixlib::pdf::PdfStatus
```

Example:

```cpp
auto saved = pdf.save(doc, "output.pdf");

if (saved.failed())
{
  const auto &error = saved.error();

  // error.code()
  // error.message()
}
```

The public error helpers are available through:

```cpp
pdf.error.to_string(error)
pdf.error.is(error, rixlib::pdf::PdfErrorCode::InvalidInput)
```

## Text example

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();
  auto doc = pdf.document();

  doc.set_title("Rix PDF Text Example");
  doc.set_author("Rix");

  auto &page = doc.add_page();
  auto y = page.y_top();

  y = page.heading(page.x_left(),y,"Rix PDF",1);
  y -= 10.0F;

  page.paragraph(
      page.x_left(),
      y,
      page.content_width(),
      "rix/pdf is a small PDF generation library for Rix and Vix.cpp applications. "
      "It keeps common PDF workflows simple while writer internals stay hidden."
  );

  auto saved = pdf.save(doc, "text.pdf");

  return saved.ok() ? 0 : 1;
}
```

## Table example

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();
  auto doc = pdf.document();
  auto &page = doc.add_page();
  auto y = page.heading(page.x_left(),page.y_top(),"Project table",1);
  y -= 20.0F;

  rixlib::pdf::Table table;

  table.set_column_widths({
      160.0F,
      160.0F,
      160.0F
  });

  table.add_header({
      "Name",
      "Language",
      "Project"
  });

  table.add_row({
      "Ada",
      "C++",
      "Rix"
  });

  table.add_row({
      "Gaspard",
      "C++",
      "Vix.cpp"
  });

  page.table(
      page.x_left(),
      y,
      table
  );

  auto saved = pdf.save(doc, "table.pdf");

  return saved.ok() ? 0 : 1;
}
```

## Drawing example

```cpp
#include <rix/pdf.hpp>

int main()
{
  auto pdf = rixlib::pdf::module();
  auto doc = pdf.document();
  auto &page = doc.add_page();

  auto y = page.heading(
      page.x_left(),
      page.y_top(),
      "Drawing primitives",
      1
  );

  y -= 20.0F;

  page.line(
      page.x_left(),
      y,
      page.x_right(),
      y,
      1.5F,
      rixlib::pdf::Color::blue_color()
  );

  y -= 70.0F;

  page.rect(
      page.x_left(),
      y,
      140.0F,
      50.0F
  );

  page.fill_rect(
      page.x_left() + 170.0F,
      y,
      140.0F,
      50.0F,
      rixlib::pdf::Color::light_gray()
  );

  page.circle(
      page.x_left() + 380.0F,
      y + 25.0F,
      25.0F,
      1.0F,
      rixlib::pdf::Color::red_color()
  );

  auto saved = pdf.save(doc, "drawing.pdf");

  return saved.ok() ? 0 : 1;
}
```

## Metadata

```cpp
auto doc = pdf.document();

doc.set_title("Rix PDF Metadata Example")
    .set_author("Rix")
    .set_subject("PDF metadata")
    .set_keywords("rix,pdf,vix,cpp");
```

The default creator is:

```txt
rix/pdf
```

## Public facade API

```cpp
auto pdf = rixlib::pdf::module();

pdf.document()
pdf.document(page_size, margins)

pdf.write(document)
pdf.save(document, "output.pdf")
pdf.make_text("output.pdf", "content", "title")

pdf.error.to_string(error)
pdf.error.make(code, message)
pdf.error.none()

pdf.image.load_jpeg("image.jpg")
pdf.image.from_jpeg_bytes(bytes)

pdf.writer.write(document)
pdf.writer.save(document, "output.pdf")
pdf.writer.create()

pdf.version()
```

## Core types

```cpp
rixlib::pdf::Color
rixlib::pdf::Font
rixlib::pdf::FontFamily
rixlib::pdf::FontStyle
rixlib::pdf::Align
rixlib::pdf::LineStyle
rixlib::pdf::PageSize
rixlib::pdf::Margins
rixlib::pdf::PdfError
rixlib::pdf::PdfResult<T>
rixlib::pdf::PdfStatus
```

## Document model

```cpp
rixlib::pdf::Document
rixlib::pdf::Page
rixlib::pdf::Metadata
rixlib::pdf::Image
rixlib::pdf::Table
rixlib::pdf::TableRow
rixlib::pdf::TableCell
rixlib::pdf::TableStyle
rixlib::pdf::TextStyle
rixlib::pdf::BorderStyle
```

## Writer layer

The writer layer is available for advanced users, but most applications should use the facade helpers.

```cpp
rixlib::pdf::writer::PdfWriter writer;

auto data = writer.write(doc);
auto saved = writer.save(doc, "output.pdf");
```

Lower-level writer internals such as object writing, font registries, image registries, escaping, and xref generation are implementation details.

## Build

```bash
vix build
```

## Run examples

```bash
vix run rix_pdf_01_basic
vix run rix_pdf_02_text
vix run rix_pdf_03_table
vix run rix_pdf_04_drawing
vix run rix_pdf_05_metadata
```

## Tests

```bash
vix tests
```

## Repository layout

```txt
pdf/
├── include/
│   └── rix/
│       ├── pdf.hpp
│       └── pdf/
│           ├── PdfModule.hpp
│           ├── Version.hpp
│           ├── core/
│           ├── document/
│           └── writer/
├── src/
│   ├── PdfModule.cpp
│   ├── Version.cpp
│   ├── core/
│   ├── document/
│   └── writer/
├── examples/
├── tests/
├── CMakeLists.txt
├── README.md
├── LICENSE
└── vix.json
```

## Package model

```txt
Vix        -> runtime, CLI, build workflow, registry client
Rix        -> userland libraries and unified facade
rix/pdf    -> PDF generation package
```

## License

MIT
