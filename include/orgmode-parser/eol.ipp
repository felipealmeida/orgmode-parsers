#ifndef ORGMODE_PARSER_EOL_IPP
#define ORGMODE_PARSER_EOL_IPP

#include <orgmode-parser/eol.hpp>

#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/char.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
eol<Iterator, Attribute>::eol()
  : eol::base_type(entry_point)
{
  entry_point =
    (qi::char_('\r') >> -qi::char_('\n'))
    | (qi::char_('\n') >> -qi::char_('\r'))
    ;

  entry_point.name("eol");
};

}

#endif
