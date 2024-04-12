#ifndef CODEWITHME_CLIENT_HPP
#define CODEWITHME_CLIENT_HPP

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Queue.hpp"
#include "Request/Request.hpp"

class FileUpdater;

class Client {
public:
    Client();

private:
    std::shared_ptr<FileUpdater>    _file_updater;
    Queue<Request>                  _requests_received;
    Queue<Request>                  _requests_to_send;

    void receiver();
    void sender();
};

#endif //CODEWITHME_CLIENT_HPP
