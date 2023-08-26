#include "Validator.h"
#include <cctype>

void TrenchCoat_Validator::validate_size(const std::string& size)
{	
	if (size != "xxs" && size != "xs" && size != "s" &&  size != "m" && size != "l" && size != "xl" && size != "xxl")
			throw TrenchCoat_Exception("Invalid size!Please try again!\n");
}

void TrenchCoat_Validator::validate_colour(const std::string& colour)
{
	if (colour != "red"  && colour != "blue" && colour != "black"  && colour != "white" &&  colour != "yellow" )
		if (colour != "pink"  && colour != "orange"  && colour != "brown"  && colour != "green"  && colour != "purple"  && colour != "gray")
			throw TrenchCoat_Exception("Invalid colour!Please try again!\n");
}

void TrenchCoat_Validator::validate_price(const std::string& price)
{
	int int_price;
	try 
	{	
		int_price = std::stoi(price);
	}
	catch (std::exception& e) 
	{
		throw TrenchCoat_Exception("Invalid price!Please try again!\n");

	}
	
	if (int_price < 0 || int_price > 100000)
		throw TrenchCoat_Exception("Invalid price!Please try again!\n");
}

void TrenchCoat_Validator::validate_quantity(const std::string& quantity)
{
	int int_quantity;
	try {
		int_quantity = std::stoi(quantity);
	}
	catch(std::exception& e){
		throw TrenchCoat_Exception("Invalid quantity!Please try again!\n");
	}
	if (int_quantity < 0 || int_quantity > 100000)
		throw TrenchCoat_Exception("Invalid quantity!Please try again!\n");
}

void TrenchCoat_Validator::validate_photograph(const std::string& photograph)
{
	if (photograph.find("https://") != 0)
		throw TrenchCoat_Exception("Invalid photograph!Please try again!\n");
}

void TrenchCoat_Validator::validate_trench_coat(TrenchCoat& trench_coat)
{
	validate_size(trench_coat.get_size());
	validate_colour(trench_coat.get_colour());
	validate_price(std::to_string(trench_coat.get_price()));
	validate_quantity(std::to_string(trench_coat.get_quantity()));
	validate_photograph(trench_coat.get_photograph());
}



