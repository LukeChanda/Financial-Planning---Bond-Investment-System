// 958 370

#include "Product.hpp"
//#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "Date.hpp"
#include "Client.hpp"

//#define institution_code_char_requirement {4}; // INS_CHARS, for product code: PRO_CHARS. Perhaps use this for the constraint of the number of chars required

// Static member variable initialised within .cpp because there can only be one instance of Product::product_count_ in
// the program.
int Product::product_count_{0};

// Check the correct layout for multi-line code
Product::Product (const ProductData product_data) : product_data_{product_data} {

    // Verify that the institution code is valid
    // Is the string 4 characters long?
    if(product_data.institution_code.size() < 4) {
        throw std::invalid_argument {"Institution code too short."}; //  Maybe also output the number of chars it currently is
        std::cerr << "ERROR: Institution code too short. It constitutes of only " << product_data.institution_code.size() << " characters. The institution code must have 4 characters."<< std::endl;
    }

    if(product_data.institution_code.size() > 4) {
        //throw std::invalid_argument {"Institution code too long."}; //  Maybe also output the
        std::cerr << "ERROR: Institution code too long. It constitutes of " << product_data.institution_code.size() << " characters. The institution code must have 4 characters."<< std::endl;
    }

    // Are the characters alphabetic?
    bool alphabetical {false};
    for(const char &i : product_data.institution_code) {
        alphabetical = (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ');

        if(alphabetical == false){
            std::cerr << "ERROR: Institution code does not solely consist of alphabetical characters." << std::endl;
            break;
        }
    }

    // Verify that the product code is valid
    // Is the string 8 characters long?
    if(product_data.product_code.size() < 8) {
        //throw std::invalid_argument {"Institution code too short."}; //  Maybe also output the number of chars it currently is
        std::cerr << "ERROR: Product code too short. It constitutes of only " << product_data.product_code.size() << " characters. The product code must have 4 characters."<< std::endl;
    }

    if(product_data.product_code.size() > 8) {
        //throw std::invalid_argument {"Institution code too long."}; //  Maybe also output the
        std::cerr << "ERROR: Product code too long. It constitutes of " << product_data.product_code.size() << " characters. The product code must have 4 characters."<< std::endl;
    }

    // Are the characters alphabetic?
    //bool alphabetical {false}; //does alphabetical need to set to false before the below code?
    for(const char &i : product_data.product_code) {
        alphabetical = (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ');

        if(alphabetical == false){
            std::cerr << "ERROR: Product code does not solely consist of alphabetical characters." << std::endl;
            break;
        }
    }

    // Increase object instance counter by 1.
    ++product_count_;
};

// Destructor
Product::~Product() {
    // Decrease object instance counter by 1.
    --product_count_;
}

int Product::ProductCount() {
    return product_count_;
}

// Returns a product's institution code
std::string Product::GetInstitutionCode() const {
    return product_data_.institution_code;
}

// Returns a product's product code
std::string Product::GetProductCode() const {
    return product_data_.product_code;
}

// Returns a product's annual equivalent rate
double Product::GetAnnualEquivalentRate() const {
    return product_data_.annual_equivalent_rate;
}

// Returns a product's interest period
std::string Product::GetInterestPeriod() const {
    return product_data_.interest_period;
}

// Returns a product's tie-in period
double Product::GetTieInPeriod() const {
    return product_data_.tie_in_period;
}

// Returns a product's minimum investment amount
double Product::GetMinimumInvestment() const {
    return product_data_.min_investment;
}

// Returns a product's maximum investment amount
double Product::GetMaximumInvestment() const {
    return product_data_.max_investment;
}

// Returns a product's investment date
std::string Product::GetInvestmentDate() const {
    return product_data_.investment_date;
}

// Returns a product's available from date
std::string Product::GetAvailableDate() const {
    return product_data_.available_date;
}

// Returns a product's maturity date
std::string Product::GetMaturityDate() const {
    return product_data_.maturity_date;
}

double Product::GetProductValue() const {
    return product_data_.product_value;
}

double Product::Period(Date &t0, Date &t1) {
    /*
     * Why pass objects arguments? Pass pointers to the objects.
    */
    double n{0.0};
    int period_int{0};
    std::string period_str{""};
    int year{0};
    int month{0};

    period_int = t1.DateInt() - t0.DateInt();

    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(8) << period_int;

    period_str = oss.str();

    year = std::stoi(period_str.substr(0,4)); // extract year
    month = std::stoi(period_str.substr(4,2)); // extract month

    if(product_data_.interest_period == "A") { // Product matures before client retires
        n = (double)(year);
    }
    else if(product_data_.interest_period == "M") { // calculate the number of complete months between investment and maturity
        n = (double)(12*year + month);
    }
    else {
        std::cerr << "Undefined interest period." << std::endl;
    }

    return n;
}

void Product::SetProductValue(const Client &client, const double &potential_investment) {
    double f{0.0}; // Product horizon value
    const double p{potential_investment}; // Present product value
    double n{0.0}; // The number of periods interest is compounded
    double r{0.0}; // interest rate

    Date retirement{client.GetRetirementDate()};
    Date maturity{product_data_.maturity_date};
    Date investment{product_data_.investment_date};

    if(product_data_.interest_period =="A") {
        r = product_data_.annual_equivalent_rate;
        //std::cout << "Interest rate, r = " << r << std::endl;
    }
    else if (product_data_.interest_period =="M") {
        r = pow((1.0+product_data_.annual_equivalent_rate),(1.0/12.0)) - 1.0;
        //std::cout << "Interest rate, r = " << r << std::endl;
    }
    else {
        std::cerr << "Invalid interest period." << std::endl;
    }

    if(retirement.DateInt()>maturity.DateInt()) { // overload operator instead to compare dates?
        // calculate the number of complete years between investment and maturity //SHOULD SWITCH CASE BE USED INSTEAD?
        n = Period(investment, maturity);
        //std::cout << "Investment period, n = " << n << std::endl;
        f = p*pow((1.0+r),n);
        //std::cout << "Product value, f = " << f << std::endl;
    }
    else if(retirement.DateInt()<=maturity.DateInt()){ // Client retires before the product matures
        // calculate the number of complete years between investment and maturity //SHOULD SWITCH CASE BE USED INSTEAD?
        n = Period(investment, retirement);
        //std::cout << "Investment period, n = " << n << std::endl;
        f = p*pow((1.0+r),n);
        //std::cout << "Product value, f = " << f << std::endl;
    }
    else {
        std::cerr << "Invalid timescale." << std::endl; // Is this correct to say?
    }

    // amount rounded down to nearest pence
    product_data_.product_value = floor(f * 100.0) / 100.0;
    //std::cout << "Debug: product value = " << product_data_.product_value << std::endl;
}

double Product::GetPrincipal() const {
    return product_data_.principal_investment;
}

// Set principal investment
void Product::SetPrincipal(const double &principal) {
    // Verifying the proposed principal is valid, i.e.greater than the min investment
    if (principal < product_data_.min_investment) { // Is their any other validation I can do?
        //throw std::runtime_error("A client cannot have negative available capital.");
        //std::cerr << "A client cannot have negative available capital." << std::endl;
    }
    product_data_.principal_investment = principal;
}

double Product::GetRate() const{
    /*if(product_data_.interest_period == "A") {
        product_data_.rate = product_data_.annual_equivalent_rate;
    }
    else if(product_data_.interest_period == "M") {
        product_data_.rate = pow((1.0+product_data_.annual_equivalent_rate),(1.0/12.0)) + 1.0;
    }
    else {
        //throw std::runtime_error("Invalid accrural rate");
        //std::cerr << "A product can only accrue interest monthly or annually." << std::endl;
    }*/
    return product_data_.rate;
}

void Product::SetRate() {
    if(product_data_.interest_period == "A") {
        product_data_.rate = product_data_.annual_equivalent_rate;
    }
    else if(product_data_.interest_period == "M") {
        product_data_.rate = pow((1.0+product_data_.annual_equivalent_rate),(1.0/12.0)) + 1.0;
    }
    else {
        //throw std::runtime_error("Invalid accrural rate");
        //std::cerr << "A product can only accrue interest monthly or annually." << std::endl;
    }
}

void Product::SetInvestmentDate(std::string t) {
    product_data_.investment_date = t;
}


