#include "database/database.h"
#include <iostream>

int main() {
    Database db("database/chess.db");
    if (db.open()) {
        int result = db.addUser("tri", "irt");
        std::cout << "addUser result: " << result << std::endl;

        // std::vector<std::vector<std::string>> matchList = db.getMatch("tue");

        // for (const auto& outerVector : matchList) {
        //     // Iterate through the inner vector
        //     for (const auto& str : outerVector) {
        //         // Print each string element
        //         std::cout << str << " ";
        //     }
        //     std::cout << std::endl;  // Move to the next line after printing each inner vector
        // }
        // std::cout << "Logging for user pert: " << (db.validateUser("pert", "pret") == 1?"Correct credentials":"Errors or wrong credentials") << std::endl;
        db.close();
    } else {
        std::cerr << "Error opening the database" << std::endl;
    }


    return 0;
}
