#ifndef ORGMODE_PARSER_TITLE_HPP
#define ORGMODE_PARSER_TITLE_HPP

#include <boost/spirit/home/qi/nonterminal.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
struct title : qi::grammar<Iterator, Attribute()>
{
  title();

  qi::rule<Iterator, Attribute()> entry_point;
};

}

#endif
