#include "keyframe.h"
#include "layer.h"

namespace playx::core {


QImage& keyframe::get_image()
{
    return image_;
}


boost::icl::discrete_interval<unit_frame> keyframe::get_interval() const {
    auto interval = boost::icl::interval<unit_frame>::right_open(start_, end_);
    return interval;
}


bool keyframe::operator==(keyframe const& other) const
{
    return start_ == other.start_ && end_ == other.end_ && image_ == other.image_;
}

}