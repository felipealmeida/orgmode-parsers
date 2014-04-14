#ifndef ORGMODE_PARSER_PREAMBLE_IPP
#define ORGMODE_PARSER_PREAMBLE_IPP

#include <orgmode-parser/preamble.hpp>

#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/auxiliary/eol.hpp>
#include <boost/spirit/home/qi/auxiliary/eoi.hpp>
#include <boost/spirit/home/qi/auxiliary/attr.hpp>

namespace orgmode_parser {

template <typename Iterator, typename Attribute>
preamble<Iterator, Attribute>::preamble()
  : preamble::base_type(entry_point)
{
  namespace qi = boost::spirit::qi;
  entry_point %=
    *
    (
     &!(qi::char_('*') | qi::eoi)
     >> *(qi::char_ - qi::eol)
     >> -eol
    )
    ;

  entry_point.name("preamble");
}


}

#endif
