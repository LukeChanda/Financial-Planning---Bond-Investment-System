// 958 370


#ifndef INPUTREADER_DATE_HPP
#define INPUTREADER_DATE_HPP

#include<string>

class Date {
    private:
        const std::string date_; // string to store the date in the format YYYYMMDD

    public:
        explicit Date (const std::string &date);

        // Returns date
        std::string GetDate() const;

        // Converts year substring to an integer value
        int YearInt();

        // Converts month substring to an integer value
        int MonthInt();

        // Converts day substring to an integer value
        int DayInt();

        // Returns Date as integer type
        int DateInt();
};

/*class Period : public Date {
    private:
        Period();

        // Returns the number of complete years between two dates
        int TimePeriodYears(Date &t0, Date& t1);

        // Returns the number of complete months between two dates
        int TimePeriodMonths(Date &t0, Date& t1);
};*/




#endif //INPUTREADER_DATE_HPP
