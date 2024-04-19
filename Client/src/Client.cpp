#include "Client.hpp"

Client::Client() {
    _file_updater.addSharedFolder("project1", "C:/Users/danii/CLionProjects/CodeWithMe/HOST");

    std::thread thread(&Client::updater, this);
    thread.detach();

    receiver();
}

[[noreturn]] void Client::receiver() {
    _responses.add(Response(R"({"changes":{"-1":"","-10":"","-11":"","-3":"","-5":"","-7":"","-9":"","1":"1x","11":"8888","12":"9x","13":"10x","14":"11x","15":"1111","18":"1313","21":"1515","22":"1616","3":"3x","4":"4444","6":"5x","8":"6666","9":"7x"},"deleted":0,"file":"project1/test_changes.txt","new_file_name":""})"));
    while (true) {
        // todo: replace with response from server
        boost::asio::post(_thread_pool, [this](){
            std::lock_guard<std::mutex> lock(_process_responses_mutex);
            _file_updater.processResponses(_responses);
        });
    }
}

void Client::sendRequests() {
    while (!_requests.isEmpty()) {
        // todo: add sending
        std::cout << _requests.get().toJson() << "\n";
    }
}

[[noreturn]] void Client::updater() {
    while (true) {
        _file_updater.checkFilesForUpdate(_requests);
        if (!_requests.isEmpty()) {
            boost::asio::post(_thread_pool, [this](){
                std::lock_guard<std::mutex> lock(_sender_mutex);
                sendRequests();
            });
        }
    }
}