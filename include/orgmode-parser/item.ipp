#ifndef ORGMODE_PARSER_ITEM_IPP
#define ORGMODE_PARSER_ITEM_IPP

#include <orgmode-parser/item.hpp>

#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/auxiliary/eol.hpp>
#include <boost/spirit/home/qi/auxiliary/attr_cast.hpp>
#include <boost/spirit/home/qi/directive/omit.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
item<Iterator, Attribute>::item()
  : item::base_type(entry_point)
{
  entry_point = title
    >> 
    -(
      qi::omit[eol]
      >> body
     )
    ;
  body = 
    (
      *(
        &!qi::omit[title]
        >> 
        (
         +(qi::char_ - qi::eol)
         >> -eol
        )
        | eol
       )
    )
    ;

  entry_point.name("item");
};

}

#endif
