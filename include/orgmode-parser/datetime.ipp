#ifndef ORGMODE_PARSER_DATETIME_IPP
#define ORGMODE_PARSER_DATETIME_IPP

#include <orgmode-parser/datetime.hpp>

#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/auxiliary/eol.hpp>
#include <boost/spirit/home/qi/auxiliary/attr.hpp>
#include <boost/spirit/home/qi/directive/omit.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/string.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template <typename Iterator, typename Attribute>
datetime<Iterator, Attribute>::datetime()
  : datetime::base_type(entry_point)
{
  entry_point %=
    qi::omit['<']
    >> qi::uint_
    >> qi::omit['-']
    >> qi::uint_
    >> qi::omit['-']
    >> qi::uint_
    >> qi::omit[+(qi::space - qi::eol)]
    >> 
    (
     (qi::omit[qi::lit("Sun")] >> qi::attr(0u))
     | (qi::omit[qi::lit("Mon")] >> qi::attr(1u))
     | (qi::omit[qi::lit("Tue")] >> qi::attr(2u))
     | (qi::omit[qi::lit("Wed")] >> qi::attr(3u))
     | (qi::omit[qi::lit("Thu")] >> qi::attr(4u))
     | (qi::omit[qi::lit("Fri")] >> qi::attr(5u))
     | (qi::omit[qi::lit("Sat")] >> qi::attr(6u))
    )
    >> -(qi::omit[+(qi::space - qi::eol)] >> time)
    >> -(qi::omit[+(qi::space - qi::eol) >> '+'] >> repeater)
    >> -(qi::omit[+(qi::space - qi::eol) >> '-'] >> lead_time)
    >> *qi::omit[qi::space - qi::eol]
    >> qi::omit['>']
    ;
  time %=
    qi::uint_
    >> qi::omit[':']
    >> qi::uint_
    ;
  repeater %=
    (
     (qi::omit['+'] >> qi::attr(true))
     | qi::attr(false)
    )
    >> qi::uint_
    >> 
    (
     qi::char_('d')
     | qi::char_('w')
     | qi::char_('m')
     | qi::char_('y')
    )
    ;
  lead_time %=
    qi::uint_
    >> 
    (
     qi::char_('d')
     | qi::char_('w')
     | qi::char_('m')
     | qi::char_('y')
    )
    ;

  entry_point.name("datetime");
  time.name("time");
  repeater.name("repeater");
  lead_time.name("lead_time");
};

}

#endif
