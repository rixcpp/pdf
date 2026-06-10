/**
 *
 *  @file Result.hpp
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

#ifndef RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_RESULT_HPP_INCLUDED
#define RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_RESULT_HPP_INCLUDED

#include <rix/pdf/core/Error.hpp>

#include <optional>
#include <utility>

namespace rixlib::pdf
{
  /**
   * @brief Result object returned by PDF operations.
   *
   * PdfResult stores either a value of type T or a PdfError.
   *
   * This type is used for operations that return data, for example:
   *
   * @code
   * PdfResult<Image>
   * PdfResult<std::string>
   * PdfResult<Document>
   * @endcode
   *
   * Normal PDF failures such as invalid input, image parsing errors,
   * file write errors, or serialization errors are represented as explicit
   * errors instead of exceptions.
   *
   * @tparam T Success value type.
   */
  template <typename T>
  class PdfResult
  {
  public:
    /**
     * @brief Success value type.
     */
    using value_type = T;

    /**
     * @brief Error value type.
     */
    using error_type = PdfError;

    /**
     * @brief Create a successful result.
     *
     * @param value Success value.
     * @return PdfResult containing the success value.
     */
    [[nodiscard]] static PdfResult success(T value)
    {
      PdfResult result;
      result.value_ = std::move(value);
      return result;
    }

    /**
     * @brief Create a failed result.
     *
     * @param error PDF error.
     * @return PdfResult containing the error.
     */
    [[nodiscard]] static PdfResult failure(PdfError error)
    {
      PdfResult result;
      result.error_ = std::move(error);
      return result;
    }

    /**
     * @brief Return true when the result contains a value.
     *
     * @return true if the operation succeeded.
     */
    [[nodiscard]] bool ok() const noexcept
    {
      return value_.has_value();
    }

    /**
     * @brief Return true when the result contains an error.
     *
     * @return true if the operation failed.
     */
    [[nodiscard]] bool failed() const noexcept
    {
      return !ok();
    }

    /**
     * @brief Boolean conversion.
     *
     * @return true if the operation succeeded.
     */
    [[nodiscard]] explicit operator bool() const noexcept
    {
      return ok();
    }

    /**
     * @brief Return the success value.
     *
     * The caller must check ok() before calling this function.
     *
     * @return Const reference to the success value.
     */
    [[nodiscard]] const T &value() const
    {
      return *value_;
    }

    /**
     * @brief Return the success value.
     *
     * The caller must check ok() before calling this function.
     *
     * @return Mutable reference to the success value.
     */
    [[nodiscard]] T &value()
    {
      return *value_;
    }

    /**
     * @brief Move the success value out of the result.
     *
     * The caller must check ok() before calling this function.
     *
     * @return Moved success value.
     */
    [[nodiscard]] T move_value()
    {
      return std::move(*value_);
    }

    /**
     * @brief Return the PDF error.
     *
     * When the result is successful, this returns an empty PdfError.
     *
     * @return Const reference to the error.
     */
    [[nodiscard]] const PdfError &error() const noexcept
    {
      return error_;
    }

  private:
    std::optional<T> value_;
    PdfError error_;
  };

  /**
   * @brief Result object for operations that only return success or failure.
   *
   * PdfStatus is used when an operation does not return a value, for example:
   *
   * @code
   * save()
   * validate()
   * write_to_file()
   * @endcode
   */
  class PdfStatus
  {
  public:
    /**
     * @brief Create a successful status.
     *
     * @return Successful PdfStatus.
     */
    [[nodiscard]] static PdfStatus success()
    {
      return PdfStatus{};
    }

    /**
     * @brief Create a failed status.
     *
     * @param error PDF error.
     * @return Failed PdfStatus.
     */
    [[nodiscard]] static PdfStatus failure(PdfError error)
    {
      PdfStatus status;
      status.error_ = std::move(error);
      return status;
    }

    /**
     * @brief Return true when the operation succeeded.
     *
     * @return true if no error is stored.
     */
    [[nodiscard]] bool ok() const noexcept
    {
      return error_.ok();
    }

    /**
     * @brief Return true when the operation failed.
     *
     * @return true if an error is stored.
     */
    [[nodiscard]] bool failed() const noexcept
    {
      return error_.has_error();
    }

    /**
     * @brief Boolean conversion.
     *
     * @return true if the operation succeeded.
     */
    [[nodiscard]] explicit operator bool() const noexcept
    {
      return ok();
    }

    /**
     * @brief Return the PDF error.
     *
     * @return Const reference to the error.
     */
    [[nodiscard]] const PdfError &error() const noexcept
    {
      return error_;
    }

  private:
    PdfError error_;
  };

} // namespace rixlib::pdf

#endif // RIXCPP_PDF_INCLUDE_RIX_PDF_CORE_RESULT_HPP_INCLUDED
