#pragma once

#include <cstdint>
#include <layer.h>
#include <layer_container.h>

#include <boost/icl/split_interval_map.hpp>
#include <boost/icl/right_open_interval.hpp>

namespace playx::core {

class frame {
public:
    frame(uint32_t frame);
    frame();
    bool operator==(frame const& other) const;
    bool operator<(frame const& other) const;
    uint32_t get_frame() const;
    void set_frame(uint32_t frame);
    friend std::ostream& operator<<(std::ostream& os, const frame& f);

private:
    uint32_t _frame;
};

class timeline {
public:
    timeline();
    std::vector<layer> getCurrentLayers(frame f);

private:
    boost::icl::split_interval_map<frame, layer_container> _imap;
};

}