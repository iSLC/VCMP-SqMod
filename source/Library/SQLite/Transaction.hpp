#ifndef _LIBRARY_SQLITE_TRANSACTION_HPP_
#define _LIBRARY_SQLITE_TRANSACTION_HPP_

// ------------------------------------------------------------------------------------------------
namespace SqMod {
namespace SQLite {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
class Transaction
{
public:
    
    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Transaction();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Transaction(const Transaction & o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Transaction(Transaction && o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ~Transaction();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Transaction & operator = (const Transaction & o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Transaction & operator = (Transaction && o);

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

#endif // _LIBRARY_SQLITE_TRANSACTION_HPP_
