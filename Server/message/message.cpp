#include "message.h"
#include <json.hpp>

using json = nlohmann::json;

/* 
    Message methods
*/
Message::Message(MessageType type) : type(type), length(0) {}
Message::Message(std::string msg) {
    type = static_cast<MessageType> (msg[0]); // Type (1B)
    length = static_cast<uint16_t>((msg[1] << 8) | msg[2]); // Length (2B)
    payload = msg.substr(3, length); // Payload (lengthB)
}
        
MessageType Message::getType() const {
    return type;
}

uint16_t Message::getLength() const {
    return length;
}

std::string Message::getPayload() const {
    return payload;
}

std::string Message::serialize() const {
    std::string msg;
    msg[0] = static_cast<char>(type);
    msg[1] = static_cast<char>(static_cast<uint8_t>(length >> 8)); // High byte of length
    msg[2] = static_cast<char>(static_cast<uint8_t>(length & 0xFF)); // Low byte of length
    if (!payload.empty()) msg += payload; 
    return msg;
}

/*
    UserMessaage methods
*/
UserMessage::UserMessage(MessageType type, std::string username, std::string password) :
    Message(type), username(username), password(password) {
        json j;
        j["username"] = username;
        j["password"] = password;
        payload = j.dump();
        length = static_cast<uint16_t>(payload.length());
    }

UserMessage::UserMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    json j = json::parse(message.getPayload());
    username = j["username"];
    password = j["password"];
}

std::string UserMessage::getUsername() const {
    return username;
}

std::string UserMessage::getPassword() const {
    return password;
}

/* 
    MoveMessage methods
*/
MoveMessage::MoveMessage(std::string source, std::string destination) : 
    Message(MOVE), source(source), destination(destination) {
        json j;
        j["source"] = source;
        j["destination"] = destination;
        payload = j.dump();
    }

MoveMessage::MoveMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    json j = json::parse(message.getPayload());
    source = j["source"];
    destination = j["destination"];
}

std::string MoveMessage::getSource() const {
    return source;
}

std::string MoveMessage::getDestination() const {
    return destination;
}

/*
    HistoryMessage methods
*/
HistoryMessage::HistoryMessage(MessageType type, std::vector<std::map<std::string, std::string>> matches) : 
    Message(type), matches(matches) {
        // Convert matches to string then assign it to payload
        std::string result;
        std::map<std::string, std::string> match;
        for (auto &element : matches) {
            json j(element);
            result += j.dump();
        }
        payload = result;
        length = static_cast<uint16_t>(payload.length());
    }

std::vector<std::string> splitString(const std::string& input) {
    std::vector<std::string> result;
    
    // Find the position of the first opening brace
    size_t startPos = input.find('{');
    
    // Process each pair of curly braces
    while (startPos != std::string::npos) {
        // Find the position of the closing brace
        size_t endPos = input.find('}', startPos + 1);
        
        // Extract the substring between the braces
        if (endPos != std::string::npos) {
            std::string substring = input.substr(startPos, endPos - startPos + 1);
            result.push_back(substring);
            
            // Find the position of the next opening brace
            startPos = input.find('{', endPos + 1);
        } else {
            // No closing brace found, break the loop
            break;
        }
    }

    return result;
}

HistoryMessage::HistoryMessage(Message message) : Message(message) {
    length = message.getPayload().length();

    // Split the payload into substring of match
    std::vector<std::string> substrings = splitString(message.getPayload());
    for (auto &element : substrings) {
        // Convert back to map type
        json j = json::parse(element);
        std::map<std::string, std::string> match;
        for (auto it = j.begin(); it != j.end(); ++it) {
            match[it.key()] = it.value();
        }
        matches.push_back(match);
    }
}

std::string HistoryMessage::serialize() const {
    std::string result;

    for (auto & element : matches) {
        json j_map(element);
        result += j_map.dump();
    }
    return result;
}

/*
    MatchMessage methods
*/
MatchMessage::MatchMessage(int matchID) : Message(SEE_MATCH), matchID(matchID) {
        json j;
        j["matchID"] = std::to_string(matchID);
        payload = j.dump();
        length = static_cast<uint16_t>(payload.length());
    }

MatchMessage::MatchMessage(Message msg) : Message(msg) {
    length = msg.getPayload().length();
    json j = json::parse(msg.getPayload());
    matchID = std::stoi(j["matchID"].get<std::string>());
}

int MatchMessage::getMatchID() const {
    return matchID;
}

/*
    ErrorMessage methods
*/
ErrorMessage::ErrorMessage(std::string error) : Message(ERROR), error(error) {
        payload += error;
        length = static_cast<uint16_t>(payload.length());
    }

ErrorMessage::ErrorMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    error = message.getPayload();
}

std::string ErrorMessage::getError() const {
    return error;
}

ListMessage::ListMessage(MessageType type, std::vector<std::pair<std::string, int>> list) : Message(type), list(list) {
    json j;
    j["list"] = list;
    payload = j.dump();
    length = static_cast<uint16_t>(payload.length());
}

ListMessage::ListMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    json j = json::parse(message.getPayload());
    list = std::vector<std::pair<std::string, int>>(j["list"]);
}

std::vector<std::pair<std::string, int>> ListMessage::getList() const {
    return list;
}

MatchFoundMessage::MatchFoundMessage(MessageType type, char color, std::string name, int ELO) : Message(type), name(name), ELO(ELO), color(color) {
    json j;
    j["color"] = color;
    j["name"] = name;
    j["ELO"] = ELO;
    payload = j.dump();
    length = static_cast<uint16_t>(payload.length());
}

MatchFoundMessage::MatchFoundMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    json j = json::parse(message.getPayload());
    color = char(int(j["color"]));
    name = std::string(j["name"]);
    ELO = int(j["ELO"]);
}

char MatchFoundMessage::getColor() const {
    return color;
}

std::string MatchFoundMessage::getName() const {
    return name;
}

int MatchFoundMessage::getELO() const {
    return ELO;
}

PromoteMessage::PromoteMessage(MessageType type, char piece, std::string destination) : Message(type), piece(piece), destination(destination) {
    json j;
    j["piece"] = piece;
    j["dest"] = destination;

    payload = j.dump();
    length = static_cast<uint16_t>(payload.length());
}

PromoteMessage::PromoteMessage(Message message) : Message(message) {
    length = message.getPayload().length();
    json j = json::parse(message.getPayload());
    piece = char(int(j["piece"]));
    destination = std::string(j["dest"]);
}

std::string PromoteMessage::getDest() const {
    return destination;
}

char PromoteMessage::getPiece() const {
    return piece;
}