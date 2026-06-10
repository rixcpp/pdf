cmake_minimum_required(VERSION 3.20)

project(rix_pdf VERSION 0.1.0 LANGUAGES CXX)

add_library(rix_pdf
  src/core/Color.cpp
  src/core/Error.cpp
  src/core/Font.cpp
  src/core/Margins.cpp
  src/core/PageSize.cpp

  src/document/Document.cpp
  src/document/Image.cpp
  src/document/Metadata.cpp
  src/document/Page.cpp
  src/document/Table.cpp

  src/writer/Escape.cpp
  src/writer/FloatFormat.cpp
  src/writer/FontMetrics.cpp
  src/writer/FontRegistry.cpp
  src/writer/ImageRegistry.cpp
  src/writer/ObjectWriter.cpp
  src/writer/PdfWriter.cpp
  src/writer/XrefTable.cpp

  src/PdfModule.cpp
  src/Version.cpp
)

add_library(rix::pdf ALIAS rix_pdf)

target_compile_features(rix_pdf PUBLIC cxx_std_20)

target_include_directories(
  rix_pdf
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

option(RIX_PDF_BUILD_EXAMPLES "Build rix/pdf examples" ON)
option(RIX_PDF_BUILD_TESTS "Build rix/pdf tests" ON)

if(RIX_PDF_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(RIX_PDF_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
