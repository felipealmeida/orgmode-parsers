
#include <orgmode-parser/datetime.hpp>
#include <orgmode-parser/datetime.ipp>
#define BOOST_TEST_MODULE datetime
#include <boost/test/included/unit_test.hpp>

#include <boost/spirit/home/qi/parse.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>

const char test1[] = 
  "<>" // fail
;

const char test2[] = 
  "<2014>" // fail
;

const char test3[] = 
  "<2014-02>" // fail
;

const char test4[] = 
  "<<>>" // fail
;

const char test5[] = 
  "<2014-02-01>" // fail
;

const char test6[] = 
  "<2014-02-01 >" // fail
;

const char test7[] = 
  "<2014-02-01 Wed>" // success
;

const char test8[] = 
  "<2014-02-01 ++1m>" // fail
;

const char test9[] = 
  "<2014-02-01 Wed ++1m>" // success
;

const char test10[] = 
  "<2014-02-01 Wed ++1m -4d>" // success
;

const char test11[] = 
  "<2014-02-01 Wed 02:00 ++1m -4d>" // success
;

const char test12[] = 
  "<2014-02-01 Wed 02:00>" // success
;

const char test13[] = 
  "<2014-02-01 Wed 02>" // fail
;

const char test14[] = 
  "<2014-02-01 W 02:00>" // fail
;

const char test15[] = 
  "<2014-02-01 We 02:00>" // fail
;

const char test16[] = 
  "<2014-02-01 Mow 02:00>" // fail
;

// const char test17[] = 
//   "[2014-02-01 Mon 02:00]" // success
// ;

BOOST_AUTO_TEST_CASE( datetime )
{
  typedef boost::tuple
    <unsigned int&, unsigned int&, unsigned int&
     , unsigned int&
     , boost::optional<boost::tuple<unsigned int, unsigned int> >&
     , boost::optional<boost::tuple<bool, unsigned int, char> >&
     , boost::optional<boost::tuple<unsigned int, char> >&
    >
    attribute;
  orgmode_parser::datetime<const char*, attribute> grammar;
  namespace qi = boost::spirit::qi;

  unsigned int year;
  unsigned int month;
  unsigned int day;
  unsigned int dayofweek;
  boost::optional<boost::tuple<unsigned int, unsigned int> > time;
  boost::optional<boost::tuple<bool, unsigned int, char> > repeater;
  boost::optional<boost::tuple<unsigned int, char> > lead_time;
  attribute tuple(year, month, day, dayofweek, time, repeater, lead_time);

  const char* iterator = test1;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test2;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test3;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test4;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test5;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test6;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test6;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test7;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(year, 2014);
  BOOST_CHECK_EQUAL(month, 2u);
  BOOST_CHECK_EQUAL(day, 1u);
  BOOST_CHECK_EQUAL(dayofweek, 3u);
  BOOST_CHECK(!time);
  BOOST_CHECK(!repeater);
  BOOST_CHECK(!lead_time);

  time = boost::none; repeater = boost::none; lead_time = boost::none;

  /*const char**/ iterator = test8;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test9;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(year, 2014);
  BOOST_CHECK_EQUAL(month, 2u);
  BOOST_CHECK_EQUAL(day, 1u);
  BOOST_CHECK_EQUAL(dayofweek, 3u);
  BOOST_CHECK(!time);
  BOOST_REQUIRE(repeater);
  BOOST_CHECK(repeater->get<0u>());
  BOOST_CHECK_EQUAL(repeater->get<1u>(), 1u);
  BOOST_CHECK_EQUAL(repeater->get<2u>(), 'm');
  BOOST_CHECK(!lead_time);

  time = boost::none; repeater = boost::none; lead_time = boost::none;

  /*const char**/ iterator = test10;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(year, 2014);
  BOOST_CHECK_EQUAL(month, 2u);
  BOOST_CHECK_EQUAL(day, 1u);
  BOOST_CHECK_EQUAL(dayofweek, 3u);
  BOOST_CHECK(!time);
  BOOST_REQUIRE(repeater);
  BOOST_CHECK(repeater->get<0u>());
  BOOST_CHECK_EQUAL(repeater->get<1u>(), 1u);
  BOOST_CHECK_EQUAL(repeater->get<2u>(), 'm');
  BOOST_REQUIRE(lead_time);
  BOOST_CHECK_EQUAL(lead_time->get<0u>(), 4u);
  BOOST_CHECK_EQUAL(lead_time->get<1u>(), 'd');

  time = boost::none; repeater = boost::none; lead_time = boost::none;

  /*const char**/ iterator = test11;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(year, 2014);
  BOOST_CHECK_EQUAL(month, 2u);
  BOOST_CHECK_EQUAL(day, 1u);
  BOOST_CHECK_EQUAL(dayofweek, 3u);
  BOOST_REQUIRE(time);
  BOOST_CHECK_EQUAL(time->get<0u>(), 2u);
  BOOST_CHECK_EQUAL(time->get<1u>(), 0u);
  BOOST_REQUIRE(repeater);
  BOOST_CHECK(repeater->get<0u>());
  BOOST_CHECK_EQUAL(repeater->get<1u>(), 1u);
  BOOST_CHECK_EQUAL(repeater->get<2u>(), 'm');
  BOOST_REQUIRE(lead_time);
  BOOST_CHECK_EQUAL(lead_time->get<0u>(), 4u);
  BOOST_CHECK_EQUAL(lead_time->get<1u>(), 'd');

  time = boost::none; repeater = boost::none; lead_time = boost::none;

  /*const char**/ iterator = test12;
  BOOST_CHECK(qi::parse(iterator, iterator + std::strlen(iterator)
                        , grammar, tuple));
  BOOST_CHECK_EQUAL(year, 2014);
  BOOST_CHECK_EQUAL(month, 2u);
  BOOST_CHECK_EQUAL(day, 1u);
  BOOST_CHECK_EQUAL(dayofweek, 3u);
  BOOST_REQUIRE(time);
  BOOST_CHECK_EQUAL(time->get<0u>(), 2u);
  BOOST_CHECK_EQUAL(time->get<1u>(), 0u);
  BOOST_CHECK(!repeater);
  BOOST_CHECK(!lead_time);

  time = boost::none; repeater = boost::none; lead_time = boost::none;

  /*const char**/ iterator = test13;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test14;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test15;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));

  /*const char**/ iterator = test16;
  BOOST_CHECK(!qi::parse(iterator, iterator + std::strlen(iterator)
                         , grammar, tuple));
}
