// 958 370

#ifndef INPUTREADER_RECORDTRANSACTION_HPP
#define INPUTREADER_RECORDTRANSACTION_HPP

#include <iostream>
#include <fstream>
#include <string>

/* Record a transaction
     * Args:
     *   std::string filename - the name of the file where the transactions are recorded
     *   std::string transaction_date - date of the transaction
     *   std::string product_institution - product institution code
     *   std::string product_code - product code
     *   std::string trans_type - type of transaction ("Invest", "Sell" or "Redeem")
     *   std::string amount - amount resulting from the transaction (in pence)
     *
     * Returns:
     *   true if the last character was the end of the current field, false
     *   otherwise.
     */

bool RecordTrans(std::string client_name, std::string transaction_date, std::string product_institution,
        std::string product_code, std::string trans_type, double amount);

#endif //INPUTREADER_RECORDTRANSACTION_HPP
