# Trench Coats Online Store 

## Features

- The application is implemented in C++ and uses layered architecture, separating the domain (product representation), repository(data-base), and user interface, and the files containing the classes which implement the validators, that are handling exceptions, and running tests. This makes the code easier to maintain and extend.

- The project is built using object-oriented programming principles. It uses polymorphism and inheritance relationships between classes and objects, to encapsulate the different components of the online store, such as the product list, shopping cart, and user interface.

- Data is stored in a text file. When the program starts, entities are read from the file. Modifications made during program execution are stored in the file. This is implemented using the iostream library. Insertion and extraction operators for your entities are created and used when reading/writing to files or the console.

- STL algorithms are used wherever possible in the application

- Tests and specifications for non-trivial functions outside the UI are provided. Test coverage is at least 98% for all layers, except the UI.

- At least 10 entities exist in the memory repository at application start

- The application includes robust input validation to ensure that the user inputs are within the expected range and format.

- The user interface is text-based and interactive. It provides a menu-driven system for users to navigate through the application's features. It provides prompts and messages to guide the user through each step, making the process intuitive and user-friendly.

- The application includes validators for the input regarding the trench coats, and custom exception classes to handle various error scenarios, such as updating a non-existent item

- A UML class diagram for the entire application exists, to show the relationship and interaction between all the classes that compose the program, in an easy way to visualize and understand it, without having to necessarily look through the code for that

- The following situations are handled:
    - If an entity that already exists is added, its quantity will be increased. The objects have a unique key associated with a pair of two attributes
    - If the user tries to update/delete an entity that does not exist, a message appears and there is no effect on the list of entities.

## Description
Trench coats are cool. Everyone owns a trench coat. The *“Proper Trench Coats”* store sells fashionable, elegant trench coats and the store has software that allows their customers to order online. The application can be used in two modes: administrator mode and user mode. When the application starts, it offers the option to choose the mode.\
**Administrator mode:** The application has a database that holds available trench coats at a given moment. The store employees can update the database, meaning: add a new trench coat, delete a trench coat (when it is sold out), and update the information of a trench coat. Each **Trench Coat** has a `size`, a `colour`, a `price`, a `quantity`, and a `photograph`, and the employees can search for the trench coat to delete or update based on the size and colour-the pair that makes the unique key. If the key they input is not associated with any available item, a message will be shown. They can update any attribute of the trench coat they want. The photograph is stored as a link to an online resource (the photograph on the presentation site of the store). The administrators also have the option to see all the trench coats in the store.\
**User mode:** A user can access the application and choose one or more trench coats to buy. The application allows the user to:
- See the trench coats in the database, by the preferred size they input, one by one. When the user chooses this option, the data of the first trench coat (size, colour, price, quantity) is displayed. If there are no available items in that size, a message will be displayed
- Choose to visualize the image of the trench coat
- Choose to add the trench to the shopping basket. In this case, the price is added to the total sum the user has to pay. The total sum is shown after each purchase.
- Choose not to add the trench coat to the basket and to continue to the next. In this case, the information corresponding to the next trench coat is shown and the user is again offered the possibility to buy it. This can continue as long as the user wants, as when arriving at the end of the list, if the user chooses next, the application shows the first trench coat again.
- Visualize the shopping basket, in a CSV or HTML file, depending on the type of file that it chooses
- Exit the user mode

To start the application, simply run the main script.
