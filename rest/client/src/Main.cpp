#include <httplib.h>
#include <cstdio>
#include <memory>
#include <thread>

void ThreadFunc(std::shared_ptr<httplib::Client> client, int id)
{
    auto response = client->Get("/api/v1/Test");

    int status       = response->status;
    std::string body = response->body;

    printf("ID: %i, Status: %i, Body: %s\n", id, status, body.c_str());
}

int main()
{
    // HTTP
    auto client = std::make_shared<httplib::Client>("http://localhost:8000");

    std::vector<std::thread> threads;

    for (int i = 0; i < 10000; ++i)
    {
        threads.push_back(std::thread(ThreadFunc, client, i));
    }

    for (std::thread& thread : threads)
    {
        thread.join();
    }

    return EXIT_SUCCESS;
}
