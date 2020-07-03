// 958 370

#ifndef INPUTREADER_CLIENT_HPP
#define INPUTREADER_CLIENT_HPP

#include <string>
#include <memory>

struct ClientData {
    const std::string name; // Client's name (forename and surname).
    double current_capital; // A client's current capital in pence. Check DATATYPES
    const std::string retirement_date; // Perhaps the date should be converted to integer type when read-in then stored.
};

class Client {
    private:
        //std::unique_ptr<Client> client;
        ClientData client_data_;
    public:
        // Constructor
        explicit Client (ClientData client_data);

        // Destructor
        ~Client(); // rule of 5 => I need to have all the other functions e.g. copy, move, etc..

        // Returns a client's name
        std::string GetName() const;

        // Returns a client's current capital
        double  GetCurrentCapital() const;

        // update capital -> changing the value, therefore validate the any values before changing them
        void SetCurrentCapital(double &new_capital); // Should I make this virtual?

        // Returns a client's retirement date
        std::string GetRetirementDate() const;
};

#endif //INPUTREADER_CLIENT_HPP
