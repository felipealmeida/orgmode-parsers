
#include <orgmode-parser/preamble.hpp>
#include <orgmode-parser/preamble.ipp>
#include <orgmode-parser/eol.ipp>
#define BOOST_TEST_MODULE preamble
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/home/qi/parse.hpp>

const char test1[] = 
  ""
;

const char test2[] = 
  "*"
;

const char test3[] = 
  "as*"
;

const char test4[] = 
  "as\n"
  "*"
;

const char test5[] = 
  "as\n"
;

BOOST_AUTO_TEST_CASE( preamble )
{
  orgmode_parser::preamble<const char*, std::string> preamble_grammar;
  namespace qi = boost::spirit::qi;

  std::string result;
  const char* iterator = test1;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , preamble_grammar, result));
  BOOST_CHECK(result.empty());

  iterator = test2;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , preamble_grammar, result));
  BOOST_CHECK(result.empty());

  iterator = test3;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , preamble_grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 3);
  BOOST_CHECK_EQUAL(result, "as*");
  result.clear();

  iterator = test4;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , preamble_grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 3);
  BOOST_CHECK_EQUAL(result, "as\n");
  result.clear();

  iterator = test5;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , preamble_grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 3);
  BOOST_CHECK_EQUAL(result, "as\n");
  result.clear();
}
