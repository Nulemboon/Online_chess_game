#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

class Database {
    public:
        Database (const char* dbName);
        ~Database();

        bool open();
        void close();

        // User-related functions

        /*  This function adds a new record to table User, registers the new user.
            Returns -1 if an error occurs, 0 if the user is already registered, and 1 if the user was successfully registered.
        */
        int addUser(const std::string& userID, const std::string& password);

        /*  This function checks if a user is registered in the database.
            Returns -1 if an error occurs, 0 if the user is not registered, and 1 if the user is registered.
        */
        int userExists(const std::string& userID);

        /*  This function is used for logging in, checks if a user's password is correct.
            Returns -1 if an error occurs, 0 if the password is incorrect or the user is not registered, and 1 if the password is correct.
        */
        int validateUser(const std::string& userID, const std::string& password);

        // Match history functions

        /*  This function adds a new record to table History.
            Returns true if the record was added successfully and false otherwise.
        */
        bool addMatch(const std::string& whiteID, const std::string& blackID, int result, const std::string& moves);
        
        /*  This function returns all matches of the user with userID
            Output order: whiteID, blackID, result, moves, time, history, historyID
            result: 0 = draw, 1 = white wins, 2 = black wins
        */
        std::vector<std::vector<std::string>> getMatch(const std::string& userID);
        
        /*  This function returns all matches between userID and opponentID
            Output order: whiteID, blackID, result, moves, time, history, historyID
            result: 0 = draw, 1 = white wins, 2 = black wins
        */
        std::vector<std::vector<std::string>> getMatch(const std::string& userID, const std::string& opponentID); // Get all match with an opponent

    private:
        sqlite3* db;
        const char* dbName;
        
        /* This function encrypts user's password using bcrypt*/
        std::string encryptPassword(const std::string& input);
};

#endif // DATABASE_H