
#include <orgmode-parser/title.hpp>
#include <orgmode-parser/title.ipp>
#define BOOST_TEST_MODULE title
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/home/qi/parse.hpp>

const char test1[] = 
  "*\n" // fail
;

const char test2[] = 
  "* title" // success
;

const char test3[] = 
  "*title" // fail
;

const char test4[] = 
  "* title\n" // success
;

const char test5[] = 
  "* title :tag:\n" // success
;

const char test6[] = 
  "* title\n" // success
  "qwe"
;

const char test7[] = 
  "*\ntitle\n" // fail
;

const char test8[] = 
  "*  title\n" // success
;

const char test9[] = 
  "*\ttitle\n" // success
;

BOOST_AUTO_TEST_CASE( title )
{
  orgmode_parser::title<const char*, std::string> grammar;
  namespace qi = boost::spirit::qi;

  std::string result;
  const char* iterator = test1;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, result));
  BOOST_CHECK(result.empty());

  iterator = test2;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 5);
  BOOST_CHECK_EQUAL(result, "title");
  result.clear();

  iterator = test3;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, result));
  BOOST_CHECK(result.empty());

  iterator = test4;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 5);
  BOOST_CHECK_EQUAL(result, "title");
  result.clear();

  iterator = test5;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 11);
  BOOST_CHECK_EQUAL(result, "title :tag:");
  result.clear();

  iterator = test6;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 5);
  BOOST_CHECK_EQUAL(result, "title");
  result.clear();

  iterator = test7;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, result));
  BOOST_CHECK(result.empty());

  iterator = test8;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 5);
  BOOST_CHECK_EQUAL(result, "title");
  result.clear();

  iterator = test9;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, result));
  BOOST_CHECK_EQUAL(result.size(), 5);
  BOOST_CHECK_EQUAL(result, "title");
  result.clear();
}
