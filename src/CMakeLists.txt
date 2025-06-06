# Create directory for the generated header files:
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/utap")

set(lexer_source "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc")
add_custom_command(
  OUTPUT "${lexer_source}"
  COMMAND ${FLEX_EXECUTABLE} "--outfile=${lexer_source}" -Putap_
          "${CMAKE_CURRENT_SOURCE_DIR}/lexer.l"
  DEPENDS lexer.l)
add_custom_target(lexer_generate DEPENDS "${lexer_source}")

set(parser_source "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")
add_custom_command(
  OUTPUT "${parser_source}" "${CMAKE_CURRENT_BINARY_DIR}/include/parser.hpp"
  COMMAND
    ${BISON_EXECUTABLE} -putap_ -bparser "${CMAKE_CURRENT_SOURCE_DIR}/parser.y"
    "--output=${parser_source}"
    "--defines=${CMAKE_CURRENT_BINARY_DIR}/include/parser.hpp"
  DEPENDS lexer_generate parser.y)
add_custom_target(parser_generate DEPENDS "${parser_source}")

file(GLOB utap_source "*.c" "*.cpp" "*.h")
add_library(UTAP
  AbstractBuilder.cpp
  DocumentBuilder.cpp
  ExpressionBuilder.cpp
  FeatureChecker.cpp
  Library.cpp
  PrettyPrinter.cpp
  StatementBuilder.cpp
  TypeChecker.cpp
  document.cpp
  expression.cpp
  keywords.cpp
  position.cpp
  property.cpp
  statement.cpp
  symbols.cpp
  type.cpp
  typeexception.cpp
  xmlreader.cpp
  xmlwriter.cpp
  ${parser_source})
target_include_directories(UTAP PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(UTAP PRIVATE LibXml2::LibXml2 ${CMAKE_DL_LIBS}
                                   ${LIBXML_WINLIBS})
