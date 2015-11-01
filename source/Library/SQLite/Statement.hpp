#ifndef _LIBRARY_SQLITE_STATEMENT_HPP_
#define _LIBRARY_SQLITE_STATEMENT_HPP_

// ------------------------------------------------------------------------------------------------
namespace SqMod {
namespace SQLite {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
class Statement
{
public:
    
    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Statement();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Statement(const Statement & o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Statement(Statement && o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ~Statement();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Statement & operator = (const Statement & o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Statement & operator = (Statement && o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    

protected:

    // --------------------------------------------------------------------------------------------

private:

    // --------------------------------------------------------------------------------------------

};

} // Namespace:: SQLite
} // Namespace:: SqMod

#endif // _LIBRARY_SQLITE_STATEMENT_HPP_
