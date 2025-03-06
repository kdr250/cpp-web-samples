#include <grpcpp/grpcpp.h>
#include <iostream>

// Include the generated protobuf header
#include "example.grpc.pb.h"

// Server-side handler for greeter
class GreeterServiceImpl final : public example::Greeter::Service
{
    grpc::Status SayHello(grpc::ServerContext* context,
                          const example::HelloRequest* request,
                          example::HelloReply* reply) override
    {
        reply->set_message("Hello, " + request->name() + "!");
        return grpc::Status::OK;
    }
};

int main()
{
    std::string serverAddress = "0.0.0.0:50051";
    GreeterServiceImpl greeterService;

    grpc::EnableDefaultHealthCheckService(true);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    builder.RegisterService(&greeterService);

    auto server = builder.BuildAndStart();

    std::cout << "Server listening on " << serverAddress << std::endl;

    // Wait for the server to shutdown
    server->Wait();

    return EXIT_SUCCESS;
}
