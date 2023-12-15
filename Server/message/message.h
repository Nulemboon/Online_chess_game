#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "json/nlohmann/json.hpp"

using json = nlohmann::json;

// Define message types
enum MessageType : uint8_t {
    // Client message
    ACCEPT,
    REJECT,
    SEE_HISTORY,
    RANDOM_MATCHMAKING,
    CREATE_ROOM,
    OFFER_DRAW,
    RESIGN,
    REGISTER, // <username> <password>
    LOGIN, // <username> <password>
    LOGOUT, // <username> 
    INVITE, // <username> 
    MOVE, // <source_position> <destination_position>
    DELETE_ROOM, // <room_id>
    ACCEPT_INVITE, // <invite_id>
    REJECT_INVITE, // <invite_id>

    // Server message
    HISTORY, // <matches>
    REGISTER_USERNAME_EXISTED,
    REGISTER_PASSWORD_FAIL,
    REGISTER_SUCCESSFUL,
    LOGIN_FAIL,
    USER_BLOCKED,
    USER_LOGGED_IN,
    LOGIN_SUCCESSFUL,
    MATCH_FOUND,
    GAME_DRAW,
    GAME_WIN,
    GAME_LOSE,

};

class Message {
    public:
        Message(MessageType type);
        Message(std::string msg);

        MessageType getType() const;
        uint16_t getLength() const;
        virtual std::string serialize() const;

    protected:
        MessageType type;
        uint16_t length;
        json payload;
};

class UserMessage : protected Message {
    public:
        UserMessage(MessageType type, std::string username, std::string password);
        UserMessage(Message message);

        std::string getUsername() const;
        std::string getPassword() const;
        std::string serialize() const override;

    private:
        std::string username;
        std::string password;
};

class MoveMessage : protected Message {
    public:
        MoveMessage(std::string source, std::string destination);
        MoveMessage(Message message);

        std::string getSource() const;
        std::string getDestination() const;
        std::string serialize() const override;
    
    private:
        std::string source;
        std::string destination;
};

class HistoryMessage : protected Message {
    public:
        HistoryMessage(std::vector<std::vector<std::string>> matches);
        HistoryMessage(Message message);

        std::vector<std::vector<std::string>> getMatches() const;
        std::string serialize() const override;

    private:
        std::vector<std::vector<std::string>> matches;
};


#endif // MESSAGE_H