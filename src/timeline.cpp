#include <timeline.h>
#include <layer_container.h>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/right_open_interval.hpp>
#include <iostream>
#include <vector>


namespace playx::core {

uint32_t frame::get_index() const
{
    return index_;
}

void frame::set_index(uint32_t frame)
{
    index_ = frame;
}

bool frame::operator==(frame const& other) const noexcept {
    return index_ == other.get_index();
}

bool frame::operator<(frame const& other) const noexcept {
    return index_ < other.get_index();
}

std::ostream& operator<<(std::ostream& os, const frame& f)
{
    os << f.get_index();
    return os;
}

timeline::timeline() : imap_() {}

std::vector<layer> timeline::get_current_layers(frame f)
{
    f = frame();
    using interval_type = boost::icl::interval<frame>;
    imap_ += std::make_pair(
        interval_type::right_open(frame(0), frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(frame(1), frame(5)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    imap_ += std::make_pair(
        interval_type::right_open(frame(0), frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));

    std::cout << imap_ << std::endl;
    return std::vector<layer>();
}

}
