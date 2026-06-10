/**
 * @file pdf.hpp
 * @brief PDF Generation Library — C++20, Header-Only, Production-Ready
 *
 * Generates standard PDF 1.4 files from scratch.
 * No external dependencies.
 *
 * Features:
 *   - Multi-page documents
 *   - Text with 14 standard PDF fonts
 *   - Font styles: bold, italic, bold-italic
 *   - Text alignment: left, center, right, justify
 *   - Automatic word-wrap and line-break
 *   - Paragraph and heading helpers
 *   - Tables with borders and column alignment
 *   - Basic vector drawing: lines, rects, circles
 *   - JPEG image embedding
 *   - Document metadata (title, author, subject)
 *   - Page size presets: A4, Letter, A3, Legal
 *   - Custom page sizes
 *   - Margins support
 *
 * Usage:
 *   pdf::Document doc;
 *   auto& page = doc.add_page();
 *   page.text(50, 750, "Hello, World!", pdf::Font::Helvetica, 24);
 *   doc.save("hello.pdf");
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace pdf
{
  enum class Font : uint8_t
  {
    Helvetica = 0,
    HelveticaBold,
    HelveticaOblique,
    HelveticaBoldOblique,
    Times,
    TimesBold,
    TimesItalic,
    TimesBoldItalic,
    Courier,
    CourierBold,
    CourierOblique,
    CourierBoldOblique,
    Symbol,
    ZapfDingbats,
  };

  enum class Align : uint8_t
  {
    Left,
    Center,
    Right,
    Justify
  };

  enum class LineStyle : uint8_t
  {
    Solid,
    Dashed,
    Dotted
  };

  /// RGB color (components 0.0–1.0)
  struct Color
  {
    float r = 0.f, g = 0.f, b = 0.f;

    static constexpr Color black() { return {0.f, 0.f, 0.f}; }
    static constexpr Color white() { return {1.f, 1.f, 1.f}; }
    static constexpr Color red() { return {1.f, 0.f, 0.f}; }
    static constexpr Color green() { return {0.f, 0.5f, 0.f}; }
    static constexpr Color blue() { return {0.f, 0.f, 1.f}; }
    static constexpr Color gray() { return {0.5f, 0.5f, 0.5f}; }
    static constexpr Color lightgray() { return {0.85f, 0.85f, 0.85f}; }
    static constexpr Color from_hex(uint32_t hex)
    {
      return {
          ((hex >> 16) & 0xFF) / 255.f,
          ((hex >> 8) & 0xFF) / 255.f,
          (hex & 0xFF) / 255.f,
      };
    }
  };

  /// Page size in points (1 pt = 1/72 inch)
  struct PageSize
  {
    float width;
    float height;

    static constexpr PageSize A4() { return {595.28f, 841.89f}; }
    static constexpr PageSize A3() { return {841.89f, 1190.55f}; }
    static constexpr PageSize Letter() { return {612.f, 792.f}; }
    static constexpr PageSize Legal() { return {612.f, 1008.f}; }
    static constexpr PageSize custom(float w, float h) { return {w, h}; }
  };

  struct Margins
  {
    float top = 72.f; // 1 inch
    float bottom = 72.f;
    float left = 72.f;
    float right = 72.f;
  };

  struct TextStyle
  {
    Font font = Font::Helvetica;
    float size = 12.f;
    Color color = Color::black();
    float line_height = 1.2f; // multiplier of font size
  };

  struct BorderStyle
  {
    bool top = true;
    bool bottom = true;
    bool left = true;
    bool right = true;
    float width = 0.5f;
    Color color = Color::black();
  };

  namespace detail
  {

    // Standard character widths for Helvetica (chars 32–127)
    static constexpr std::array<int, 96> HELVETICA_WIDTHS = {{278, 278, 355, 556, 556, 889, 667, 191, 333, 333, 389, 584, 278, 333, 278, 278,
                                                              556, 556, 556, 556, 556, 556, 556, 556, 556, 556, 278, 278, 584, 584, 584, 556,
                                                              1015, 667, 667, 722, 722, 667, 611, 778, 722, 278, 500, 667, 556, 833, 722, 778,
                                                              667, 778, 722, 667, 611, 722, 667, 944, 667, 667, 611, 278, 278, 278, 469, 556,
                                                              333, 556, 556, 500, 556, 556, 278, 556, 556, 222, 222, 500, 222, 833, 556, 556,
                                                              556, 556, 333, 500, 278, 556, 500, 722, 500, 500, 500, 334, 260, 334, 584, 350}};

    static constexpr std::array<int, 96> HELVETICA_BOLD_WIDTHS = {{278, 333, 474, 556, 556, 889, 722, 238, 333, 333, 389, 584, 278, 333, 278, 278,
                                                                   556, 556, 556, 556, 556, 556, 556, 556, 556, 556, 333, 333, 584, 584, 584, 611,
                                                                   975, 722, 722, 722, 722, 667, 611, 778, 722, 278, 556, 722, 611, 833, 722, 778,
                                                                   667, 778, 722, 667, 611, 722, 667, 944, 667, 667, 611, 333, 278, 333, 584, 556,
                                                                   333, 556, 611, 556, 611, 556, 333, 611, 611, 278, 278, 556, 278, 889, 611, 611,
                                                                   611, 611, 389, 556, 333, 611, 556, 778, 556, 556, 500, 389, 280, 389, 584, 350}};

    static constexpr std::array<int, 96> COURIER_WIDTHS = {{600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
                                                            600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
                                                            600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
                                                            600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
                                                            600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
                                                            600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600}};

    static constexpr std::array<int, 96> TIMES_WIDTHS = {{250, 333, 408, 500, 500, 833, 778, 180, 333, 333, 500, 564, 250, 333, 250, 278,
                                                          500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 278, 278, 564, 564, 564, 444,
                                                          921, 722, 667, 667, 722, 611, 556, 722, 722, 333, 389, 722, 611, 889, 722, 722,
                                                          556, 722, 667, 556, 611, 722, 722, 944, 722, 722, 611, 333, 278, 333, 469, 500,
                                                          333, 444, 500, 444, 500, 444, 333, 500, 500, 278, 278, 500, 278, 778, 500, 500,
                                                          500, 500, 333, 389, 278, 500, 500, 722, 500, 500, 444, 480, 200, 480, 541, 350}};

    /// Get character width table for a font (in 1/1000 pt units)
    inline const std::array<int, 96> &font_widths(Font f)
    {
      switch (f)
      {
      case Font::HelveticaBold:
      case Font::HelveticaBoldOblique:
        return HELVETICA_BOLD_WIDTHS;
      case Font::Courier:
      case Font::CourierBold:
      case Font::CourierOblique:
      case Font::CourierBoldOblique:
        return COURIER_WIDTHS;
      case Font::Times:
      case Font::TimesBold:
      case Font::TimesItalic:
      case Font::TimesBoldItalic:
        return TIMES_WIDTHS;
      default:
        return HELVETICA_WIDTHS;
      }
    }

    /// Compute text width in points
    inline float text_width(std::string_view text, Font font, float size)
    {
      const auto &widths = font_widths(font);
      float total = 0.f;
      for (unsigned char c : text)
      {
        if (c >= 32 && c < 128)
          total += widths[c - 32];
        else
          total += 600; // fallback
      }
      return total * size / 1000.f;
    }

    /// PDF font resource name
    inline std::string_view font_name(Font f)
    {
      switch (f)
      {
      case Font::Helvetica:
        return "Helvetica";
      case Font::HelveticaBold:
        return "Helvetica-Bold";
      case Font::HelveticaOblique:
        return "Helvetica-Oblique";
      case Font::HelveticaBoldOblique:
        return "Helvetica-BoldOblique";
      case Font::Times:
        return "Times-Roman";
      case Font::TimesBold:
        return "Times-Bold";
      case Font::TimesItalic:
        return "Times-Italic";
      case Font::TimesBoldItalic:
        return "Times-BoldItalic";
      case Font::Courier:
        return "Courier";
      case Font::CourierBold:
        return "Courier-Bold";
      case Font::CourierOblique:
        return "Courier-Oblique";
      case Font::CourierBoldOblique:
        return "Courier-BoldOblique";
      case Font::Symbol:
        return "Symbol";
      case Font::ZapfDingbats:
        return "ZapfDingbats";
      }
      return "Helvetica";
    }

    /// Escape a string for PDF string literal
    inline std::string pdf_escape(std::string_view s)
    {
      std::string out;
      out.reserve(s.size() + 8);
      for (unsigned char c : s)
      {
        if (c == '(')
          out += "\\(";
        else if (c == ')')
          out += "\\)";
        else if (c == '\\')
          out += "\\\\";
        else if (c == '\n')
          out += "\\n";
        else if (c == '\r')
          out += "\\r";
        else if (c == '\t')
          out += "\\t";
        else
          out += static_cast<char>(c);
      }
      return out;
    }

    /// Float to compact string (max 4 decimal places, trim trailing zeros)
    inline std::string f2s(float v)
    {
      std::ostringstream ss;
      ss << std::fixed << std::setprecision(4) << v;
      std::string s = ss.str();
      auto dot = s.find('.');
      if (dot != std::string::npos)
      {
        std::size_t last = s.find_last_not_of('0');
        if (last != std::string::npos && last > dot)
          s = s.substr(0, last + 1);
        else if (last == dot)
          s = s.substr(0, dot);
      }
      return s;
    }

    /// Color command (stroke or fill)
    inline std::string color_cmd(Color c, bool stroke)
    {
      std::string s = f2s(c.r) + " " + f2s(c.g) + " " + f2s(c.b) + " ";
      s += stroke ? "RG" : "rg";
      return s;
    }

    struct WrappedLine
    {
      std::string text;
      bool is_last; // last line of paragraph (affects justify)
    };

    inline std::vector<WrappedLine> wrap_text(std::string_view text,
                                              Font font, float size, float max_width)
    {
      std::vector<WrappedLine> lines;
      std::string current;
      std::string word;

      auto flush_word = [&]()
      {
        if (word.empty())
          return;
        std::string candidate = current.empty() ? word : (current + " " + word);
        if (text_width(candidate, font, size) <= max_width)
        {
          current = candidate;
        }
        else
        {
          if (!current.empty())
          {
            lines.push_back({current, false});
            current = word;
          }
          else
          {
            // word wider than line — force it
            lines.push_back({word, false});
            current.clear();
          }
        }
        word.clear();
      };

      for (char c : text)
      {
        if (c == '\n')
        {
          flush_word();
          lines.push_back({current, true});
          current.clear();
        }
        else if (c == ' ' || c == '\t')
        {
          flush_word();
        }
        else
        {
          word += c;
        }
      }
      flush_word();
      if (!current.empty())
        lines.push_back({current, true});
      else if (!lines.empty())
        lines.back().is_last = true;
      return lines;
    }

  } // namespace detail

  struct Image
  {
    std::vector<uint8_t> data;
    int width = 0;
    int height = 0;
    int components = 3; // 1=gray, 3=RGB, 4=CMYK

    /// Load JPEG from file (reads raw bytes + parses SOF0 for dimensions)
    [[nodiscard]] static Image load_jpeg(const std::string &path)
    {
      std::ifstream f(path, std::ios::binary);
      if (!f)
        throw std::runtime_error("Cannot open image: " + path);
      Image img;
      img.data = std::vector<uint8_t>(
          std::istreambuf_iterator<char>(f),
          std::istreambuf_iterator<char>());
      parse_jpeg_dims(img);
      return img;
    }

    /// Load JPEG from memory buffer
    [[nodiscard]] static Image from_jpeg_bytes(std::vector<uint8_t> bytes)
    {
      Image img;
      img.data = std::move(bytes);
      parse_jpeg_dims(img);
      return img;
    }

  private:
    static void parse_jpeg_dims(Image &img)
    {
      const auto &d = img.data;
      if (d.size() < 4 || d[0] != 0xFF || d[1] != 0xD8)
        throw std::runtime_error("Not a valid JPEG file");
      std::size_t i = 2;
      while (i + 4 < d.size())
      {
        if (d[i] != 0xFF)
        {
          ++i;
          continue;
        }
        uint8_t marker = d[i + 1];
        uint16_t len = (static_cast<uint16_t>(d[i + 2]) << 8) | d[i + 3];
        // SOF0, SOF1, SOF2 contain image dimensions
        if ((marker >= 0xC0 && marker <= 0xC3) && i + 9 < d.size())
        {
          img.components = d[i + 4 + 3];
          img.height = (static_cast<int>(d[i + 5]) << 8) | d[i + 6];
          img.width = (static_cast<int>(d[i + 7]) << 8) | d[i + 8];
          return;
        }
        i += 2 + len;
      }
      throw std::runtime_error("Could not parse JPEG dimensions");
    }
  };

  struct TableCell
  {
    std::string text;
    Align align = Align::Left;
    Color text_color = Color::black();
    Color bg_color = Color::white();
    bool has_bg = false;
    int colspan = 1;
  };

  struct TableRow
  {
    std::vector<TableCell> cells;
    bool is_header = false;
    Color header_bg = Color::from_hex(0x2c3e50);
    Color header_fg = Color::white();
    float height = 0.f; // 0 = auto
  };

  struct TableStyle
  {
    Font font = Font::Helvetica;
    float font_size = 10.f;
    Font header_font = Font::HelveticaBold;
    float header_size = 10.f;
    float row_height = 20.f;
    float cell_padding = 4.f;
    BorderStyle border;
    Color stripe_color = Color::from_hex(0xF2F2F2);
    bool stripe_rows = true;
  };

  class Page
  {
  public:
    explicit Page(PageSize size, Margins margins = {})
        : size_(size), margins_(margins) {}

    [[nodiscard]] float width() const noexcept { return size_.width; }
    [[nodiscard]] float height() const noexcept { return size_.height; }

    [[nodiscard]] float content_width() const noexcept
    {
      return size_.width - margins_.left - margins_.right;
    }
    [[nodiscard]] float content_height() const noexcept
    {
      return size_.height - margins_.top - margins_.bottom;
    }
    [[nodiscard]] float x_left() const noexcept { return margins_.left; }
    [[nodiscard]] float x_right() const noexcept { return size_.width - margins_.right; }
    [[nodiscard]] float y_top() const noexcept { return size_.height - margins_.top; }
    [[nodiscard]] float y_bottom() const noexcept { return margins_.bottom; }

    /// Draw a single line of text at (x, y) — y is baseline from bottom
    Page &text(float x, float y, std::string_view str,
               Font font = Font::Helvetica, float size = 12.f,
               Color color = Color::black())
    {
      use_font(font);
      stream_ += "BT\n";
      stream_ += detail::color_cmd(color, false) + "\n";
      stream_ += "/F" + std::to_string(font_index(font)) +
                 " " + detail::f2s(size) + " Tf\n";
      stream_ += detail::f2s(x) + " " + detail::f2s(y) + " Td\n";
      stream_ += "(" + detail::pdf_escape(str) + ") Tj\n";
      stream_ += "ET\n";
      return *this;
    }

    /// Draw text with alignment within a given width
    Page &text_aligned(float x, float y, float width, std::string_view str,
                       Font font, float size, Color color, Align align)
    {
      float tw = detail::text_width(str, font, size);
      float tx = x;
      switch (align)
      {
      case Align::Center:
        tx = x + (width - tw) / 2.f;
        break;
      case Align::Right:
        tx = x + width - tw;
        break;
      default:
        break;
      }
      text(tx, y, str, font, size, color);
      return *this;
    }

    /// Draw a paragraph with automatic word-wrap and alignment
    /// Returns the Y position after the last line
    float paragraph(float x, float y, float max_width, std::string_view str,
                    Font font = Font::Helvetica, float size = 12.f,
                    Color color = Color::black(), Align align = Align::Left,
                    float line_spacing = 1.4f)
    {
      auto lines = detail::wrap_text(str, font, size, max_width);
      float leading = size * line_spacing;
      float cy = y;

      use_font(font);
      stream_ += detail::color_cmd(color, false) + "\n";

      for (auto &line : lines)
      {
        if (line.text.empty())
        {
          cy -= leading;
          continue;
        }

        if (align == Align::Justify && !line.is_last && line.text.find(' ') != std::string::npos)
        {
          // Justified: compute word spacing
          float tw = detail::text_width(line.text, font, size);
          int spaces = static_cast<int>(std::count(line.text.begin(), line.text.end(), ' '));
          float ws = spaces > 0 ? (max_width - tw) / spaces : 0.f;

          stream_ += "BT\n";
          stream_ += "/F" + std::to_string(font_index(font)) +
                     " " + detail::f2s(size) + " Tf\n";
          stream_ += detail::f2s(ws) + " Tw\n";
          stream_ += detail::f2s(x) + " " + detail::f2s(cy) + " Td\n";
          stream_ += "(" + detail::pdf_escape(line.text) + ") Tj\n";
          stream_ += "0 Tw\n";
          stream_ += "ET\n";
        }
        else
        {
          float tx = x;
          float tw = detail::text_width(line.text, font, size);
          if (align == Align::Center)
            tx = x + (max_width - tw) / 2.f;
          else if (align == Align::Right)
            tx = x + max_width - tw;

          stream_ += "BT\n";
          stream_ += "/F" + std::to_string(font_index(font)) +
                     " " + detail::f2s(size) + " Tf\n";
          stream_ += detail::f2s(tx) + " " + detail::f2s(cy) + " Td\n";
          stream_ += "(" + detail::pdf_escape(line.text) + ") Tj\n";
          stream_ += "ET\n";
        }
        cy -= leading;
      }
      return cy;
    }

    /// Heading shortcut (bold, larger font)
    float heading(float x, float y, std::string_view str,
                  int level = 1, Color color = Color::black())
    {
      static constexpr std::array<float, 6> SIZES = {24.f, 20.f, 16.f, 14.f, 13.f, 12.f};
      float sz = SIZES[std::clamp(level - 1, 0, 5)];
      Font f = Font::HelveticaBold;
      text(x, y, str, f, sz, color);
      return y - sz * 1.4f;
    }

    /// Draw a straight line
    Page &line(float x1, float y1, float x2, float y2,
               float width = 1.f, Color color = Color::black(),
               LineStyle style = LineStyle::Solid)
    {
      set_line_style(style, width);
      stream_ += detail::color_cmd(color, true) + "\n";
      stream_ += detail::f2s(x1) + " " + detail::f2s(y1) + " m\n";
      stream_ += detail::f2s(x2) + " " + detail::f2s(y2) + " l\n";
      stream_ += "S\n";
      reset_line_style(style);
      return *this;
    }

    /// Draw a rectangle (stroke only)
    Page &rect(float x, float y, float w, float h,
               float line_width = 1.f, Color color = Color::black())
    {
      stream_ += detail::f2s(line_width) + " w\n";
      stream_ += detail::color_cmd(color, true) + "\n";
      stream_ += detail::f2s(x) + " " + detail::f2s(y) + " " +
                 detail::f2s(w) + " " + detail::f2s(h) + " re\n";
      stream_ += "S\n";
      return *this;
    }

    /// Draw a filled rectangle
    Page &fill_rect(float x, float y, float w, float h, Color fill_color)
    {
      stream_ += detail::color_cmd(fill_color, false) + "\n";
      stream_ += detail::f2s(x) + " " + detail::f2s(y) + " " +
                 detail::f2s(w) + " " + detail::f2s(h) + " re\n";
      stream_ += "f\n";
      return *this;
    }

    /// Draw a filled + stroked rectangle
    Page &fill_stroke_rect(float x, float y, float w, float h,
                           Color fill_color, Color stroke_color,
                           float line_width = 1.f)
    {
      stream_ += detail::f2s(line_width) + " w\n";
      stream_ += detail::color_cmd(fill_color, false) + "\n";
      stream_ += detail::color_cmd(stroke_color, true) + "\n";
      stream_ += detail::f2s(x) + " " + detail::f2s(y) + " " +
                 detail::f2s(w) + " " + detail::f2s(h) + " re\n";
      stream_ += "B\n";
      return *this;
    }

    /// Draw a circle (approximated with Bézier curves)
    Page &circle(float cx, float cy, float r,
                 float line_width = 1.f, Color color = Color::black(),
                 bool filled = false)
    {
      const float k = 0.5522847498f * r;
      stream_ += detail::f2s(line_width) + " w\n";
      if (filled)
        stream_ += detail::color_cmd(color, false) + "\n";
      stream_ += detail::color_cmd(color, true) + "\n";

      stream_ += detail::f2s(cx) + " " + detail::f2s(cy + r) + " m\n";
      stream_ += detail::f2s(cx + k) + " " + detail::f2s(cy + r) + " " +
                 detail::f2s(cx + r) + " " + detail::f2s(cy + k) + " " +
                 detail::f2s(cx + r) + " " + detail::f2s(cy) + " c\n";
      stream_ += detail::f2s(cx + r) + " " + detail::f2s(cy - k) + " " +
                 detail::f2s(cx + k) + " " + detail::f2s(cy - r) + " " +
                 detail::f2s(cx) + " " + detail::f2s(cy - r) + " c\n";
      stream_ += detail::f2s(cx - k) + " " + detail::f2s(cy - r) + " " +
                 detail::f2s(cx - r) + " " + detail::f2s(cy - k) + " " +
                 detail::f2s(cx - r) + " " + detail::f2s(cy) + " c\n";
      stream_ += detail::f2s(cx - r) + " " + detail::f2s(cy + k) + " " +
                 detail::f2s(cx - k) + " " + detail::f2s(cy + r) + " " +
                 detail::f2s(cx) + " " + detail::f2s(cy + r) + " c\n";
      stream_ += (filled ? "B\n" : "S\n");
      return *this;
    }

    /// Draw a horizontal rule (full-width line)
    Page &hrule(float y, float x_start = -1, float x_end = -1,
                float width = 0.5f, Color color = Color::gray())
    {
      float xs = x_start < 0 ? margins_.left : x_start;
      float xe = x_end < 0 ? size_.width - margins_.right : x_end;
      line(xs, y, xe, y, width, color);
      return *this;
    }

    /// Place a JPEG image at (x, y) with given display width/height in points
    Page &image(const Image &img, float x, float y, float w, float h)
    {
      int idx = add_image(img);
      stream_ += "q\n";
      stream_ += detail::f2s(w) + " 0 0 " + detail::f2s(h) +
                 " " + detail::f2s(x) + " " + detail::f2s(y) + " cm\n";
      stream_ += "/Im" + std::to_string(idx) + " Do\n";
      stream_ += "Q\n";
      return *this;
    }

    /// Place image maintaining aspect ratio within a bounding box
    Page &image_fit(const Image &img, float x, float y, float max_w, float max_h)
    {
      float ar = static_cast<float>(img.width) / static_cast<float>(img.height);
      float w = max_w, h = max_w / ar;
      if (h > max_h)
      {
        h = max_h;
        w = max_h * ar;
      }
      return image(img, x, y, w, h);
    }

    /// Draw a table. columns = list of column widths in points.
    /// Returns Y position below the table.
    float draw_table(float x, float y,
                     const std::vector<float> &col_widths,
                     const std::vector<TableRow> &rows,
                     const TableStyle &style = {})
    {
      float cy = y;

      for (std::size_t ri = 0; ri < rows.size(); ++ri)
      {
        const auto &row = rows[ri];
        float rh = row.height > 0 ? row.height : style.row_height;

        float cx = x;
        for (std::size_t ci = 0; ci < col_widths.size(); ++ci)
        {
          float cw = col_widths[ci];
          if (ci >= row.cells.size())
          {
            // empty cell
            if (style.border.top || style.border.bottom ||
                style.border.left || style.border.right)
              draw_cell_border(cx, cy - rh, cw, rh, style.border);
            cx += cw;
            continue;
          }
          const auto &cell = row.cells[ci];

          // colspan
          float total_cw = cw;
          for (int span = 1; span < cell.colspan && ci + span < col_widths.size(); ++span)
            total_cw += col_widths[ci + span];

          // background
          if (row.is_header)
          {
            fill_rect(cx, cy - rh, total_cw, rh, row.header_bg);
          }
          else if (cell.has_bg)
          {
            fill_rect(cx, cy - rh, total_cw, rh, cell.bg_color);
          }
          else if (style.stripe_rows && ri % 2 == 1)
          {
            fill_rect(cx, cy - rh, total_cw, rh, style.stripe_color);
          }

          // cell border
          if (style.border.top || style.border.bottom ||
              style.border.left || style.border.right)
            draw_cell_border(cx, cy - rh, total_cw, rh, style.border);

          // cell text
          Font f = row.is_header ? style.header_font : style.font;
          float fsz = row.is_header ? style.header_size : style.font_size;
          Color fcol = row.is_header ? row.header_fg : cell.text_color;
          Align al = cell.align;

          float tx = cx + style.cell_padding;
          float tw = total_cw - 2.f * style.cell_padding;
          float ty = cy - rh + (rh - fsz) / 2.f + 2.f;

          text_aligned(tx, ty, tw, cell.text, f, fsz, fcol, al);

          cx += total_cw;
          ci += static_cast<std::size_t>(cell.colspan - 1);
        }
        cy -= rh;
      }
      return cy;
    }

    Page &page_number(int num, int total = -1,
                      float y = -1,
                      Font font = Font::Helvetica, float size = 9.f,
                      Color color = Color::gray())
    {
      std::string s = total > 0
                          ? std::to_string(num) + " / " + std::to_string(total)
                          : std::to_string(num);
      float fy = y < 0 ? margins_.bottom / 2.f : y;
      float fx = size_.width / 2.f - detail::text_width(s, font, size) / 2.f;
      text(fx, fy, s, font, size, color);
      return *this;
    }

    [[nodiscard]] const std::string &stream() const noexcept { return stream_; }
    [[nodiscard]] const std::vector<Font> &fonts() const noexcept { return fonts_used_; }
    [[nodiscard]] const std::vector<const Image *> &images() const noexcept { return images_; }
    [[nodiscard]] int image_count() const noexcept { return static_cast<int>(images_.size()); }
    [[nodiscard]] int font_index(Font f) const noexcept
    {
      for (int i = 0; i < static_cast<int>(fonts_used_.size()); ++i)
        if (fonts_used_[i] == f)
          return i + 1;
      return 1;
    }

  private:
    PageSize size_;
    Margins margins_;
    std::string stream_;
    std::vector<Font> fonts_used_;
    std::vector<const Image *> images_;

    void use_font(Font f)
    {
      if (std::find(fonts_used_.begin(), fonts_used_.end(), f) == fonts_used_.end())
        fonts_used_.push_back(f);
    }

    int add_image(const Image &img)
    {
      images_.push_back(&img);
      return static_cast<int>(images_.size()); // 1-based
    }

    void set_line_style(LineStyle style, float width)
    {
      stream_ += detail::f2s(width) + " w\n";
      switch (style)
      {
      case LineStyle::Dashed:
        stream_ += "[6 3] 0 d\n";
        break;
      case LineStyle::Dotted:
        stream_ += "[2 2] 0 d\n";
        break;
      default:
        stream_ += "[] 0 d\n";
        break;
      }
    }

    void reset_line_style(LineStyle style)
    {
      if (style != LineStyle::Solid)
        stream_ += "[] 0 d\n";
    }

    void draw_cell_border(float x, float y, float w, float h, const BorderStyle &b)
    {
      stream_ += detail::f2s(b.width) + " w\n";
      stream_ += detail::color_cmd(b.color, true) + "\n";
      if (b.left)
      {
        stream_ += detail::f2s(x) + " " + detail::f2s(y) + " m " + detail::f2s(x) + " " + detail::f2s(y + h) + " l S\n";
      }
      if (b.right)
      {
        stream_ += detail::f2s(x + w) + " " + detail::f2s(y) + " m " + detail::f2s(x + w) + " " + detail::f2s(y + h) + " l S\n";
      }
      if (b.bottom)
      {
        stream_ += detail::f2s(x) + " " + detail::f2s(y) + " m " + detail::f2s(x + w) + " " + detail::f2s(y) + " l S\n";
      }
      if (b.top)
      {
        stream_ += detail::f2s(x) + " " + detail::f2s(y + h) + " m " + detail::f2s(x + w) + " " + detail::f2s(y + h) + " l S\n";
      }
    }
  };

  struct Metadata
  {
    std::string title;
    std::string author;
    std::string subject;
    std::string creator = "pdf/1.0";
    std::string keywords;
  };

  class Document
  {
  public:
    explicit Document(PageSize default_size = PageSize::A4(),
                      Margins default_margins = {})
        : default_size_(default_size), default_margins_(default_margins) {}

    /// Add a new page with default size/margins, return reference
    Page &add_page()
    {
      pages_.emplace_back(default_size_, default_margins_);
      return pages_.back();
    }

    /// Add a page with specific size
    Page &add_page(PageSize size, Margins margins = {})
    {
      pages_.emplace_back(size, margins);
      return pages_.back();
    }

    /// Access existing page by index
    Page &page(std::size_t index) { return pages_.at(index); }
    [[nodiscard]] std::size_t page_count() const noexcept { return pages_.size(); }

    Document &set_title(std::string_view v)
    {
      meta_.title = v;
      return *this;
    }
    Document &set_author(std::string_view v)
    {
      meta_.author = v;
      return *this;
    }
    Document &set_subject(std::string_view v)
    {
      meta_.subject = v;
      return *this;
    }
    Document &set_keywords(std::string_view v)
    {
      meta_.keywords = v;
      return *this;
    }
    Document &set_creator(std::string_view v)
    {
      meta_.creator = v;
      return *this;
    }

    /// Serialize the document to a PDF byte string
    [[nodiscard]] std::string to_string() const
    {
      std::string pdf;
      pdf.reserve(65536);
      std::vector<std::size_t> offsets; // xref offsets

      pdf += "%PDF-1.4\n";
      pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment hint

      int obj_id = 1;
      // obj 1 = catalog, obj 2 = pages dict, obj 3..N = page content
      // We'll emit objects sequentially and collect offsets.

      // Collect all images across all pages globally
      struct GlobalImage
      {
        const Image *img;
        int obj_id;
      };
      std::vector<GlobalImage> global_images;
      for (const auto &pg : pages_)
      {
        for (const Image *img : pg.images())
        {
          // Check if already added (same pointer)
          bool found = false;
          for (auto &gi : global_images)
            if (gi.img == img)
            {
              found = true;
              break;
            }
          if (!found)
            global_images.push_back({img, 0}); // obj_id assigned below
        }
      }

      // Assign obj IDs:
      // 1 = catalog
      // 2 = pages
      // 3..2+N = page objects
      // 3+N..  = page streams
      // then font objects
      // then image XObjects

      const int N = static_cast<int>(pages_.size());
      const int page_obj_start = 3;
      const int stream_obj_start = page_obj_start + N;
      int next_obj = stream_obj_start + N;

      // Font objects: one per unique font name used globally
      std::map<Font, int> font_obj_ids;
      for (const auto &pg : pages_)
        for (Font f : pg.fonts())
          if (font_obj_ids.find(f) == font_obj_ids.end())
            font_obj_ids[f] = next_obj++;

      // Image objects
      for (auto &gi : global_images)
        gi.obj_id = next_obj++;

      // Info object
      const int info_obj = next_obj++;
      // Total objects
      const int total_objs = next_obj;

      offsets.resize(static_cast<std::size_t>(total_objs + 1), 0);

      offsets[1] = pdf.size();
      pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

      offsets[2] = pdf.size();
      pdf += "2 0 obj\n<< /Type /Pages /Kids [";
      for (int i = 0; i < N; ++i)
        pdf += std::to_string(page_obj_start + i) + " 0 R ";
      pdf += "] /Count " + std::to_string(N) + " >>\nendobj\n";

      for (int i = 0; i < N; ++i)
      {
        const Page &pg = pages_[static_cast<std::size_t>(i)];
        int page_obj = page_obj_start + i;
        int stream_obj = stream_obj_start + i;
        offsets[static_cast<std::size_t>(page_obj)] = pdf.size();

        pdf += std::to_string(page_obj) + " 0 obj\n";
        pdf += "<< /Type /Page /Parent 2 0 R\n";
        pdf += "   /MediaBox [0 0 " +
               detail::f2s(pg.width()) + " " + detail::f2s(pg.height()) + "]\n";
        pdf += "   /Contents " + std::to_string(stream_obj) + " 0 R\n";

        // Resources
        pdf += "   /Resources <<\n";
        // Fonts
        if (!pg.fonts().empty())
        {
          pdf += "     /Font <<\n";
          for (Font f : pg.fonts())
          {
            pdf += "       /F" + std::to_string(pg.font_index(f)) +
                   " " + std::to_string(font_obj_ids[f]) + " 0 R\n";
          }
          pdf += "     >>\n";
        }
        // XObjects (images)
        if (!pg.images().empty())
        {
          pdf += "     /XObject <<\n";
          int local_idx = 1;
          for (const Image *img : pg.images())
          {
            int gobj = 0;
            for (auto &gi : global_images)
              if (gi.img == img)
              {
                gobj = gi.obj_id;
                break;
              }
            pdf += "       /Im" + std::to_string(local_idx++) +
                   " " + std::to_string(gobj) + " 0 R\n";
          }
          pdf += "     >>\n";
        }
        pdf += "   >>\n";
        pdf += ">>\nendobj\n";
      }

      for (int i = 0; i < N; ++i)
      {
        const Page &pg = pages_[static_cast<std::size_t>(i)];
        int stream_obj = stream_obj_start + i;
        offsets[static_cast<std::size_t>(stream_obj)] = pdf.size();

        const std::string &content = pg.stream();
        pdf += std::to_string(stream_obj) + " 0 obj\n";
        pdf += "<< /Length " + std::to_string(content.size()) + " >>\n";
        pdf += "stream\n";
        pdf += content;
        pdf += "\nendstream\nendobj\n";
      }

      for (auto &[f, fobj] : font_obj_ids)
      {
        offsets[static_cast<std::size_t>(fobj)] = pdf.size();
        pdf += std::to_string(fobj) + " 0 obj\n";
        pdf += "<< /Type /Font /Subtype /Type1\n";
        pdf += "   /BaseFont /" + std::string(detail::font_name(f)) + "\n";
        pdf += "   /Encoding /WinAnsiEncoding\n";
        pdf += ">>\nendobj\n";
      }

      for (auto &gi : global_images)
      {
        offsets[static_cast<std::size_t>(gi.obj_id)] = pdf.size();
        const Image &img = *gi.img;
        std::string cs = (img.components == 1) ? "DeviceGray" : (img.components == 4) ? "DeviceCMYK"
                                                                                      : "DeviceRGB";
        pdf += std::to_string(gi.obj_id) + " 0 obj\n";
        pdf += "<< /Type /XObject /Subtype /Image\n";
        pdf += "   /Width " + std::to_string(img.width) + "\n";
        pdf += "   /Height " + std::to_string(img.height) + "\n";
        pdf += "   /ColorSpace /" + cs + "\n";
        pdf += "   /BitsPerComponent 8\n";
        pdf += "   /Filter /DCTDecode\n";
        pdf += "   /Length " + std::to_string(img.data.size()) + "\n";
        pdf += ">>\nstream\n";
        pdf.append(reinterpret_cast<const char *>(img.data.data()), img.data.size());
        pdf += "\nendstream\nendobj\n";
      }

      offsets[static_cast<std::size_t>(info_obj)] = pdf.size();
      pdf += std::to_string(info_obj) + " 0 obj\n<<\n";
      if (!meta_.title.empty())
        pdf += "  /Title (" + detail::pdf_escape(meta_.title) + ")\n";
      if (!meta_.author.empty())
        pdf += "  /Author (" + detail::pdf_escape(meta_.author) + ")\n";
      if (!meta_.subject.empty())
        pdf += "  /Subject (" + detail::pdf_escape(meta_.subject) + ")\n";
      if (!meta_.creator.empty())
        pdf += "  /Creator (" + detail::pdf_escape(meta_.creator) + ")\n";
      if (!meta_.keywords.empty())
        pdf += "  /Keywords (" + detail::pdf_escape(meta_.keywords) + ")\n";
      pdf += ">>\nendobj\n";

      std::size_t xref_offset = pdf.size();
      pdf += "xref\n";
      pdf += "0 " + std::to_string(total_objs) + "\n";
      pdf += "0000000000 65535 f \n";
      for (int i = 1; i < total_objs; ++i)
      {
        std::ostringstream oss;
        oss << std::setw(10) << std::setfill('0') << offsets[static_cast<std::size_t>(i)]
            << " 00000 n \n";
        pdf += oss.str();
      }

      pdf += "trailer\n";
      pdf += "<< /Size " + std::to_string(total_objs) +
             " /Root 1 0 R /Info " + std::to_string(info_obj) + " 0 R >>\n";
      pdf += "startxref\n";
      pdf += std::to_string(xref_offset) + "\n";
      pdf += "%%EOF\n";

      return pdf;
    }

    /// Save document to a file
    void save(const std::string &path) const
    {
      std::ofstream f(path, std::ios::binary);
      if (!f)
        throw std::runtime_error("Cannot open file for writing: " + path);
      auto data = to_string();
      f.write(data.data(), static_cast<std::streamsize>(data.size()));
    }

  private:
    PageSize default_size_;
    Margins default_margins_;
    std::vector<Page> pages_;
    Metadata meta_;
  };

  /// Generate a simple single-page text document and save it
  inline void make_text_pdf(
      const std::string &path,
      std::string_view content,
      std::string_view title = "",
      Font font = Font::Helvetica,
      float font_size = 12.f)
  {
    Document doc(PageSize::A4());
    if (!title.empty())
      doc.set_title(title);
    auto &pg = doc.add_page();
    float x = pg.x_left();
    float y = pg.y_top();
    if (!title.empty())
    {
      y = pg.heading(x, y, title, 1);
      y -= 10.f;
    }
    pg.paragraph(x, y, pg.content_width(), content, font, font_size);
    doc.save(path);
  }

  /// Quick table PDF — headers + rows of strings
  inline void make_table_pdf(const std::string &path,
                             std::string_view title,
                             const std::vector<std::string> &headers,
                             const std::vector<std::vector<std::string>> &rows)
  {
    Document doc(PageSize::A4());
    if (!title.empty())
      doc.set_title(title);
    auto &pg = doc.add_page();

    float x = pg.x_left();
    float y = pg.y_top();

    if (!title.empty())
    {
      y = pg.heading(x, y, title, 1);
      y -= 16.f;
    }

    // Auto column widths
    const float total_w = pg.content_width();
    const std::size_t nc = headers.size();
    const float col_w = nc > 0 ? total_w / static_cast<float>(nc) : total_w;
    std::vector<float> col_widths(nc, col_w);

    // Build table rows
    std::vector<TableRow> table_rows;

    // Header row
    TableRow hdr;
    hdr.is_header = true;
    for (const auto &h : headers)
      hdr.cells.push_back({h, Align::Left});
    table_rows.push_back(hdr);

    // Data rows
    for (const auto &row : rows)
    {
      TableRow tr;
      for (std::size_t c = 0; c < nc; ++c)
        tr.cells.push_back({c < row.size() ? row[c] : "", Align::Left});
      table_rows.push_back(tr);
    }

    pg.draw_table(x, y, col_widths, table_rows);
    doc.save(path);
  }

} // namespace pdf
