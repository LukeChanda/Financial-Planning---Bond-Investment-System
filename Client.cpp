// 958 370

#include "Client.hpp"

#include <stdexcept>
#include <iostream>

Client::Client(ClientData client_data) : client_data_{client_data} {
    // I need to validate that data when I construct it
    /*if (client_data.current_capital < 0) {
        throw std::invalid_argument("Capital cannot be less than zero.");
    }*/
}

//add an exception throw check

// Returns a client's name
std::string Client::GetName() const {
    return client_data_.name;
}

// Returns a client's current capital
double Client::GetCurrentCapital() const {
    return client_data_.current_capital;
}

// Update capital. changing the value, therefore validate the any values before changing them
void Client::SetCurrentCapital(double &new_capital) { // Should I make this virtual?
    // Verifying the proposed new capital is valid, i.e. a non-negative double before being updated.
    if (new_capital < 0) { // Is their any other validation I can do?
        //throw std::runtime_error("A client cannot have negative available capital.");
        //std::cerr << "A client cannot have negative available capital." << std::endl;
    }
    client_data_.current_capital = new_capital;
}

// Returns a client's retirement date
std::string Client::GetRetirementDate() const {
    return client_data_.retirement_date;
}

// Destructor
Client::~Client() {

}



