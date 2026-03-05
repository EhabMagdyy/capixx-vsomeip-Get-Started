#include <CommonAPI/CommonAPI.hpp>
#include <v0/GettingStarted/HelloWorldStubDefault.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace v0::GettingStarted;

// Override the methods you defined in .fidl
class HelloWorldService : public HelloWorldStubDefault{
public:
    void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply) override{
        // clientID: identifies which client sent the request
        // name:  the in parameter from your .fidl (String name)
        // _replay: this is a callback function, not a return value. CommonAPI uses this pattern because methods can be async. 
        // You call _reply(response) to send the answer back. This maps directly to the out { String message } in your .fidl
        std::cout << "--> Received from client (" << _client << "): " << _name << std::endl;
        std::string response = "Hello " + _name;
        _reply(response);
    }
};

int main(){
    // Registering the Service -> it reads commonapi.ini to know which binding to use (in my case vsomeip))
    auto runtime = CommonAPI::Runtime::get();
    // Creates your service instance on the heap wrapped in a shared_ptr 
    // CommonAPI requires shared ownership because the runtime holds a reference to it internally.
    auto service = std::make_shared<HelloWorldService>();

    // Register the service with the runtime.
    bool success = runtime->registerService(
        "local",                        // domain
        "GettingStarted.Instance",      // must match .fdepl InstanceId
        service                         // the service instance you created
    );

    if(!success){
        std::cerr << "Service registration failed!" << std::endl;
        return -1;
    }

    std::cout << "Service successfully registered." << std::endl;

    // Fire event every 3 seconds
    int counter = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::string msg = "Event #" + std::to_string(++counter) + " from Service";
        std::cout << "Firing event: " << msg << std::endl;
        service->fireNotifyGreetingEvent(msg);
    }

    return 0;
}
