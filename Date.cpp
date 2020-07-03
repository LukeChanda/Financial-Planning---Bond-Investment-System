// 958 370
// Created by Luke on 25/04/2020.
//

#include "Date.hpp"
#include <stdexcept> // for std::runtime_error
#include <iostream> // for std::cerr

Date::Date(const std::string &date) : date_{date} {
    // Verify date format
    // Is 8 characters long?
    if(date.size() < 8) {
        //throw std::invalid_argument {"Institution code too short."}; //  Maybe also output the number of chars it currently is
        std::cerr << "ERROR: Date too short. It constitutes of only " << date.size() << " characters. The date must have 8 characters."<< std::endl;
    }

    if(date.size() > 8) {
        //throw std::invalid_argument {"Institution code too long."}; //  Maybe also output the
        std::cerr << "ERROR: Date too long. It constitutes of " << date.size() << " characters. The date must have 8 characters."<< std::endl;
    }

    bool numeric{true};

    // Are characters numeric?
    for(const char &i : date) {
        if(!isdigit(i)){
            //throw std::invalid_argument {"Non-numeric char in string."};
            numeric = false;
            std::cerr << "ERROR: Date does not solely consist of numeric characters." << std::endl;
            //break;
        }
    }

    if (numeric) {
        // Verify the date is valid
        const int year{YearInt()}; // Year stored as an integer
        const int month{MonthInt()}; // Month stored as an integer
        const int day{DayInt()}; // Day stored as an integer

        // Will assume any year is valid
        // 1 <= month <= 12
        if ( (1 > month) || (12 < month) ) {
            //throw std::runtime_error("Month outside valid range");
            std::cerr << "Month outside valid range" << std::endl;
        }
        // Check days is correct for month
        // Start by checking for zero day
        if (day==0) {
            //throw std::runtime_error("Day is zero");
            std::cerr << "Day is zero" << std::endl;

        }
        // This is a great example of switch and the utility of fall-through logic
        bool good {false}; // Assume the days is invalid and test for valid values
        switch (month) {
            // February is complicated
            case 2:
                // Leap year if year is divisible by 4 ...
                if ( year % 4 ) {
                    // Not a leap year (year % 4) was true, i.e. non-zero
                    good = (day < 29); // 28 days or less in non-leap-years
                } else {
                    // Possible leap year - (year % 4) was false

                    /* Leap years do not occur on centuries unless the century is
                    * also divisible by 400, so we need to check for that edge
                    * case.
                    */
                    if ( (year % 100) && (! (year % 400) ) ) {
                        // Year is divisible by 100 but not 400, not a leap year.
                        good = (day < 29);
                    } else {
                        /* Year is divisible by 4 and either not by 100 or by 400,
                        * therefore a leap year with 29 days in February.
                        */
                        good = (day < 30);
                        //std::cout << "Leap year." << std::endl;
                    }
                }
                break;

            case 4:
            case 6:
            case 9:
            case 11:
                good = (day < 31);  // 30 days in April, June, September and November
                break;
            default:
                good = (day < 32); // 31 days in all other months, excluding February
                break;
        }
        if ( ! good ) {
            //throw std::runtime_error("There are less days in the month than that");
            std::cerr << "There are less days in the month than that" << std::endl;
        }
    }
}

std::string Date::GetDate() const {
    return std::string(date_);
}

// Can the below functions be marked with const?

int Date::YearInt() {
    // Extract substring "YYYY" from string "YYYYMMDD" and convert to int
    int year{0};

    try
    {
        year = std::stoi(date_.substr(0,4));

    } //const std::exception & e
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Bad input: std::invalid_argument thrown ->" << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Integer overflow: std::out_of_range thrown ->" << e.what() << std::endl;
    }

    return year;
}

int Date::MonthInt() {
    // Extract substring "MM" from string "YYYYMMDD" and convert to int

    int month{0};

    try
    {
        month = std::stoi(date_.substr(4,2));

    } //const std::exception & e
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Bad input: std::invalid_argument thrown ->" << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Integer overflow: std::out_of_range thrown ->" << e.what() << std::endl;
    }

    return month;
}

int Date::DayInt() {
    // Extract substring "MM" from string "YYYYMMDD" and convert to int
    int day{0};

    try
    {
        day = std::stoi(date_.substr(6,2));

    } //const std::exception & e
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Bad input: std::invalid_argument thrown ->" << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Integer overflow: std::out_of_range thrown ->" << e.what() << std::endl;
    }

    return day;
}

int Date::DateInt() {
    int date_int{0};

    try
    {
        date_int = std::stoi(date_);

    } //const std::exception & e
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Bad input: std::invalid_argument thrown ->" << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Integer overflow: std::out_of_range thrown ->" << e.what() << std::endl;
    }

    return date_int;
}

/*int Period::TimePeriodYears(Date &t0, Date& t1) {
    int T{0}; // Time Period

    if (t0.YearInt() > t1.YearInt()) {
        std::cerr << "Invalid date order." << std::endl;
    }
    else {
        T = t1.YearInt() - t0.YearInt();
    }

    return T;
}*/

/*int Period::TimePeriodMonths(Date &t0, Date &t1) {
    int T{0}; // Time Period

    if (t0.MonthInt() > t1.MonthInt()) {
        std::cerr << "Invalid date order." << std::endl;
    }
    else {
        T = t1.MonthInt() - t0.MonthInt();
    }

    return T;
}*/
