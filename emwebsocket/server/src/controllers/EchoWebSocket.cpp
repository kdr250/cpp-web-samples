#include "EchoWebSocket.h"

void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr& connectionPtr,
                                     std::string&& message,
                                     const WebSocketMessageType& messageType)
{
    // write your application logic here
    for (auto& connection : connections)
    {
        connection->send(message);  // echo to all clients
    }
}

void EchoWebSocket::handleNewConnection(const HttpRequestPtr& requestPtr,
                                        const WebSocketConnectionPtr& connectionPtr)
{
    // write your application logic here
    connections.emplace_back(connectionPtr);
}

void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr& connectionPtr)
{
    // write your application logic here
    std::erase(connections, connectionPtr);
}
