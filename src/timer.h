#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace playx::core {

class timer {
public:
    timer() = default;
    timer(std::function<void(uint)> callback, uint duration, uint repeat_count)
        : io_()
        , callback_(std::move(callback))
        , timer_(io_, boost::asio::chrono::milliseconds(duration))
        , strand_(io_)
        , duration_(boost::asio::chrono::milliseconds(duration))
        , repeat_count_(repeat_count)
        , counter_()
    {}
    void callback() {
        if (counter_ >= repeat_count_) {
            return;
        }
        callback_(counter_);
        counter_++;
        timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
        timer_.async_wait(strand_.wrap(boost::bind(&timer::callback, this)));
    }
    void start() {
        timer_.async_wait(strand_.wrap(boost::bind(&timer::callback, this)));
        t_ = boost::thread(boost::bind(&boost::asio::io_service::run, &io_));
    }
    void stop() {
        io_.stop();
        t_.join();
    }

private:
    boost::asio::io_service io_;
    std::function<void(uint)> callback_;
    boost::asio::steady_timer timer_;
    boost::thread t_;
    boost::asio::io_service::strand strand_;
    boost::asio::chrono::milliseconds duration_;
    uint repeat_count_;
    uint counter_;
};

}