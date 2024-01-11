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

std::vector<std::map<std::string, std::string>> HistoryMessage::getMatches() const {
    return matches;
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
    if (type == SEE_MATCH) matchID = std::stoi(j["matchID"].get<std::string>());
    else match = j["moves"];
}

MatchMessage::MatchMessage(std::string match) : Message(MATCH), match(match) {
    json j;
    j["moves"] = match;
    payload = j.dump();
    length = static_cast<uint16_t>(payload.length());
}

int MatchMessage::getMatchID() const {
    return matchID;
}

std::string MatchMessage::getMatch() const {
    return match;
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

/*
    InviteMessage methods
*/
InviteMessage::InviteMessage(std::vector<std::pair<std::string, int>> playerList) : Message(ONLINE_LIST), playerList(playerList) {
    // Convert player to string then assign it to payload
        std::string result;
        std::pair<std::string, int> player;
        for (auto &element : playerList) {
            json j;
            j["username"] = element.first;
            j["elo"] = element.second;
            result += j.dump();
        }
        payload = result;
        length = static_cast<uint16_t>(payload.length());
}

InviteMessage::InviteMessage(Message message) : Message(message){
    length = message.getPayload().length();

    // Split the payload into substring of player
    std::vector<std::string> substrings = splitString(message.getPayload());
    for (auto &element : substrings) {
        // Convert back to map type
        json j = json::parse(element);
        std::pair<std::string, int> player;
        player.first = j["username"];
        player.second = j["elo"];
        playerList.push_back(player);
    }
}

std::vector<std::pair<std::string, int>> InviteMessage::getPlayerList() const {
    return playerList;
}
