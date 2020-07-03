// 958 370

#ifndef INPUTREADER_PRODUCT_HPP
#define INPUTREADER_PRODUCT_HPP

#include<string>
#include <cmath> // pow

#include "Date.hpp"
#include "Client.hpp"

struct ProductData {
    std::string institution_code;
    std::string product_code;
    double annual_equivalent_rate; // Monthly interest rate, %
    std::string interest_period; // a single period over which interest is accrued, e.g. monthly or yearly
    double tie_in_period; // Time period within which investment cannot be resold, measured in years
    double min_investment; // Minimum investment amount measured in GBP Sterling, £
    double max_investment; // Maximum investment amount measured in GBP Sterling, £
    std::string investment_date; // The date on which the product was purchased/invested in.
    std::string available_date; // From this date the product is available for investment Format: YYYYMMDD
    std::string maturity_date; // Date on which the product matures/expires. Format: YYYYMMDD
    double product_value; // Value of the product at a client's retirement date or the product's maturity date (whichever is first).
    double principal_investment; // Amount invested in the product by a client
    double rate; // accrued interest rate
};

class Product {
    private:
        static int product_count_; // Do I use this?
        ProductData product_data_;

    public:
    // Constructor (single argument therefore marked explicit to avoid implicit type conversions)
    explicit Product (const ProductData product_data);

    // Destructor
    ~Product();

    // Counts the number of instances of the product object
    static int ProductCount();

    // Should the below getters be virtual?

    // Returns a product's institution code
    std::string GetInstitutionCode() const;

    // Returns a product's product code
    std::string GetProductCode() const;

    // Returns a product's annual equivalent rate
    double GetAnnualEquivalentRate() const;

    // Returns a product's interest period
    std::string GetInterestPeriod() const;

    // Returns a product's tie-in period
    double GetTieInPeriod() const;

    // Returns a product's minimum investment amount
    double GetMinimumInvestment() const;

    // Returns a product's maximum investment amount
    double GetMaximumInvestment() const;

    // Returns a product's investment date
    std::string GetInvestmentDate() const;

    void SetInvestmentDate(std::string t);

    // Returns a product's available from date
    std::string GetAvailableDate() const;

    // Returns a product's maturity date
    std::string GetMaturityDate() const;

    // Returns a product's horizon value (time is either retirement or maturity, whichever is first)
    double GetProductValue() const;

    double Product::Period(Date &t0, Date &t1);

    // Set a product's horizon value
    void Product::SetProductValue(const Client &client, const double &potential_investment);

    // Returns a product's principal investment
    double GetPrincipal() const;

    // Set principal investment
    void SetPrincipal(const double &principal);

    // Return's interest rate
    double GetRate() const;

    // Set product rate
    void SetRate();

    // Compares to products according to their value a the horizon (maturity or retirement)
    bool operator <(const Product &product) const {
        return product_data_.product_value < product.GetProductValue();
    }
};

#endif //INPUTREADER_PRODUCT_HPP
