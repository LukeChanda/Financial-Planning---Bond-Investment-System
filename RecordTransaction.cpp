// 958 370

#include "RecordTransaction.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

bool RecordTrans(std::string client_name, std::string transaction_date, std::string product_institution,
                 std::string product_code, std::string trans_type, double amount) {

    std::string filename{"../" + client_name + ".csv"};

    // convert amount to pence before recording it
    //amount = std::floor((amount * 100.0) + 0.5) / 100.0;
    amount = int(amount*100.00);


    //std::cout << "Debug: In record transaction, checking conversion from pounds to pence. Amount = " << amount << std::endl;


    std::ofstream  file;
    file.open(filename, std::ios_base::app);
    file << transaction_date << "," << product_institution << "," << product_code << "," << trans_type << "," << amount << std::endl;
    file.close();

    return true;
}