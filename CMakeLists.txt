cmake_minimum_required(VERSION 3.20)

project(rix_pdf VERSION 0.1.0 LANGUAGES CXX)

add_library(rix_pdf INTERFACE)
add_library(rix::pdf ALIAS rix_pdf)

target_compile_features(rix_pdf INTERFACE cxx_std_20)

target_include_directories(
  rix_pdf
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

option(RIX_PDF_BUILD_EXAMPLES "Build rix/pdf examples" ON)
option(RIX_PDF_BUILD_TESTS "Build rix/pdf tests" ON)

if(RIX_PDF_BUILD_EXAMPLES)
  add_executable(rix_pdf_basic examples/basic.cpp)
  target_link_libraries(rix_pdf_basic PRIVATE rix::pdf)

  add_executable(rix_pdf_text examples/text.cpp)
  target_link_libraries(rix_pdf_text PRIVATE rix::pdf)

  add_executable(rix_pdf_table examples/table.cpp)
  target_link_libraries(rix_pdf_table PRIVATE rix::pdf)

  add_executable(rix_pdf_drawing examples/drawing.cpp)
  target_link_libraries(rix_pdf_drawing PRIVATE rix::pdf)
endif()

if(RIX_PDF_BUILD_TESTS)
  enable_testing()

  add_executable(rix_pdf_tests tests/pdf_tests.cpp)
  target_link_libraries(rix_pdf_tests PRIVATE rix::pdf)

  add_test(NAME rix_pdf_tests COMMAND rix_pdf_tests)
endif()
