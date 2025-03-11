#include <mongoose.h>

constexpr const char *URL = "ws://localhost:8000/echo";

// Print websocket response and signal that we're done
static void Handle(struct mg_connection *client, int event, void *eventData)
{
    if (event == MG_EV_OPEN)
    {
        client->is_hexdumping = 1;
    }
    else if (event == MG_EV_ERROR)
    {
        // On error, log error message
        MG_ERROR(("%p %s", client->fd, (char *)eventData));
    }
    else if (event == MG_EV_WS_OPEN)
    {
        // When websocket handshake is successful, send message
        mg_ws_send(client, "hello", 5, WEBSOCKET_OP_TEXT);
    }
    else if (event == MG_EV_WS_MSG)
    {
        // When we get echo response, print it
        struct mg_ws_message *wm = (struct mg_ws_message *)eventData;
        printf("GOT ECHO REPLY: [%.*s]\n", (int)wm->data.len, wm->data.buf);
    }

    if (event == MG_EV_ERROR || event == MG_EV_CLOSE || event == MG_EV_WS_MSG)
    {
        *(bool *)client->fn_data = true;  // Signal that we're done
    }
}

int main(int argc, char *argv[])
{
    struct mg_mgr eventManager;    // Event manager
    bool done = false;             // Event handler flips it to true
    struct mg_connection *client;  // Client connection

    mg_mgr_init(&eventManager);  // Initialise event manager

    mg_log_set(MG_LL_DEBUG);  // Set log level

    client = mg_ws_connect(&eventManager, URL, Handle, &done, NULL);  // Create client

    while (client && !done)
    {
        mg_mgr_poll(&eventManager, 1000);  // Wait for echo
    }

    mg_mgr_free(&eventManager);  // Deallocate resources

    return 0;
}
