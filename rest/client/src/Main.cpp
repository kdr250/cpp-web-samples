#include <httplib.h>
#include <iostream>

int main()
{
    // HTTP
    httplib::Client client("http://localhost:8000");

    auto response = client.Get("/api/v1/Test");

    std::cout << "Status: " << response->status << std::endl;
    std::cout << "Body: " << response->body << std::endl;

    return EXIT_SUCCESS;
}
