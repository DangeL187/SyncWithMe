#include "Client.hpp"
#include "FileUpdater.hpp"

Client::Client() {
    _file_updater = std::make_shared<FileUpdater>(&_requests_to_send);
    _file_updater->addAllowedFolder("C:/Users/danii/CLionProjects/CodeWithMe/example");
    while (true) {}
}

void Client::receiver() {

}

void Client::sender() {

}