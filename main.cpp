// Student ID = 958 370

#include <list>
#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include <ostream>
#include <cmath> // pow
#include <algorithm>

#include "InputReader.hpp"
#include "FixedWidthInputReader.hpp" // For template factory
#include "Product.hpp"
#include "Client.hpp"
#include "Date.hpp"
#include "RecordTransaction.hpp"

// Program entry point
int main() {
    //  Input Files

    // Client file
    const std::string client_csv {"../client.csv"}; // Input filename
    const std::string client_tsv {"../client.tsv"}; // Input filename

    // Products file
    const std::string feed {"../feed.dat"}; // Input filename

    // Create instances file reader classes

    // Create an instance of FixedWidthInputReader
    std::unique_ptr<InputReader> read_dat;

    // Create an instance of CSVInputReader
    std::unique_ptr<InputReader> read_csv;

    // Create an instance of TSVInputReader
    std::unique_ptr<InputReader> read_tsv;

    // Attempt to open csv format of client file
    try {
        read_csv = InputReaderFactory(client_csv);
    } catch (const std::exception & e) {
        std::cerr << "A problem occurred opening " << client_csv << ": " << e.what() << std::endl;
        return 1; // Abort with error status
    }

    // Attempt to open tsv format of client file
    try {
        read_tsv = InputReaderFactory(client_tsv);
    } catch (const std::exception & e) {
        std::cerr << "A problem occurred opening " << client_tsv << ": " << e.what() << std::endl;
        return 1; // Abort with error status
    }

    std::cout << "Multiple formats of client file found and proceeding with csv version." << std::endl;

    // Attempt to open products file
    try {
        // For fixed width fields - field widths are template arguments
        read_dat = InputReaderFactory<4,8,5,1,2,6,6,8,8>(feed);
    } catch (const std::exception & e) {
        std::cerr << "A problem occurred opening " << feed << ": " << e.what() << std::endl;
        return 1; // Abort with error status
    }

    int k{0}; // line counter
    bool empty_string{false};
    std::string product_field{""};

    //Product characteristics
    std::string institution_code{""};
    std::string product_code{""};
    double annual_equivalent_rate{0.0}; // Monthly interest rate, %
    std::string interest_period{""}; // a single period over which interest is accrued, e.g. monthly or yearly
    double tie_in_period{0.0}; // Time period within which investment cannot be resold, measured in years
    double min_investment{0.0}; // Minimum investment amount measured in GBP Sterling, £
    double max_investment{0.0}; // Maximum investment amount measured in GBP Sterling, £
    std::string investment_date{""}; // The date on which the product was purchased/invested in.
    std::string available_date{""}; // From this date the product is available for investment Format: YYYYMMDD
    std::string maturity_date{""}; // Date on which the product matures/expires. Format: YYYYMMDD
    double product_value{0.0}; // Value of the product at a client's retirement date or the product's maturity date (whichever is first).
    double principal_investment{0.0}; // Amount invested in the product by a client
    double rate{0.0}; // accrued interest rate

    std::list<Product> product_list; // Store all products in a list

    // filling up product list
    while(!empty_string) {
        product_field = std::string(read_dat->GetNextField());

        // read in institution code
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            institution_code = product_field;
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // read in product code
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            product_code = product_field;
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // read in AER
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            annual_equivalent_rate = std::stod(product_field);
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // Interest accrued monthly, "M", or annually, "A"
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            interest_period = product_field;
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // tie-in period
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            tie_in_period = std::stod(product_field);
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // minimum investment, £
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            min_investment = std::stod(product_field);
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // maximum investment, £
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            max_investment = std::stod(product_field);
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // available date
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            available_date = product_field;
            ++k;
        }

        product_field = std::string(read_dat->GetNextField());

        // maturity date
        if(product_field.empty()){
            empty_string = true;
        }
        else {
            maturity_date = product_field;
            ++k;
        }

        /** The instance creation attempt should be enclosed by a try catch **/
        if(product_field.empty()) {
            empty_string = true;
        }
        else {
            // Set values of product data
            ProductData product_data{institution_code, product_code, annual_equivalent_rate, interest_period, tie_in_period,
                                     min_investment, max_investment, investment_date, available_date, maturity_date,
                                     product_value, principal_investment, rate};

            // Attempt to create object
            Product product{product_data};

            // Add product to product list
            product_list.push_back(product);
        }
    }

    int j{0}; // Line counter

    // List to store a client's products (portfolio)
    std::list<Product> portfolio;

    bool empty{false}; // Boolean variable used to check if returned field is empty
    bool numeric{true}; // Is capital numeric?
    std::string field{""}; // Store returned field

    double periods{0.0}; // number of periods between two dates

    // Client characteristics
    std::string name{""}; // Store client's name
    double capital{0.0}; // Store client's capital (£)
    std::string retire{""}; // Store retirement date

    double new_capital{0.0};

    while(!empty) {

        Date current_date{"20200405"}; // The start date for each client is 5th April 2020 i.e. "20200405".

        // client name
        field = std::string(read_csv->GetNextField());

        if(field.empty()){
            empty = true;
        }
        else {
            name = field;
        }

        // current capital
        field = std::string(read_csv->GetNextField());

        if(field.empty()){
            empty = true;
        }
        else {
            // Are characters numeric?
            for(const char &i : field) {
                if(!isdigit(i)){
                    //throw std::invalid_argument {"Non-numeric char in string."};
                    std::cout << "Non-numeric field = " << field << std::endl; // cerr
                    capital = 0.0;
                    numeric = false;
                    break; // Exit loop since invalid field format detected
                }
            }
            if(numeric) {
                capital = (std::stod(field)) / 100.0; // Convert capital from pence to pounds
            }

        }

        // retirement date
        field = std::string(read_csv->GetNextField());

        if(field.empty()){
            empty = true;
        }
        else {
            retire = field;
        }

        if(numeric) {
            /** The instance creation attempt should be enclosed by a try catch **/
            // To avoid falling out of scope the object should be referred to using a pointer that
            // exits outside the try catch scope.
            ClientData client_data {name, capital, retire};
            Client client {client_data};

            ++j;

            /** Check if any products in the portfolio have matured **/
            double total_redeem{0.0}; // Total capital redeemed from portfolio products
            double redeem_value{0.0}; // capital redeem from a given product
            double current_capital{client.GetCurrentCapital()}; // A client's current capital

            /** Check for maturity**/

            if(!portfolio.empty()) {
                //Create an iterator of std::list
                std::list<Product>::iterator product_it;

                // Make iterator point to beginning and increment it by one until it reaches end of list.
                for (product_it = portfolio.begin(); product_it != portfolio.end(); product_it++) {

                    Date matured{product_it->GetMaturityDate()};

                    // Has an existing client product matured?
                    if(matured.DateInt() >= current_date.DateInt()) {
                        // Redeem product
                        Date product_investment_date{product_it->GetInvestmentDate()};

                        // Set interest rate according to product accrual rate
                        product_it->SetRate();

                        periods  = product_it->Period(product_investment_date, current_date);
                        redeem_value = (product_it->GetPrincipal())*(pow((1.0+product_it->GetRate()),periods));

                        RecordTrans(client.GetName(), current_date.GetDate(), product_it->GetInstitutionCode(),
                                    product_it->GetProductCode(), "Redeem", redeem_value);

                        //** Delete product from list **/

                        // Updated redeem value
                        total_redeem += redeem_value;
                    }
                }

                // Update client capital
                current_capital += total_redeem;
                client.SetCurrentCapital(current_capital);
            }

            //Create an iterator of std::list
            std::list<Product>::iterator product_list_it;

            // Make iterate point to beginning and increment it one by one till it reaches the end of list.
            for (product_list_it = product_list.begin(); product_list_it != product_list.end(); product_list_it++)
            {
                // Sufficient capital to invest?
                if (client.GetCurrentCapital() >= product_list_it->GetMinimumInvestment()) {

                    // Yes. More capital than minimum investment

                    // How much should be invested?
                    if (client.GetCurrentCapital() < product_list_it->GetMaximumInvestment()) {
                        /** Perhaps call transaction object to calculate new capital.**/
                        // Invest all available capital into product.

                        // Set Principal
                        product_list_it->SetPrincipal(client.GetCurrentCapital());

                        double K{0.0}; // zero capital when all invested

                        // Update capital to zero
                        client.SetCurrentCapital(K); // All capital invested in new product

                    }
                    else {
                        // Current capital is greater than or equal to max investment.
                        // Investing maximum possible amount into product

                        // Set Principal
                        product_list_it->SetPrincipal(product_list_it->GetMaximumInvestment());

                        new_capital = client.GetCurrentCapital()-(product_list_it->GetMaximumInvestment());
                        client.SetCurrentCapital(new_capital);
                    }

                    // Set investment date
                    product_list_it->SetInvestmentDate(product_list_it->GetAvailableDate());

                    // Set Product value
                    product_list_it->SetProductValue(client, client.GetCurrentCapital());

                    // set product rate
                    product_list_it->SetRate();

                    // Set values of product data
                    ProductData new_product_data{product_list_it->GetInstitutionCode(),
                                                 product_list_it->GetProductCode(),
                                                 product_list_it->GetAnnualEquivalentRate(),
                                                 product_list_it->GetInterestPeriod(),
                                                 product_list_it->GetTieInPeriod(),
                                                 product_list_it->GetMinimumInvestment(),
                                                 product_list_it->GetMaximumInvestment(),
                                                 product_list_it->GetInvestmentDate(), // Invested on the day became available
                                                 product_list_it->GetAvailableDate(),
                                                 product_list_it->GetMaturityDate(),
                                                 product_list_it->GetProductValue(),
                                                 product_list_it->GetPrincipal(), // Investing all client capital
                                                 product_list_it->GetRate()};

                    // Attempt to create object
                    Product new_product{new_product_data};

                    // add product to portfolio
                    portfolio.push_back(new_product);

                    // Record Transaction
                    RecordTrans(client.GetName(), product_list_it->GetAvailableDate(), product_list_it->GetInstitutionCode(),
                                product_list_it->GetProductCode(), "Invest", product_list_it->GetPrincipal());
                }
                else {
                    // No. Less capital than minimum investment.

                    // Find the least valuable product in portfolio
                    // Sort portfolio by product horizon value using Lambda Function as comparator
                    portfolio.sort([](const Product &product1, const Product &product2) {
                        if(product1.GetProductValue() == product2.GetProductValue()) {
                            return product1 < product2;
                        } else {
                            return product1.GetProductValue() < product2.GetProductValue();
                        }
                    });

                    // Access the least valuable product in portfolio i.e first element in portfolio list.

                    Date invest_date{portfolio.front().GetInvestmentDate()};
                    Date current_time{product_list_it->GetAvailableDate()};

                    double duration{product_list_it->Period(invest_date,current_time)};

                    if(duration > portfolio.front().GetTieInPeriod()) { // Has tie_period been exceeded?
                        // It is possible to sell product

                        // Should the product be sold?
                        double sale_value = portfolio.front().GetPrincipal()*(pow((1.0+portfolio.front().GetRate()),duration));
                        // Is the product value > required minimum investment
                        if(sale_value >= product_list_it->GetMinimumInvestment()) {

                            // How much should be invested?
                            if (sale_value < product_list_it->GetMaximumInvestment()) {

                                // Invest all sale value into product.

                                // Set Principal
                                product_list_it->SetPrincipal(sale_value);


                                double K{0.0}; // zero capital when all invested

                                // Update capital to zero
                                client.SetCurrentCapital(K); // All capital invested in new product
                                // Sell product
                                // Record Transaction
                                RecordTrans(client.GetName(), product_list_it->GetAvailableDate(), portfolio.front().GetInstitutionCode(),
                                            portfolio.front().GetProductCode(), "Sell", sale_value);
                            }
                            else {
                                // Sale value greater than or equal to max investment
                                // Set Principal
                                product_list_it->SetPrincipal(product_list_it->GetMaximumInvestment());

                                // Update capital
                                new_capital = client.GetCurrentCapital() + sale_value;
                                client.SetCurrentCapital(new_capital);
                            }

                            // Set investment date
                            product_list_it->SetInvestmentDate(product_list_it->GetAvailableDate());

                            // Set Product value
                            product_list_it->SetProductValue(client, client.GetCurrentCapital());

                            // set product rate
                            product_list_it->SetRate();


                            // Set values of product data
                            ProductData new_product_data{product_list_it->GetInstitutionCode(),
                                                         product_list_it->GetProductCode(),
                                                         product_list_it->GetAnnualEquivalentRate(),
                                                         product_list_it->GetInterestPeriod(),
                                                         product_list_it->GetTieInPeriod(),
                                                         product_list_it->GetMinimumInvestment(),
                                                         product_list_it->GetMaximumInvestment(),
                                                         product_list_it->GetInvestmentDate(), // Invested on the day became available
                                                         product_list_it->GetAvailableDate(),
                                                         product_list_it->GetMaturityDate(),
                                                         product_list_it->GetProductValue(),
                                                         product_list_it->GetPrincipal(), // Investing all client capital
                                                         product_list_it->GetRate()};

                            // Attempt to create object
                            Product new_product{new_product_data};

                            // add product to portfolio
                            portfolio.push_back(new_product);

                            // Record Transaction
                            RecordTrans(client.GetName(), product_list_it->GetAvailableDate(), product_list_it->GetInstitutionCode(),
                                        product_list_it->GetProductCode(), "Invest", product_list_it->GetPrincipal());
                        }
                    }
                }
            }
        }

        //reset numeric boolean
        numeric = true;
    }

    return 0; // Exit with success status
}