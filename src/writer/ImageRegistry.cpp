/**
 *
 *  @file ImageRegistry.cpp
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

#include <rix/pdf/writer/ImageRegistry.hpp>

#include <algorithm>

namespace rixlib::pdf::writer
{
  void ImageRegistry::add(const Image *image)
  {
    if (image == nullptr || !image->valid())
    {
      return;
    }

    if (!contains(image))
    {
      images_.push_back(image);
    }
  }

  void ImageRegistry::add_all(const std::vector<const Image *> &images)
  {
    for (const auto *image : images)
    {
      add(image);
    }
  }

  bool ImageRegistry::contains(const Image *image) const noexcept
  {
    return std::find(images_.begin(), images_.end(), image) != images_.end();
  }

  std::size_t ImageRegistry::size() const noexcept
  {
    return images_.size();
  }

  bool ImageRegistry::empty() const noexcept
  {
    return images_.empty();
  }

  int ImageRegistry::assign_object_ids(int first_object_id)
  {
    object_ids_.clear();

    int next_object_id = first_object_id;

    for (const auto *image : images_)
    {
      object_ids_[image] = next_object_id;
      ++next_object_id;
    }

    return next_object_id;
  }

  int ImageRegistry::object_id(const Image *image) const noexcept
  {
    const auto found = object_ids_.find(image);

    if (found == object_ids_.end())
    {
      return 0;
    }

    return found->second;
  }

  int ImageRegistry::page_image_index(
      const std::vector<const Image *> &page_images,
      const Image *image) noexcept
  {
    for (int index = 0; index < static_cast<int>(page_images.size()); ++index)
    {
      if (page_images[static_cast<std::size_t>(index)] == image)
      {
        return index + 1;
      }
    }

    return 1;
  }

  const std::vector<const Image *> &ImageRegistry::images() const noexcept
  {
    return images_;
  }
} // namespace rixlib::pdf::writer
