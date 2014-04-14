#ifndef ORGMODE_PARSER_ITEM_HPP
#define ORGMODE_PARSER_ITEM_HPP

#include <orgmode-parser/title.hpp>
#include <orgmode-parser/eol.hpp>

#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace orgmode_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace fusion = boost::fusion;

template <typename Iterator, typename Attribute>
struct item : qi::grammar<Iterator, Attribute()>
{
  item();

  typedef typename boost::remove_reference<typename fusion::result_of::at_c<Attribute, 0u>::type>::type title_attribute;
  typedef typename boost::remove_reference<typename fusion::result_of::at_c<Attribute, 1u>::type>::type body_attribute;

  qi::rule<Iterator, body_attribute()> body;
  qi::rule<Iterator, Attribute()> entry_point;
  orgmode_parser::title<Iterator, title_attribute> title;
  orgmode_parser::eol<Iterator, body_attribute> eol;
};

}

#endif
