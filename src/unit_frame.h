#pragma once

#include <boost/icl/split_interval_map.hpp>

#include <cstdint>
#include <iosfwd>

namespace playx::core {
    
class unit_frame {
public:
    explicit unit_frame(uint32_t frame) : index_(frame) {}
    unit_frame() = default;
    bool operator==(unit_frame const& other) const noexcept;
    bool operator<(unit_frame const& other) const noexcept;
    unit_frame& operator++();
    unit_frame& operator--();

    uint32_t get_index() const;
    void set_index(uint32_t frame);
    friend std::ostream& operator<<(std::ostream& os, const unit_frame& f);
    friend unit_frame operator+(unit_frame const& f, unit_frame const& other);

private:
    uint32_t index_;
};

}