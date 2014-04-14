#ifndef ORGMODE_PARSER_DATETIME_HPP
#define ORGMODE_PARSER_DATETIME_HPP

#include <boost/spirit/home/qi/nonterminal.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace fusion = boost::fusion;

template <typename Iterator, typename Attribute>
struct datetime : qi::grammar<Iterator, Attribute()>
{
  datetime();

  typedef typename boost::remove_reference<typename fusion::result_of::at_c<Attribute, 4u>::type>::type::value_type time_attribute;
  typedef typename boost::remove_reference<typename fusion::result_of::at_c<Attribute, 5u>::type>::type::value_type repeater_attribute;
  typedef typename boost::remove_reference<typename fusion::result_of::at_c<Attribute, 6u>::type>::type::value_type lead_time_attribute;

  qi::rule<Iterator, Attribute()> entry_point;
  qi::rule<Iterator, time_attribute()> time;
  qi::rule<Iterator, repeater_attribute()> repeater;
  qi::rule<Iterator, lead_time_attribute()> lead_time;
};

}

#endif
