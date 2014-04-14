#ifndef ORGMODE_PARSER_TITLE_IPP
#define ORGMODE_PARSER_TITLE_IPP

#include <orgmode-parser/title.hpp>

#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/auxiliary/eol.hpp>
#include <boost/spirit/home/qi/directive/omit.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
title<Iterator, Attribute>::title()
  : title::base_type(entry_point)
{
  entry_point %=
    qi::omit
    [
     qi::char_('*')
     >> +(qi::space - qi::eol)
    ]
    >> *(qi::char_ - qi::eol)
    ;

  entry_point.name("title");
};

}

#endif
