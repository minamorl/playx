#include <vector>
#include <timeline.h>
#include <layer_container.h>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/right_open_interval.hpp>
#include <iostream>

namespace playx::core {

frame::frame(uint32_t frame) : _frame(frame) {}

frame::frame() : _frame(0) {}

uint32_t frame::get_frame() const
{
    return _frame;
}

void frame::set_frame(uint32_t frame)
{
    _frame = frame;
}

bool frame::operator==(frame const& other) const {
    return _frame == other.get_frame();
}

bool frame::operator<(frame const& other) const {
    return _frame < other.get_frame();
}

std::ostream& operator<<(std::ostream& os, const frame& f)
{
    os << f.get_frame();
    return os;
}

timeline::timeline() : _imap() {}

std::vector<layer> timeline::getCurrentLayers(frame f)
{
    f = frame();
    using interval_type = boost::icl::interval<frame>;
    _imap += std::make_pair(
        interval_type::right_open(frame(0), frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    _imap += std::make_pair(
        interval_type::right_open(frame(1), frame(5)),
        playx::core::layer_container(std::vector<layer>{layer()}));
    _imap += std::make_pair(
        interval_type::right_open(frame(0), frame(1)),
        playx::core::layer_container(std::vector<layer>{layer()}));

    std::cout << _imap << std::endl;
    return std::vector<layer>();
}

}
