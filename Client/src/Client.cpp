#include "Client.hpp"

Client::Client() {
    _file_updater.addAllowedFolder("C:/Users/danii/CLionProjects/CodeWithMe/example");

    std::thread thread(&Client::updater, this);
    thread.detach();

    receiver();
}

[[noreturn]] void Client::receiver() {
    while (true) {

    }
}

void Client::sendRequests() {
    boost::asio::post(_thread_pool, [this](){
        std::lock_guard<std::mutex> lock(_sender_mutex);
        while (!_requests_to_send.isEmpty()) {
            _requests_to_send.get().toJson();
        }
    });
}

[[noreturn]] void Client::updater() {
    while (true) {
        _file_updater.checkFilesForUpdate(_requests_to_send);
        if (!_requests_to_send.isEmpty()) {
            sendRequests();
        }
    }
}