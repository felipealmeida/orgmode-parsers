
#include <orgmode-parser/item.hpp>
#include <orgmode-parser/item.ipp>
#include <orgmode-parser/title.ipp>
#include <orgmode-parser/eol.ipp>
#define BOOST_TEST_MODULE item
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/home/qi/parse.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>

const char test1[] = 
  "* title" // success
;

const char test2[] = 
  "* title\n" // success
;

const char test3[] = 
  "* title\n" // success
  "body"
;

const char test4[] = 
  "* title\n" // success
  "body\n"
;

const char test5[] = 
  "* title\n" // success
  "body*\n"
;

const char test6[] = 
  "* title\n" // success
  "*body\n"
;

const char test7[] = 
  "* title\n" // success
  "* title2\n"
;

BOOST_AUTO_TEST_CASE( item )
{
  orgmode_parser::item<const char*
                           , boost::tuple<std::string&, std::string&>
                           > grammar;
  namespace qi = boost::spirit::qi;

  std::string title, body;
  boost::tuple<std::string&, std::string&> tuple(title, body);

  const char* iterator = test1;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK(body.empty());

  title.clear(); body.clear();

  /*const char**/ iterator = test2;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK(body.empty());

  title.clear(); body.clear();

  /*const char**/ iterator = test3;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK_EQUAL(body, "body");

  title.clear(); body.clear();

  /*const char**/ iterator = test4;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK_EQUAL(body, "body\n");

  title.clear(); body.clear();

  /*const char**/ iterator = test5;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK_EQUAL(body, "body*\n");

  title.clear(); body.clear();

  /*const char**/ iterator = test6;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK_EQUAL(body, "*body\n");

  title.clear(); body.clear();

  /*const char**/ iterator = test7;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(title, "title");
  BOOST_CHECK(body.empty());
}
