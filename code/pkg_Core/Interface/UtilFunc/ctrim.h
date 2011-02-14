#ifndef UTILFUNC_CTRIM_H_
#define UTILFUNC_CTRIM_H_

#pragma warning (push, 2)
#include <iterator>
#include <functional>
#include <algorithm>
#ifndef __GNUC__
#include <locale>
#endif
#pragma warning (pop)

namespace trim
{
    //---------------------------------------------------------------------------
    template <typename T> struct space;

    template <> struct space<char>: public std::unary_function<char, bool>
    {
        bool operator()(char c) const {return c > 0 && c <= ' ';}
    };

    template <> struct space<wchar_t>: public std::unary_function<wchar_t, bool>
    {
        bool operator()(wchar_t c) const {return c > 0 && c <= L' ';}
    };
    //---------------------------------------------------------------------------
    template <typename T> class value: std::unary_function<T, bool>
    {
    private:
        T val_;
    public:
        explicit value(const T& v): val_(v) {}
        bool operator()(const T& v) const {return v == val_;}
    };
    //---------------------------------------------------------------------------
    template<class T, class S> struct values: std::binary_function<T, S, bool>
    {
        bool operator()(const T& v, const S& c) const
        {
            for (typename S::const_iterator it = c.begin(); it != c.end(); ++it)
            {
                if (v == *it)
                    return true;
            }
            return false;
        }
    };
    //---------------------------------------------------------------------------
#ifndef __GNUC__
    template <typename T, std::ctype_base::mask type = std::ctype_base::space>
    class locale_char: public std::unary_function<T, bool>
    {
    private:
        const std::ctype<T> & ctype_;
    public:
        bool operator() (const T& v) const {return ctype_.is(type, v);}
        explicit locale_char(const std::locale& loc = std::locale())
            : ctype_(std::use_facet<std::ctype<T> >(loc)) {}
    };
#endif
    //---------------------------------------------------------------------------

    template <typename BidirectionalIterator, typename OutputIterator, typename Predicate>
    OutputIterator
        ctrim( BidirectionalIterator first,
        BidirectionalIterator last,
        OutputIterator result,
        Predicate pred )
    {
        typedef std::reverse_iterator<BidirectionalIterator> ReverseIterator;
        typedef typename std::iterator_traits<BidirectionalIterator>::value_type value_type;

        BidirectionalIterator start = std::find_if(first, last, std::not1(pred));
        return std::copy( start,
            std::find_if( ReverseIterator(last),
            ReverseIterator(start),
            std::not1(pred) ).base(),
            result );
    }

    template <typename BidirectionalIterator, typename OutputIterator>
    OutputIterator
        ctrim( BidirectionalIterator first,
        BidirectionalIterator last,
        OutputIterator result )
    {
        typedef typename std::iterator_traits<BidirectionalIterator>::value_type value_type;
        return ctrim(first, last, result, space<value_type>());
    }

    template <typename S, typename Predicate> void ctrim(S& s, Predicate pred)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(pred)));
        s.erase(std::find_if( s.rbegin(), s.rend(), std::not1(pred) ).base(), s.end());
    }

    template <typename S> void ctrim(S& s)
    {
        typedef typename S::value_type value_type;
        ctrim(s, space<value_type>());
    }

    template <class S> void remove(S& c, const S& match)
    {
        typedef typename S::value_type value_type;
        for (;;)
        {
            typename S::iterator it = std::find_if(c.begin(), c.end(),
                std::bind2nd(values<value_type, S>(), match));
            if (it == c.end())
                break;
            c.erase(it);
        }
    }

    template <class S, class C> long replace(S& s, const S& match, const C& newchar)
    {
        long count = 0;
        typedef typename S::value_type value_type;
        typename S::iterator it = s.begin();

        for (; it != s.end(); ++it)
        {
            it = std::find_if(it, s.end(),
                std::bind2nd(values<value_type, S>(), match));
            if (it != s.end())
            {
                *it = newchar;
                count++;
            }
        }

        return count;
    }

    template <class S> long replace_each(S& s, const S& match, const S& chars)
    {
        long count = 0;
        typedef typename S::value_type value_type;
        typename S::iterator it = s.begin();

        for (; it != s.end(); ++it)
        {
            it = std::find_if(it, s.end(),
                std::bind2nd(values<value_type, S>(), match));
            if (it != s.end())
            {
                size_t n = match.find(*it);
                if (n < chars.size())
                {
                    *it = chars[n];
                    count++;
                }
            }
        }

        return count;
    }
}

#endif // UTILFUNC_CTRIM_H_
