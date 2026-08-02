add_executable(url_tests
    UrlLexerTests.cpp
)

target_link_libraries(url_tests
    PRIVATE
        browser_url
        gtest_main
)

include(GoogleTest)

gtest_discover_tests(url_tests)