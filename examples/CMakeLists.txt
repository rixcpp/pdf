add_executable(rix_pdf_01_basic 01_basic.cpp)
target_link_libraries(rix_pdf_01_basic PRIVATE rix::pdf)

add_executable(rix_pdf_02_text 02_text.cpp)
target_link_libraries(rix_pdf_02_text PRIVATE rix::pdf)

add_executable(rix_pdf_03_table 03_table.cpp)
target_link_libraries(rix_pdf_03_table PRIVATE rix::pdf)

add_executable(rix_pdf_04_drawing 04_drawing.cpp)
target_link_libraries(rix_pdf_04_drawing PRIVATE rix::pdf)

add_executable(rix_pdf_05_metadata 05_metadata.cpp)
target_link_libraries(rix_pdf_05_metadata PRIVATE rix::pdf)
