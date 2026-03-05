#include <CommonAPI/CommonAPI.hpp>
#include <v0/GettingStarted/HelloWorldProxy.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main(){
    // Building the Proxy to call the service
    auto runtime = CommonAPI::Runtime::get();
    // "local" and "GettingStarted.Instance" must match the domain and instanceId used in the service registration
    auto proxy = runtime->buildProxy<v0::GettingStarted::HelloWorldProxy>("local", "GettingStarted.Instance");

    // Wait until the service is available before making calls
    while(!proxy->isAvailable()){
        std::cout << "Waiting for service..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    
    CommonAPI::CallStatus callStatus;
    std::string result;
    // Call the sayHello method on the service. The parameters are:
    // - "Ehab": the name to send to the service
    // - callStatus: an output parameter that will contain the status of the call after it returns
    // - result: an output parameter that will contain the response from the service (the "message" field in the .fidl)
    proxy->sayHello("Ehab", callStatus, result);

    // Check call succeeded
    if(callStatus == CommonAPI::CallStatus::SUCCESS){
        std::cout << "Response: " << result << std::endl;
    } 
    else{
        std::cout << "Call failed with status: " << static_cast<int>(callStatus) << std::endl;
    }

    // Subscribe to event
    proxy->getNotifyGreetingEvent().subscribe([](const std::string& greeting) {
        std::cout << "Event received: " << greeting << std::endl;
    });

    // ← Keep client alive — events arrive on background thread
    std::cout << "Listening for events..." << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}