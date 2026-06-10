/**
 *
 *  @file Metadata.cpp
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

#include <utility>

namespace rixlib::pdf
{
  Metadata::Metadata()
      : creator_("rix/pdf")
  {
  }

  const std::string &Metadata::title() const noexcept
  {
    return title_;
  }

  void Metadata::set_title(std::string value)
  {
    title_ = std::move(value);
  }

  const std::string &Metadata::author() const noexcept
  {
    return author_;
  }

  void Metadata::set_author(std::string value)
  {
    author_ = std::move(value);
  }

  const std::string &Metadata::subject() const noexcept
  {
    return subject_;
  }

  void Metadata::set_subject(std::string value)
  {
    subject_ = std::move(value);
  }

  const std::string &Metadata::creator() const noexcept
  {
    return creator_;
  }

  void Metadata::set_creator(std::string value)
  {
    creator_ = std::move(value);

    if (creator_.empty())
    {
      creator_ = "rix/pdf";
    }
  }

  const std::string &Metadata::keywords() const noexcept
  {
    return keywords_;
  }

  void Metadata::set_keywords(std::string value)
  {
    keywords_ = std::move(value);
  }

  void Metadata::clear()
  {
    title_.clear();
    author_.clear();
    subject_.clear();
    creator_ = "rix/pdf";
    keywords_.clear();
  }

  bool Metadata::empty() const noexcept
  {
    return title_.empty() &&
           author_.empty() &&
           subject_.empty() &&
           keywords_.empty();
  }
} // namespace rixlib::pdf
