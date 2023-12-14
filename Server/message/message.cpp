#include "message.h"
#include "json/nlohmann/json.hpp"

using json = nlohmann::json;

/* 
    Message methods
*/
Message::Message(MessageType type) : type(type), length(0) {}
Message::Message(std::string msg) {
    type = static_cast<MessageType> (msg[0]); // Type (1B)
    length = static_cast<uint16_t>((msg[1] << 8) | msg[2]); // Length (2B)
    payload = json::parse(msg.substr(3, length)); // Payload (lengthB)
}
        
MessageType Message::getType() const {
    return type;
}

uint16_t Message::getLength() const {
    return length;
}

std::string Message::serialize() const {
    std::string msg;
    msg[0] = static_cast<char>(type);
    msg[1] = static_cast<char>(static_cast<uint8_t>(length >> 8)); // High byte of length
    msg[2] = static_cast<char>(static_cast<uint8_t>(length & 0xFF)); // Low byte of length
    return msg;
}

/*
    UserMessaage methods
*/
// UserMessage(MessageType type, std::string username, std::string password);
//         UserMessage(Message message);

//         std::string getUsername() const;
//         std::string getPassword() const;
//         std::string serialize() const override;
UserMessage::UserMessage(MessageType type, std::string username, std::string password) :
    Message(type), username(username), password(password) {}