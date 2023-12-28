#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>

class Database {
    public:
        Database (const char* dbName);
        ~Database();

        bool open();
        void close();
        sqlite3* getConnection() const;

        // User-related functions

        /*  This function adds a new record to table User, registers the new user.
            Returns -1 if an error occurs, 0 if the user is already registered, and 1 if the user was successfully registered.
        */
        int addUser(const std::string& username, const std::string& password);

        /*  This function checks if a user is registered in the database.
            Returns -1 if an error occurs, 0 if the user is not registered, and 1 if the user is registered.
        */
        int userExists(const std::string& username);

        /*  This function is used for logging in, checks if a user's password is correct.
            Returns -1 if an error occurs, 0 if the password is incorrect, 1 if the password is correct, and 2 if the user is not registered.
        */
        int validateUser(const std::string& username, const std::string& password);

        // Match history functions

        /*  This function adds a new record to table History.
            Returns -1 if an error occured, 1 if the record was added successfully and 0 if whiteID or blackID not found.
        */
        int addMatch(const std::string& whiteID, const std::string& blackID, int result, const std::string& moves);
        
        /*  This function returns all matches of the user with username
            Output order: whiteID, blackID, result, moves, time, history, historyID
            result: 0 = draw, 1 = white wins, 2 = black wins
        */
        std::vector<std::map<std::string, std::string>> getHistory(const std::string& username);
        
        /*  This function returns all matches between username and opponentID
            Output order: whiteID, blackID, result, moves, time, history, historyID
            result: 0 = draw, 1 = white wins, 2 = black wins
        */
        std::vector<std::map<std::string, std::string>> getHistory(const std::string& username, const std::string& opponentID); // Get all match with an opponent

        /* This function returns the details of matchID, including moves
        */
        std::vector<std::map<std::string, std::string>> getMatch(const int matchID);
    private:
        sqlite3* db;
        const char* dbName;
        
        /* This function encrypts user's password using bcrypt*/
        std::string encryptPassword(const std::string& input);
};

#endif // DATABASE_H