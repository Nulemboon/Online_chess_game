#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <json.hpp>

using json = nlohmann::json;

// Define message types
enum MessageType : uint8_t {
    // Client message
    OK,
    NOT_OK,
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
    PROMOTE, // <destination_position>
    DELETE_ROOM, // <room_id>
    ACCEPT_INVITE, // <username>
    REJECT_INVITE, // <username>
    ACCEPT_DRAW,
    REJECT_DRAW,
    SEE_MATCH, // <match_id>

    // Server message
    HISTORY, // <matches>
    MATCH, // <match>
    REGISTER_USERNAME_EXISTED,
    REGISTER_PASSWORD_FAIL,
    REGISTER_SUCCESSFUL,
    LOGIN_FAIL,
    USER_BLOCKED,
    USER_LOGGED_IN,
    LOGIN_SUCCESSFUL,
    ONLINE_LIST,
    MATCH_FOUND,
    MATCHMAKING_TIMEOUT,
    MOVE_NOT_OK,
    STALEMATE,
    THREE_FOLD,
    FIFTY,
    GAME_DRAW,
    GAME_WIN,
    GAME_LOSE,
    ERROR,
};

class Message {
    public:
        Message(MessageType type);
        Message(std::string msg);

        MessageType getType() const;
        uint16_t getLength() const;
        std::string getPayload() const;
        // Parse the message into a string
        virtual std::string serialize() const;

    protected:
        MessageType type;
        uint16_t length;
        std::string payload;
};

class UserMessage : public Message {
    public:
        UserMessage(MessageType type, std::string username, std::string password);
        UserMessage(Message message);

        std::string getUsername() const;
        std::string getPassword() const;

    private:
        std::string username;
        std::string password;
};

class MoveMessage : public Message {
    public:
        MoveMessage(std::string source, std::string destination);
        MoveMessage(Message message);

        std::string getSource() const;
        std::string getDestination() const;
    
    private:
        std::string source;
        std::string destination;
};

class HistoryMessage : public Message {
    public:
        HistoryMessage(MessageType type, std::vector<std::map<std::string, std::string>> matches);
        HistoryMessage(Message message);

        std::vector<std::map<std::string, std::string>> getMatches() const;
        std::string serialize() const override;

    private:
        std::vector<std::map<std::string, std::string>> matches;
};

class MatchMessage : public Message {
    public:
    MatchMessage(int matchID);
    MatchMessage(Message message);
    MatchMessage(std::string match);

    int getMatchID() const;
    std::string getMatch() const;
    
    private:
    int matchID;
    std::string match;
};

class ErrorMessage : public Message {
    public:
    ErrorMessage(std::string error);
    ErrorMessage(Message message);

    std::string getError() const;
    
    private:
    std::string error;
};

class InviteMessage : public Message {
    public:
    InviteMessage(std::vector<std::pair<std::string, int>> playerList);
    InviteMessage(Message message);

    std::vector<std::pair<std::string, int>> getPlayerList() const;

    private:
    std::vector<std::pair<std::string, int>> playerList;
};

class ListMessage : public Message {
public:
    ListMessage(MessageType type, std::vector<std::pair<std::string, int>> list);
    ListMessage(Message message);

    std::vector<std::pair<std::string, int>> getList() const;

private:
    std::vector<std::pair<std::string, int>> list;
};

class MatchFoundMessage : public Message {
public:
    MatchFoundMessage(MessageType type, char color, std::string name, int ELO);
    MatchFoundMessage(Message message);

    char getColor() const;
    std::string getName() const;
    int getELO() const;

private:
    char color;
    std::string name;
    int ELO;
};

class PromoteMessage : public Message {
public:
    PromoteMessage(MessageType type, char piece, std::string destination);
    PromoteMessage(Message message);

    char getPiece() const;
    std::string getDest() const;

private:
    char piece;
    std::string destination;
};


#endif // MESSAGE_H
