/**
 *
 *  @file Document.cpp
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

#include <utility>

namespace rixlib::pdf
{
  Document::Document()
      : Document(PageSize::A4(), Margins{})
  {
  }

  Document::Document(PageSize default_size, Margins default_margins)
      : default_size_(default_size),
        default_margins_(default_margins)
  {
  }

  const PageSize &Document::default_page_size() const noexcept
  {
    return default_size_;
  }

  Document &Document::set_default_page_size(PageSize value) noexcept
  {
    default_size_ = value;
    return *this;
  }

  const Margins &Document::default_margins() const noexcept
  {
    return default_margins_;
  }

  Document &Document::set_default_margins(Margins value) noexcept
  {
    default_margins_ = value;
    return *this;
  }

  Page &Document::add_page()
  {
    pages_.emplace_back(default_size_, default_margins_);
    return pages_.back();
  }

  Page &Document::add_page(PageSize size)
  {
    pages_.emplace_back(size, default_margins_);
    return pages_.back();
  }

  Page &Document::add_page(PageSize size, Margins margins)
  {
    pages_.emplace_back(size, margins);
    return pages_.back();
  }

  Page &Document::page(std::size_t index)
  {
    return pages_.at(index);
  }

  const Page &Document::page(std::size_t index) const
  {
    return pages_.at(index);
  }

  const std::vector<Page> &Document::pages() const noexcept
  {
    return pages_;
  }

  std::vector<Page> &Document::pages() noexcept
  {
    return pages_;
  }

  std::size_t Document::page_count() const noexcept
  {
    return pages_.size();
  }

  bool Document::empty() const noexcept
  {
    return pages_.empty();
  }

  void Document::clear_pages()
  {
    pages_.clear();
  }

  const Metadata &Document::metadata() const noexcept
  {
    return metadata_;
  }

  Metadata &Document::metadata() noexcept
  {
    return metadata_;
  }

  Document &Document::set_metadata(Metadata value) noexcept
  {
    metadata_ = std::move(value);
    return *this;
  }

  Document &Document::set_title(std::string value)
  {
    metadata_.set_title(std::move(value));
    return *this;
  }

  Document &Document::set_author(std::string value)
  {
    metadata_.set_author(std::move(value));
    return *this;
  }

  Document &Document::set_subject(std::string value)
  {
    metadata_.set_subject(std::move(value));
    return *this;
  }

  Document &Document::set_creator(std::string value)
  {
    metadata_.set_creator(std::move(value));
    return *this;
  }

  Document &Document::set_keywords(std::string value)
  {
    metadata_.set_keywords(std::move(value));
    return *this;
  }
} // namespace rixlib::pdf
