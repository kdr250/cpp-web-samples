#include <grpcpp/grpcpp.h>
#include <iostream>

// Include the generated protobuf header
#include "example.grpc.pb.h"

int main()
{
    // A channel provides a connection to a gRPC server
    std::shared_ptr<grpc::Channel> channel =
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    // a client stub using the channel that provides the interface to talk to the server
    std::unique_ptr<example::Greeter::Stub> greeterStub = example::Greeter::NewStub(channel);

    std::cout << "> What is you name ?" << std::endl;
    std::cout << "> " << std::flush;
    std::string name;

    while (std::getline(std::cin, name))
    {
        grpc::ClientContext context;

        // fill in the request data
        example::HelloRequest request;
        request.set_name(name);

        example::HelloReply reply;

        // call the server and get the response
        grpc::Status status = greeterStub->SayHello(&context, request, &reply);

        if (status.ok())
        {
            std::cout << "receive message: " << reply.message() << std::endl;
        }
        else
        {
            std::cout << "call failed..." << status.error_message() << std::endl;
        }
        std::cout << "> " << std::flush;
    }

    return EXIT_SUCCESS;
}
