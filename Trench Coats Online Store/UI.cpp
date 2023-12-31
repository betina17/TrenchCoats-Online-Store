#include "UI.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include "Validator.h"
#include <limits>


void User_Interface::start_menu()
{
	
		std::string person;
		int position_of_trench_coat_in_repo;
		Repository* text_file_repository;
		text_file_repository = new Text_File_Repository;
		text_file_repository->read_from_file(data_base);
		int total_price_of_shopping_basket = 0;

		while (1)
		{
				std::cout << "\n";
				std::cout << "\nFor admin mode, press a";
				std::cout << "\nFor user mode, press b";
				std::cout << "\nTo exit the store, press c";
			while (true)
			{
				std::cout << "\nIntrduce your option>";
				std::cin >> person;
				#undef max
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (person.length() == 1 && (person[0] == 'a' || person[0] == 'b' || person[0] == 'c')) {
					break;
				}
				else
					std::cout << "Invalid input. Try again!\n";
			}
			if (person == "a")
			{
				std::string admin_option;
				while (1) {
					std::cout << "\n";
					std::cout << "\nPress 1 to display all the trench coats available in the store\n";
					std::cout << "Press 2 to add a trench to the database\n";
					std::cout << "Press 3 to remove a trench from the database, if it is out of supply\n";
					std::cout << "Press 4 to update the information about a trench coat\n";
					std::cout << "Press 5 to exit administrator mode\n";
					while (true) {
						std::cout << "Introduce your option>";
						std::cin >> admin_option;
						
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear any remaining characters in the input buffer

						if (admin_option.length() == 1 && (admin_option[0] == '1' || admin_option[0] == '2' || admin_option[0] == '3' || admin_option[0] == '4' || admin_option[0] == '5'))
							break;  // Exit the loop as the input is valid
						
						else 
							std::cout << "Invalid option. Please enter 1, 2, or 3.\n";
						
					
					}
					if (admin_option == "1")
					{
						for (auto& trench_coat : data_base)
							std::cout << trench_coat.display_as_string();
					}
					else if (admin_option == "2" || admin_option == "3" || admin_option == "4")
					{
						std::string size;
						while (true)
						{  //as long as the user gives invalid input, a message is shown to him and he can introduce the input again
							std::cout << "\nIntroduce the size of the trench coat: xxs/xs/s/m/l/xl/xxl>";
							std::cin >> size;

							try
							{

								TrenchCoat_Validator::validate_size(size);
								break;
							}
							catch (TrenchCoat_Exception& e)
							{
								std::cout << e.what();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								//here it's not necessary to clear the buffer. but just to be sure

							}
						}
						std::string colour;
						while (true)
						{
							std::cout << "\nIntroduce the colour of the trench coat:>";
							std::cin >> colour;
							try
							{
								TrenchCoat_Validator::validate_colour(colour);
								break;
							}
							catch (TrenchCoat_Exception& e)
							{
								std::cout << e.what();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							}
						}
						auto trench_coat_iterator = std::find_if(data_base.begin(), data_base.end(), [&](TrenchCoat& trench_coat) {return trench_coat.get_colour() == colour && trench_coat.get_size() == size; });
						if (trench_coat_iterator != data_base.end())
						{
							position_of_trench_coat_in_repo = std::distance(data_base.begin(), trench_coat_iterator);
						}

						if (admin_option == "2")
						{
							if (trench_coat_iterator != data_base.end()) //daca iteratorul ajunge la final inseamna ca nu exista elementul respectiv deja
							{
								int quantity_of_trench_coat = data_base[position_of_trench_coat_in_repo].get_quantity();
								quantity_of_trench_coat++;
								data_base[position_of_trench_coat_in_repo].set_quantity(quantity_of_trench_coat);
								text_file_repository->write_to_file(data_base);
								std::cout << "\nThe trench coat already exists in the database, therefore its quantity was increased\n";
							}
							else {
								std::string price;
								while (true)
								{
									std::cout << "\nIntroduce the price of the new trench coat>";
									std::cin >> price;
									try
									{
										TrenchCoat_Validator::validate_price(price);
										break;
									}
									catch (TrenchCoat_Exception& e)
									{
										std::cout << e.what();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

									}
								}
								std::string quantity;
								while (true)
								{
									std::cout << "\nIntroduce the quantity of the new trench coat>";
									std::cin >> quantity;
									try
									{
										TrenchCoat_Validator::validate_quantity(quantity);
										break;
									}
									catch (TrenchCoat_Exception& e)
									{
										std::cout << e.what();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

									}
								}
								std::string photo_link;
								while (true)
								{
									std::cout << "\nIntroduce the photo of the new trench coat>";
									std::cin >> photo_link;
									try
									{
										TrenchCoat_Validator::validate_photograph(photo_link);
										break;
									}
									catch (TrenchCoat_Exception& e)
									{
										std::cout << e.what();
										std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									}
								}
								int int_price = std::stoi(price);
								int int_quantity = std::stoi(quantity);
								TrenchCoat new_trench_coat = TrenchCoat(size, colour, int_price, int_quantity, photo_link);
								data_base.push_back(new_trench_coat);
								text_file_repository->write_to_file(data_base);
							}

						}
						else if (admin_option == "3")
						{
							if (data_base.size() == 0)
								std::cout << "\nThe data base is empty, so therefore, there is no element that you can remove.\n";
							else
							{
								if (trench_coat_iterator == data_base.end())
									std::cout << "\nThis trench coat doesn't exist in our data base.\n";
								else {
									int quantity_of_trench_coat = data_base[position_of_trench_coat_in_repo].get_quantity();
									if (quantity_of_trench_coat > 1)
									{
										quantity_of_trench_coat--;
										data_base[position_of_trench_coat_in_repo].set_quantity(quantity_of_trench_coat);
										std::cout << "\nThe trench coat is not out of supply, therefore it wasn't fully removed, but its quantity was decreased";
									}
									else if (quantity_of_trench_coat == 0)
									{

										data_base.erase(trench_coat_iterator);
										std::cout << "thee trench coat is out of supply, therefore it was completely removed from the data base";
									}

								}
								text_file_repository->write_to_file(data_base);
							}
						}
						else if (admin_option == "4")
						{
							if (data_base.size() == 0)
								std::cout << "\nThe data base is empty, so therefore, there is no element that you can update.\n";
							else {

								if (trench_coat_iterator == data_base.end())
									std::cout << "\nThis trench coat doesn't exist in our data base.\n";
								else
								{
									std::string option_to_update = "e";
									while (1)
									{
										std::cout << "\n";
										std::cout << "\nTo update the price of the trench coat, press a";
										std::cout << "\nTo update the quantity of the trench coat, press b";
										std::cout << "\nTo update the photograph of the trench coat, press c";
										std::cout << "\nWhen you finished updating the information about the trench coat, press d";
										std::cout << "\n>";
										while (true)
										{	
											std::cout << "Introduce your option to update>";
											std::cin >> option_to_update;
											std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
											if (option_to_update.length() == 1 && (option_to_update[0] == 'a' || option_to_update[0] == 'b' || option_to_update[0] == 'c' || option_to_update[0] == 'd'))
												break;
											else
												std::cout << "Invalid option. Try again!";
										}
										if (option_to_update == "a")
										{
											std::string new_price;
											while(true)
											{ 
												std::cout << "\nIntroduce the new price of the trench coat>";
												std::cin >> new_price;
												try
												{TrenchCoat_Validator::validate_price(new_price);
													break;
												}
												catch (TrenchCoat_Exception& e)
												{
													std::cout << e.what();
													std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
												}
											}
											
											int int_new_price = std::stoi(new_price);
											data_base[position_of_trench_coat_in_repo].set_price(int_new_price);
											text_file_repository->write_to_file(data_base);
											//nu pot sa folosesc dynamic_array.get_element(position).set_price, pt ca get_element nu returneaza
											//elementul in sine, ci o copie a lui, pt ca daca te uiti in functie elementul nu e transmir prin
											//referinta, asta inseamna ca functia returneaza o copie a elementului, si eu chiar daca schimb pretul
											//la acea copie, nu se schimba si la elementul original. PFOAAAAA.
											//daca scriam in repo Telem& get_element(int position) cu &, returna elemu, si puteam sa folosesc aici
											//dynamic_array.get_element(position_of_trench_coat_in_repo).set_price(new_price);

										}
										else if (option_to_update == "b")
										{
											std::string new_quantity;
											while(true)
											{ 
												std::cout << "\nIntroduce the new quantity of the trench coat>";					
												std::cin >> new_quantity;
												try
												{TrenchCoat_Validator::validate_quantity(new_quantity);
													break;
												}
												catch (TrenchCoat_Exception& e)
												{
													std::cout << e.what();
													std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
												}
											}
											
											int int_new_quantity = std::stoi(new_quantity);
											data_base[position_of_trench_coat_in_repo].set_quantity(int_new_quantity);
											text_file_repository->write_to_file(data_base);
										}
										else if (option_to_update == "b")
										{
											std::string new_photo_link;
											while(true)
											{ 
												std::cout << "\nIntroduce the new photo of the trench coat>";											
												std::cin >> new_photo_link;
												try
												{TrenchCoat_Validator::validate_photograph(new_photo_link);
													break;
												}
												catch (TrenchCoat_Exception& e)
												{
													std::cout << e.what();
													std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
												}
											}
											
											data_base[position_of_trench_coat_in_repo].set_photograph(new_photo_link);
											text_file_repository->write_to_file(data_base);
										}
										else if (option_to_update == "d")
											break;
										
									}

								}
							}

						}
					}
					else if (admin_option == "5")
					{
						break;
					}
					
				}
			}
			else if (person == "b")
			{
				std::string user_option;
				std::string file_type_to_save_shopping_basket;
				std::string file_to_save_shopping_basket;
				Repository* html_file_repository;
				html_file_repository = new HTML_Repository;
				Repository* csv_file_repository;
				csv_file_repository = new CSV_Repository;
				while (1)
				{
					std::cout << "\nIntroduce the type of the file where you want to save your shopping basket, CSV or HTML>";
					std::cin >> file_type_to_save_shopping_basket;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (file_type_to_save_shopping_basket.find("HTML") != std::string::npos)
					{
						file_to_save_shopping_basket = "htmlfile.html";
						break;
					}
					else if (file_type_to_save_shopping_basket.find("CSV") != std::string::npos)
					{
						file_to_save_shopping_basket = "csvfile.csv";
						break;
					}
					else {
						std::cout << "\nInvalid file type.Try again";
					}
				}
				//aici am facut fara exceptie si validator, le-am facut cumva manual ))
				//std::ofstream fout(file_to_save_shopping_basket);
				while (1)
				{
					std::cout << "\n";
					std::cout << "\nPress 1 to display all the trench coats of the size you want";
					std::cout << "\nPress 2 to see display the shopping basket in the format of a file that you chose";
					std::cout << "\nPress 3 to exit user mode";
					while (true)
					{
						std::cout << "\nIntroduce your option>";
						std::cin >> user_option;
						if (user_option.length()==1 && (user_option[0] == '1' || user_option[0] == '2' || user_option[0] == '3'))
							break;
						else
							std::cout << "Invalid input.Try again!";
					}
					if (user_option == "1")
					{
						std::string size;
						while (true)
						{  
							std::cout << "\nIntroduce the size of the trench coat: xxs/xs/s/m/l/xl/xxl>";
							std::cin >> size;

							try
							{

								TrenchCoat_Validator::validate_size(size);
								int we_have_size = 0;
								for (TrenchCoat& trench_coat : data_base)
									if (strcmp(trench_coat.get_size().c_str(), size.c_str()) == 0)
									{
										we_have_size = 1;
										break;
									}
								if (we_have_size == 1)
									break; //if it got here, it means no exception has been thrown, and we break the loop to go further and introduce the colour
								else
									std::cout << "Sorry, we currently don't have any item in this size. Check another size!";
							}
							catch (TrenchCoat_Exception& e)
							{
								std::cout << e.what();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							}
						}
						
						int i = 0;
						std::string option = "i";
						while (option != "e")
						{
							if (strcmp(data_base[i].get_size().c_str(), size.c_str()) == 0)
							{
								std::cout << data_base[i].display_as_string();
								std::cout << "\n Press 'i' to display the link of the image of the trench coat, or press '-' to skip this step";
								std::string image;
								while (true)
								{
									std::cout << "\n>";
									
									std::cin >> image;
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									if (image.length() ==1 && image[0] == 'i')
									{
										data_base[i].ShowImage();
										break;
									}
									else if (image.length() == 1 && image[0] == '-')
									{
										std::cout << "\n";
										break;
									}
									else
										std::cout << "Invalid input! Try again!";
								}
								//separately or in the same call show image of the coat
								std::cout << "\n Press '+' to add the trench coat to the shooping basket, or press '-' to skip this step";
								std::string add;
								while (true)
								{
									std::cout << "\n>";
									std::cin >> add;
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									if (add.length() == 1 && add[0] == '+')
									{
										shopping_basket.push_back(data_base[i]);
										total_price_of_shopping_basket = total_price_of_shopping_basket + data_base[i].get_price();
										std::cout << "\nNow the total price of your shopping basket is " << total_price_of_shopping_basket << " euros.";
									}
									if (add.length() == 1 && (add[0] == '+' || add[0] == '-'))
									{
										
										std::cout << "\n Press'>' to go to the next trench coat, or 'e' to exit the trench coats";
										while (true)
										{
											std::cout << "\n>";
											std::cin >> option;
											std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
											if (option.length() == 1 && (option[0] == '>' || option[0] == 'e'))
											{
												i++;
												if (i == (data_base.size()))
													i = 0;
												break;
											}
											else
												std::cout << "Invalid input!Try again!";
										}
										break;

									}
								
									else
									
										std::cout << "\nInvalid input! Try again!";
										
								}

							}
							else
							{
								i++;
								if (i == (data_base.size()))
									i = 0;
							}
						}

					}
					else if (user_option == "2")
					{
						if (file_type_to_save_shopping_basket.find("HTML") != std::string::npos)
						{
							html_file_repository->write_to_file(shopping_basket);
							//std::string output_command = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe \"" + file_to_save_shopping_basket + "\"";
							//aici nu merge deschis cu system
							ShellExecuteA(NULL, "open", file_to_save_shopping_basket.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);

						}
						else
						{
							csv_file_repository->write_to_file(shopping_basket);
							std::string output_command = "D:\\apps\\asm\\asm_tools\\npp\\notepad++.exe \"" + file_to_save_shopping_basket + "\"";
							system(output_command.c_str());
						}


					}
					else if (user_option == "3")
					{
						break;
					}
				}
			}

			else if (person == "c")
			{
				std::cout << "Thank you for your time in our store, have a great day!";
				break;
			}

		}
	
}


//daca introduci input=123s, cand faci a=stoi(input), a=123. daca input=s123, a=stoi(input) va da eroare

// the relationship between the User_Interface class and both the Repository class and the CSV_Repository class can be considered Dependency relationships, 
//as the User_Interface class relies on these classes for its proper functioning but does not contain or inherit from them. it uses them as parameters for its functions

//continue intrerupe loop-ul curent si merge inapoi sus la inceputul lui, break iese din loop-ul curent si merge la urmatoarea instructiune dupa loop

/*The relationship between your UI class and TrenchCoat_Validator class in this context can be considered as "uses-a" or "has-a" relationship. This is because 
the UI class is using functionalities of the TrenchCoat_Validator class. It is not a "is-a" (inheritance) or "kind-of" relationship since the UI class does not 
inherit from the TrenchCoat_Validator class.

The "uses-a" relationship is often seen when one class uses the methods of another class, but there isn't a strong relationship between the two. This is often
the case when one class is a utility class providing static methods, like TrenchCoat_Validator in your case.
*/

