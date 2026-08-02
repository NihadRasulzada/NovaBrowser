#include "url/UrlLexer.hpp"
#include <gtest/gtest.h>

using namespace Browser::Url;

namespace {

	// Helper: assert the full token sequence (type + value, in order) matches expected.
	void ExpectTokens(const std::vector<UrlToken>& actual,
		const std::vector<UrlToken>& expected) {
		ASSERT_EQ(actual.size(), expected.size())
			<< "Token count mismatch. Got " << actual.size()
			<< " tokens, expected " << expected.size() << ".";
		for (std::size_t i = 0; i < expected.size(); ++i) {
			EXPECT_EQ(static_cast<int>(actual[i].Type), static_cast<int>(expected[i].Type))
				<< "Type mismatch at index " << i;
			EXPECT_EQ(actual[i].Value, expected[i].Value)
				<< "Value mismatch at index " << i
				<< " (type=" << static_cast<int>(actual[i].Type) << ")";
		}
	}

	std::vector<UrlToken> LexUrl(const std::string& url) {
		UrlLexer lexer(url);
		return lexer.Tokenize();
	}

} // namespace

// ---------------------------------------------------------------------
// 1. http://example.com
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpNoPath) {
	auto tokens = LexUrl("http://example.com");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "http" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 2. https://example.com
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsNoPath) {
	auto tokens = LexUrl("https://example.com");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 3. https://www.example.com
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsWithWwwSubdomain) {
	auto tokens = LexUrl("https://www.example.com");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "www.example.com" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 4. http://example.com/  (root path, trailing slash)
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpRootPathOnly) {
	auto tokens = LexUrl("http://example.com/");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "http" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 5. https://example.org/path
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsSingleSegmentPath) {
	auto tokens = LexUrl("https://example.org/path");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.org" },
		{ UrlTokenType::Path,   "/path" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 6. https://example.net/path/to/resource
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsMultiSegmentPath) {
	auto tokens = LexUrl("https://example.net/path/to/resource");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.net" },
		{ UrlTokenType::Path,   "/path/to/resource" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 7. https://example.com/path?query=value
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithQuery) {
	auto tokens = LexUrl("https://example.com/path?query=value");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/path" },
		{ UrlTokenType::Query,  "query=value" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 8. https://example.com/path#section
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithFragment) {
	auto tokens = LexUrl("https://example.com/path#section");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme,   "https" },
		{ UrlTokenType::Host,     "example.com" },
		{ UrlTokenType::Path,     "/path" },
		{ UrlTokenType::Fragment, "section" },
		{ UrlTokenType::End,      "" },
		});
}

// ---------------------------------------------------------------------
// 9. https://example.com/path?query=value#section
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithQueryAndFragment) {
	auto tokens = LexUrl("https://example.com/path?query=value#section");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme,   "https" },
		{ UrlTokenType::Host,     "example.com" },
		{ UrlTokenType::Path,     "/path" },
		{ UrlTokenType::Query,    "query=value" },
		{ UrlTokenType::Fragment, "section" },
		{ UrlTokenType::End,      "" },
		});
}

// ---------------------------------------------------------------------
// 10. https://example.com/index.html
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithFileExtension) {
	auto tokens = LexUrl("https://example.com/index.html");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/index.html" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 11. http://example.com/a/b/c/d/e
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpDeeplyNestedPath) {
	auto tokens = LexUrl("http://example.com/a/b/c/d/e");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "http" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/a/b/c/d/e" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 12. https://example.com/path/  (trailing slash on multi-char path)
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithTrailingSlash) {
	auto tokens = LexUrl("https://example.com/path/");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/path/" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 13. https://example.com/PATH/CaseSensitive
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathIsCaseSensitive) {
	auto tokens = LexUrl("https://example.com/PATH/CaseSensitive");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/PATH/CaseSensitive" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 14. https://example.com/path.with.dots
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithDots) {
	auto tokens = LexUrl("https://example.com/path.with.dots");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/path.with.dots" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// 15. https://example.com/path-with-dashes_and_underscores
// ---------------------------------------------------------------------
TEST(UrlLexerTest, HttpsPathWithDashesAndUnderscores) {
	auto tokens = LexUrl("https://example.com/path-with-dashes_and_underscores");
	ExpectTokens(tokens, {
		{ UrlTokenType::Scheme, "https" },
		{ UrlTokenType::Host,   "example.com" },
		{ UrlTokenType::Path,   "/path-with-dashes_and_underscores" },
		{ UrlTokenType::End,    "" },
		});
}

// ---------------------------------------------------------------------
// Extra sanity checks — token count only, useful as quick smoke tests
// that mirror how you'll likely eyeball output while iterating.
// ---------------------------------------------------------------------
TEST(UrlLexerTest, EndTokenIsAlwaysLast) {
	for (const std::string url : {
		"http://example.com",
			"https://example.com/path?query=value#section",
			"https://example.com/path.with.dots",
	}) {
		auto tokens = LexUrl(url);
		ASSERT_FALSE(tokens.empty());
		EXPECT_EQ(tokens.back().Type, UrlTokenType::End);
		EXPECT_EQ(tokens.back().Value, "");
	}
}

TEST(UrlLexerTest, SchemeTokenIsAlwaysFirst) {
	for (const std::string url : {
		"http://example.com",
			"https://www.example.com",
			"https://example.com/path/to/resource",
	}) {
		auto tokens = LexUrl(url);
		ASSERT_FALSE(tokens.empty());
		EXPECT_EQ(tokens.front().Type, UrlTokenType::Scheme);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}