#ifndef _LIBRARY_NUMERIC_LONGINT_HPP_
#define _LIBRARY_NUMERIC_LONGINT_HPP_

// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
template < typename T > class LongInt;

/* ------------------------------------------------------------------------------------------------
 *
*/
template <> class LongInt< Int64 >
{
public:

    // --------------------------------------------------------------------------------------------
    typedef Int64 Type;

private:

    // --------------------------------------------------------------------------------------------
    Type    m_Data;
    SQChar  m_Text[32];

public:

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt()
        : m_Data(0), m_Text()
    {
        /* ... */
    }

    LongInt(Type n)
        : m_Data(n), m_Text()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt(CSStr text);
    LongInt(CSStr text, SQInteger fall);

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt(const LongInt< Type > & o)
        : m_Data(o.m_Data), m_Text()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    ~LongInt()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt & operator = (const LongInt< Type > & o)
    {
        m_Data = o.m_Data;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > & operator = (Type data)
    {
        m_Data = data;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > & operator = (CSStr text);

    /* --------------------------------------------------------------------------------------------
     *
    */
    bool operator == (const LongInt< Type > & o) const
    {
        return (m_Data == o.m_Data);
    }

    bool operator != (const LongInt< Type > & o) const
    {
        return (m_Data != o.m_Data);
    }

    bool operator < (const LongInt< Type > & o) const
    {
        return (m_Data < o.m_Data);
    }

    bool operator > (const LongInt< Type > & o) const
    {
        return (m_Data > o.m_Data);
    }

    bool operator <= (const LongInt< Type > & o) const
    {
        return (m_Data <= o.m_Data);
    }

    bool operator >= (const LongInt< Type > & o) const
    {
        return (m_Data >= o.m_Data);
    }


    /* --------------------------------------------------------------------------------------------
     *
    */
    operator Type () const { return m_Data; }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > operator + (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data + o.m_Data);
    }

    LongInt< Type > operator - (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data - o.m_Data);
    }

    LongInt< Type > operator * (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data * o.m_Data);
    }

    LongInt< Type > operator / (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data / o.m_Data);
    }

    LongInt< Type > operator % (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data % o.m_Data);
    }


    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > operator - () const
    {
        return LongInt< Type >(-m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to compare two instances of this type.
    */
    Int32 Cmp(const LongInt< Type > & o) const
    {
        if (m_Data == o.m_Data)
        {
            return 0;
        }
        else if (m_Data > o.m_Data)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to convert an instance of this type to a string.
    */
    CSStr ToString();

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to retrieve the name from instances of this type.
    */
    static SQInteger Typename(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     *
    */
    void SetNum(Type data)
    {
        m_Data = data;
    }

    Type GetNum() const
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    SQInteger GetSNum() const
    {
        return ClampL< Type, SQInteger >(m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    void SetStr(CSStr text)
    {
        *this = text;
    }

    CSStr GetCStr()
    {
        return ToString();
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    void Random();
    void Random(Type n);
    void Random(Type m, Type n);

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel integer.
    */
    SQInteger ToSqInteger() const
    {
        return ClampL< Type, SQInteger >(m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel float.
    */
    SQFloat ToSqFloat() const
    {
        return ClampL< Float64, SQFloat >(static_cast< Float64 >(m_Data));
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel string.
    */
    CSStr ToSqString()
    {
        return ToString();
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel boolean.
    */
    bool ToSqBool() const
    {
        return (m_Data > 0);
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel character.
    */
    SQChar ToSqChar() const
    {
        return ClampL< Type, SQChar >(m_Data);
    }
};

/* ------------------------------------------------------------------------------------------------
 *
*/
template <> class LongInt< Uint64 >
{
public:

    // --------------------------------------------------------------------------------------------
    typedef Uint64 Type;

private:

    // --------------------------------------------------------------------------------------------
    Type    m_Data;
    SQChar  m_Text[32];

public:

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt()
        : m_Data(0), m_Text()
    {
        /* ... */
    }

    LongInt(Type n)
        : m_Data(n), m_Text()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt(CSStr text);
    LongInt(CSStr text, SQInteger fall);

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt(const LongInt< Type > & o)
        : m_Data(o.m_Data), m_Text()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    ~LongInt()
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt & operator = (const LongInt< Type > & o)
    {
        m_Data = o.m_Data;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > & operator = (Type data)
    {
        m_Data = data;
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > & operator = (CSStr text);

    /* --------------------------------------------------------------------------------------------
     *
    */
    bool operator == (const LongInt< Type > & o) const
    {
        return (m_Data == o.m_Data);
    }

    bool operator != (const LongInt< Type > & o) const
    {
        return (m_Data != o.m_Data);
    }

    bool operator < (const LongInt< Type > & o) const
    {
        return (m_Data < o.m_Data);
    }

    bool operator > (const LongInt< Type > & o) const
    {
        return (m_Data > o.m_Data);
    }

    bool operator <= (const LongInt< Type > & o) const
    {
        return (m_Data <= o.m_Data);
    }

    bool operator >= (const LongInt< Type > & o) const
    {
        return (m_Data >= o.m_Data);
    }


    /* --------------------------------------------------------------------------------------------
     *
    */
    operator Type () const { return m_Data; }

    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > operator + (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data + o.m_Data);
    }

    LongInt< Type > operator - (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data - o.m_Data);
    }

    LongInt< Type > operator * (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data * o.m_Data);
    }

    LongInt< Type > operator / (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data / o.m_Data);
    }

    LongInt< Type > operator % (const LongInt< Type > & o) const
    {
        return LongInt< Type >(m_Data % o.m_Data);
    }


    /* --------------------------------------------------------------------------------------------
     *
    */
    LongInt< Type > operator - () const
    {
        return LongInt< Type >(-m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to compare two instances of this type.
    */
    Int32 Cmp(const LongInt< Type > & o) const
    {
        if (m_Data == o.m_Data)
        {
            return 0;
        }
        else if (m_Data > o.m_Data)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to convert an instance of this type to a string.
    */
    CSStr ToString();

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to retrieve the name from instances of this type.
    */
    static SQInteger Typename(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     *
    */
    void SetNum(Type data)
    {
        m_Data = data;
    }

    Type GetNum() const
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    SQInteger GetSNum() const
    {
        return (SQInteger)(m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    void SetStr(CSStr text)
    {
        *this = text;
    }

    CSStr GetCStr()
    {
        return ToString();
    }

    /* --------------------------------------------------------------------------------------------
     *
    */
    void Random();
    void Random(Type n);
    void Random(Type m, Type n);

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel integer.
    */
    SQInteger ToSqInteger() const
    {
        return ClampL< Type, SQInteger >(m_Data);
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel float.
    */
    SQFloat ToSqFloat() const
    {
        return ClampL< Float64, SQFloat >(static_cast< Float64 >(m_Data));
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel string.
    */
    CSStr ToSqString()
    {
        return ToString();
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel boolean.
    */
    bool ToSqBool() const
    {
        return (m_Data > 0);
    }

    /* --------------------------------------------------------------------------------------------
     * Attempt to convert the long integer to a squirrel character.
    */
    SQChar ToSqChar() const
    {
        return ClampL< Type, SQChar >(m_Data);
    }
};

// ------------------------------------------------------------------------------------------------
typedef LongInt< Int64 > SLongInt;
typedef LongInt< Uint64 > ULongInt;

} // Namespace:: SqMod

#endif // _LIBRARY_NUMERIC_LONGINT_HPP_