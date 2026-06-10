set(RIX_PDF_TESTS
  ColorTests
  DocumentTests
  EscapeTests
  FloatFormatTests
  FontMetricsTests
  ImageTests
  MetadataTests
  PageSizeTests
  PageTests
  PdfCoreTests
  PdfErrorTests
  PdfModuleTests
  PdfWriterTests
)

foreach(test_name IN LISTS RIX_PDF_TESTS)
  add_executable(${test_name} ${test_name}.cpp)
  target_link_libraries(${test_name} PRIVATE rix::pdf)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
