#pragma once

#include "keyframe.h"

#include <vector>
#include <iosfwd>

namespace playx::core {

class keyframe_container {
public:
    keyframe_container() = default;
    explicit keyframe_container(std::vector<keyframe> v)
        : v_(std::move(v))
    {}

    std::vector<keyframe>& get_keyframes();
    
    template<class... Args>
    void emplace_back(Args&&... args)
    {
        v_.emplace_back(std::forward<Args>(args)...);
    }

    size_t size() const noexcept;

    keyframe_container& operator+=(keyframe_container const& other);

    bool operator==(keyframe_container const& other) const;
    std::vector<keyframe>& operator()();
    friend std::ostream& operator<<(std::ostream& os, const keyframe_container& lc);

private:
    std::vector<keyframe> v_;
};


}