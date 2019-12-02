#include <timeline.h>

namespace playx::core {

frame::frame(uint32_t frame) : _frame(frame) {}

uint32_t frame::get_frame() const
{
    return _frame;
}

void frame::set_frame(uint32_t frame)
{
    _frame = frame;
}

bool frame::operator==(frame& other) const {
    return _frame == other.get_frame();
}

timeline::timeline() : _vec() {}

std::vector<layer> timeline::getCurrentLayers(frame f)
{
    std::vector<layer> v;
    
    for (auto const& x : _vec) {
        if (x.first == f) {
            v.push_back(x.second);
        }
    }

    return v;
}

}
