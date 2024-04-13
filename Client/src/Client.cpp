#include "Client.hpp"

Client::Client() {
    _file_updater.addAllowedFolder("C:/Users/danii/CLionProjects/CodeWithMe/example");

    std::thread thread(&Client::updater, this);
    thread.detach();

    receiver();
}

[[noreturn]] void Client::receiver() {
    while (true) {
        std::cout << "received request\n";
        _requests_received.add(Request());
        boost::asio::post(_thread_pool, [this](){
            std::lock_guard<std::mutex> lock(_process_request_mutex);
            _file_updater.processRequests(_requests_received);
        });
    }
}

void Client::sendRequests() {
    while (!_requests_to_send.isEmpty()) {
        _requests_to_send.get().toJson(); // todo: add sending
    }
}

[[noreturn]] void Client::updater() {
    while (true) {
        _file_updater.checkFilesForUpdate(_requests_to_send);
        if (!_requests_to_send.isEmpty()) {
            boost::asio::post(_thread_pool, [this](){
                std::lock_guard<std::mutex> lock(_sender_mutex);
                sendRequests();
            });
        }
    }
}