#ifndef ORGMODE_PARSER_PREAMBLE_HPP
#define ORGMODE_PARSER_PREAMBLE_HPP

#include <orgmode-parser/eol.hpp>

#include <boost/spirit/home/qi/nonterminal.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
struct preamble : qi::grammar<Iterator, Attribute()>
{
  preamble();

  qi::rule<Iterator, Attribute()> entry_point;
  orgmode_parser::eol<Iterator, Attribute> eol;
};

}

#endif
