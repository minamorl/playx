#pragma once

#include "layer.h"
#include "keyframe.h"

#include <memory>
#include <vector>
#include <iosfwd>

namespace playx::core {

class keyframe_container {
public:
    keyframe_container() = default;
    keyframe_container(std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>> v)
        : v_(std::move(v))
    {}

    std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>& get_keyframes();
    
    template<class... Args>
    void emplace_back(Args&&... args)
    {
        v_.emplace_back(std::forward<Args>(args)...);
    }

    size_t size() const noexcept;

    keyframe_container& operator+=(keyframe_container const& other);

    bool operator==(keyframe_container const& other) const;
    std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>>& operator()();
    friend std::ostream& operator<<(std::ostream& os, const keyframe_container& lc);

private:
    std::vector<std::pair<std::shared_ptr<layer>, std::shared_ptr<keyframe>>> v_;
};


}