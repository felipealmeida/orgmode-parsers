#ifndef ORGMODE_PARSER_EOL_HPP
#define ORGMODE_PARSER_EOL_HPP

#include <boost/spirit/home/qi/nonterminal.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
struct eol : qi::grammar<Iterator, Attribute()>
{
  eol();

  qi::rule<Iterator, Attribute()> entry_point;
};

}

#endif
