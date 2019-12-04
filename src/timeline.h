#pragma once

#include "layer.h"
#include "layer_container.h"

#include <boost/icl/split_interval_map.hpp>

#include <cstdint>
#include <iosfwd>

namespace playx::core {

class frame {
public:
    explicit frame(uint32_t frame) : index_(frame) {}
    frame() = default;
    bool operator==(frame const& other) const noexcept;
    bool operator<(frame const& other) const noexcept;
    uint32_t get_index() const;
    void set_index(uint32_t frame);
    friend std::ostream& operator<<(std::ostream& os, const frame& f);

private:
    uint32_t index_;
};

class timeline {
public:
    timeline();
    std::vector<layer> get_current_layers(frame f);

private:
    boost::icl::split_interval_map<frame, layer_container> imap_;
};

}