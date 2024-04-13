#ifndef CODEWITHME_CLIENT_HPP
#define CODEWITHME_CLIENT_HPP

#include <fstream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include "FileUpdater.hpp"
#include "Queue.hpp"
#include "Request/Request.hpp"

class Client {
public:
    Client();

private:
    FileUpdater                 _file_updater;
    std::mutex                  _process_request_mutex;
    Queue<Request>              _requests_received;
    Queue<Request>              _requests_to_send;
    std::mutex                  _sender_mutex;
    boost::asio::thread_pool    _thread_pool{2};

    [[noreturn]] void receiver();
    void sendRequests();
    [[noreturn]] void updater();
};

#endif //CODEWITHME_CLIENT_HPP
