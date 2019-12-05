#pragma once

#include "keyframe.h"

#include <vector>
#include <iosfwd>

namespace playx::core {

class keyframe_container {
public:
    keyframe_container() = default;
    explicit keyframe_container(std::vector<keyframe> v);

    std::vector<keyframe>& get_keyframes();
    
    void push_back(keyframe l);
    size_t size() const;

    keyframe_container& operator+=(keyframe_container const& other);

    bool operator==(keyframe_container const& other) const;
    std::vector<keyframe>& operator()();
    friend std::ostream& operator<<(std::ostream& os, const keyframe_container& lc);

private:
    std::vector<keyframe> v_;
};


}