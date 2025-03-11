#include <drogon/HttpAppFramework.h>
#include <drogon/WebSocketClient.h>
#include <iostream>

using namespace drogon;
using namespace std::chrono_literals;

int main()
{
    auto websocketPtr = WebSocketClient::newWebSocketClient("ws://localhost:8000");

    auto request = HttpRequest::newHttpRequest();
    request->setPath("/echo");

    websocketPtr->setMessageHandler(
        [](const std::string& message,
           const WebSocketClientPtr& clientPtr,
           const WebSocketMessageType& type)
        {
            std::string messageType;
            switch (type)
            {
                case WebSocketMessageType::Text:
                    messageType = "text";
                    break;

                case WebSocketMessageType::Pong:
                    messageType = "pong";
                    break;

                case WebSocketMessageType::Ping:
                    messageType = "ping";
                    break;

                case WebSocketMessageType::Binary:
                    messageType = "binary";
                    break;

                case WebSocketMessageType::Close:
                    messageType = "close";
                    break;

                default:
                    messageType = "Unknown";
                    break;
            }

            LOG_INFO << "new message (" << messageType << "): " << message;
        });

    websocketPtr->setConnectionClosedHandler(
        [](const WebSocketClientPtr& clientPtr)
        {
            LOG_INFO << "WebSocket connection closed!";
        });

    LOG_INFO << "Connecting to WebSocket!";

    websocketPtr->connectToServer(
        request,
        [](ReqResult result, const HttpResponsePtr& response, const WebSocketClientPtr& clientPtr)
        {
            if (result != ReqResult::Ok)
            {
                LOG_ERROR << "Failed to establish WebSocket connection!";
                clientPtr->stop();
                return;
            }
            LOG_INFO << "WebSocket connected!";
            clientPtr->getConnection()->setPingMessage("", 2s);
            clientPtr->getConnection()->send("Hello World!");
        });

    // Quit the application after 15 seconds
    app().getLoop()->runAfter(15,
                              []()
                              {
                                  app().quit();
                              });

    app().setLogLevel(trantor::Logger::kDebug);
    app().run();
    LOG_INFO << "Finish!";

    return EXIT_SUCCESS;
}
