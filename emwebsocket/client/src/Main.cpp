#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#include <iostream>

EM_BOOL OnOpen(int eventType, const EmscriptenWebSocketOpenEvent* websocketEvent, void* userData)
{
    std::cout << "On Open" << std::endl;

    EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(websocketEvent->socket, "Hello");
    if (result)
    {
        std::cout << "Failed to execute emscripten_websocket_send_utf8_text(): " << result
                  << std::endl;
    }
    return EM_TRUE;
}

EM_BOOL OnError(int eventType, const EmscriptenWebSocketErrorEvent* websocketEvent, void* userData)
{
    std::cout << "On Error" << std::endl;
    return EM_TRUE;
}

EM_BOOL OnClose(int eventType, const EmscriptenWebSocketCloseEvent* websocketEvent, void* userData)
{
    std::cout << "On Close" << std::endl;
    return EM_TRUE;
}

EM_BOOL OnMessage(int eventType,
                  const EmscriptenWebSocketMessageEvent* websocketEvent,
                  void* userData)
{
    std::cout << "On Message" << std::endl;

    if (websocketEvent->isText)
    {
        std::cout << "message: " << websocketEvent->data << std::endl;  // for only ascii chars
    }

    return EM_TRUE;
}

int main()
{
    if (!emscripten_websocket_is_supported())
    {
        std::cout << "websocket is not supported..." << std::endl;
        return EXIT_SUCCESS;
    }

    EmscriptenWebSocketCreateAttributes websocketAttributes = {"ws://127.0.0.1:8080/echo",
                                                               NULL,
                                                               EM_TRUE};

    EMSCRIPTEN_WEBSOCKET_T websocket = emscripten_websocket_new(&websocketAttributes);

    emscripten_websocket_set_onopen_callback(websocket, NULL, OnOpen);
    emscripten_websocket_set_onerror_callback(websocket, NULL, OnError);
    emscripten_websocket_set_onclose_callback(websocket, NULL, OnClose);
    emscripten_websocket_set_onmessage_callback(websocket, NULL, OnMessage);

    return EXIT_SUCCESS;
}
