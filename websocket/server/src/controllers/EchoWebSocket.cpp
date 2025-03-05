#include "EchoWebSocket.h"

void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr& connectionPtr,
                                     std::string&& message,
                                     const WebSocketMessageType& messageType)
{
    // write your application logic here
    connectionPtr->send(message);  // just echo
}

void EchoWebSocket::handleNewConnection(const HttpRequestPtr& requestPtr,
                                        const WebSocketConnectionPtr& connectionPtr)
{
    // write your application logic here
}

void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr& connectionPtr)
{
    // write your application logic here
}
