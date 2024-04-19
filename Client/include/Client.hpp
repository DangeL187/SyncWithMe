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

class Client {
public:
    Client();

private:
    /*========================Client========================*/
    FileUpdater                 _file_updater;
    Queue<Response>             _responses;
    Queue<Request>              _requests;
    /*======================================================*/

    /*=======================threads========================*/
    std::mutex                  _process_responses_mutex;
    std::mutex                  _sender_mutex;
    boost::asio::thread_pool    _thread_pool{2};
    /*======================================================*/

    [[noreturn]] void receiver();
    void sendRequests();
    [[noreturn]] void updater();
};

#endif //CODEWITHME_CLIENT_HPP
