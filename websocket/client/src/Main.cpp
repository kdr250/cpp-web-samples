#include <IXNetSystem.h>
#include <IXUserAgent.h>
#include <IXWebSocket.h>
#include <iostream>

int main()
{
    // Required on Windows
    ix::initNetSystem();

    // websockt object
    ix::WebSocket webSocket;

    // Connecto to a server
    std::string url("ws://localhost:8000/echo");
    webSocket.setUrl(url);

    // Setup a callback fired when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback(
        [](const ix::WebSocketMessagePtr& message)
        {
            switch (message->type)
            {
                case ix::WebSocketMessageType::Message:
                    std::cout << "received message: " << message->str << std::endl;
                    std::cout << "> " << std::flush;
                    break;

                case ix::WebSocketMessageType::Open:
                    std::cout << "Connection established" << std::endl;
                    std::cout << "> " << std::flush;
                    break;

                case ix::WebSocketMessageType::Error:
                    std::cout << "Connection error: " << message->str << std::endl;
                    std::cout << "> " << std::flush;
                    break;

                default:
                    break;
            }
        });

    webSocket.start();

    webSocket.send("Hello World!");

    std::cout << "> " << std::flush;

    std::string text;
    while (std::getline(std::cin, text))
    {
        webSocket.send(text);
        std::cout << "> " << std::flush;
    }

    return EXIT_SUCCESS;
}
