#include <iostream>
#include <string>

const double tax = 1.3;

class Commodity {
public:
    Commodity(std::string name_, int id_, double price_);
    std::string get_name();
    int get_id() const;
    double get_price();
    double get_price(double units);
    bool set_price(double price_);
    double get_price_with_sales_tax(double units);
private:
    std::string name;
    int id;
    double price;
};

Commodity::Commodity(std::string name_, int id_, double price_) : name(name_), id(id_), price(price_) {}

std::string Commodity::get_name(){
    return name;
}

int Commodity::get_id() const{
    return id;
}
double Commodity::get_price() {
    return price;
}
double Commodity::get_price(double units) {
    return price*units;
}
bool Commodity::set_price(double price_){
    price = price_;
    return 1;
}

double Commodity::get_price_with_sales_tax(double units){
    return price*tax*units;
}
