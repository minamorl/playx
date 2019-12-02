#pragma once

#include <cstdint>
#include <layer.h>

namespace playx::core {

class frame {
public:
    frame(uint32_t frame);
    bool operator==(frame& other) const;
    uint32_t get_frame() const;
    void set_frame(uint32_t frame);

private:
    uint32_t _frame;
};

class timeline {
public:
    timeline();
    std::vector<layer> getCurrentLayers(frame f);

private:
    std::vector<std::pair<frame, layer>> _vec;
};

}