/**
 *
 *  @file ImageRegistry.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_IMAGEREGISTRY_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_IMAGEREGISTRY_HPP_INCLUDED

#include <rix/pdf/document/Image.hpp>

#include <cstddef>
#include <map>
#include <vector>

namespace rixlib::pdf::writer
{
  /**
   * @brief Registry for images used by a PDF document.
   *
   * ImageRegistry stores unique image pointers and assigns one PDF object id
   * per image. Image ownership stays outside the registry.
   */
  class ImageRegistry
  {
  public:
    /**
     * @brief Construct an empty image registry.
     */
    ImageRegistry() = default;

    /**
     * @brief Register an image if it is not already registered.
     *
     * Null pointers and invalid images are ignored.
     *
     * @param image Image pointer to register.
     */
    void add(const Image *image);

    /**
     * @brief Register all images from a range.
     *
     * @param images Image pointers to register.
     */
    void add_all(const std::vector<const Image *> &images);

    /**
     * @brief Return true when the image is already registered.
     *
     * @param image Image pointer to check.
     * @return true if the image is registered.
     */
    [[nodiscard]] bool contains(const Image *image) const noexcept;

    /**
     * @brief Return the number of registered images.
     *
     * @return Image count.
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief Return true when no images are registered.
     *
     * @return true if the registry is empty.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Assign PDF object ids to registered images.
     *
     * Object ids are assigned in the order images were registered.
     *
     * @param first_object_id First available PDF object id.
     * @return Next available PDF object id after assignment.
     */
    int assign_object_ids(int first_object_id);

    /**
     * @brief Return the PDF object id for an image.
     *
     * @param image Image pointer to query.
     * @return Object id, or 0 if not assigned.
     */
    [[nodiscard]] int object_id(const Image *image) const noexcept;

    /**
     * @brief Return the page-local image resource index.
     *
     * Page-local image indexes are one-based and depend on the page image list.
     *
     * @param page_images Images used by a page.
     * @param image Image pointer to query.
     * @return One-based index, or 1 as safe fallback.
     */
    [[nodiscard]] static int page_image_index(
        const std::vector<const Image *> &page_images,
        const Image *image) noexcept;

    /**
     * @brief Return all registered images in stable order.
     *
     * @return Registered image pointers.
     */
    [[nodiscard]] const std::vector<const Image *> &images() const noexcept;

  private:
    std::vector<const Image *> images_;
    std::map<const Image *, int> object_ids_;
  };
} // namespace rixlib::pdf::writer

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_WRITER_IMAGEREGISTRY_HPP_INCLUDED
