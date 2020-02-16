#pragma once

#include <QOpenGLFunctions_4_4_Core>
#include <iostream>

namespace playx::core {



class color_picker {
public:
    using color_type = std::array<float, 4>;

    color_picker(unsigned width, unsigned height)
        : width_(width)
        , height_(height)
        , gl(new QOpenGLFunctions_4_4_Core()) {}
    
    void initialize() {
        gl->initializeOpenGLFunctions();
        is_initialized_ = true;
    }

    color_type pick(unsigned x, unsigned y) {
        auto const color_channels = 4;
        gl->glGenBuffers(1, &pbo_);
        gl->glBindBuffer(GL_PIXEL_PACK_BUFFER , pbo_);
        gl->glBufferData(GL_PIXEL_PACK_BUFFER, width_ * height_ * color_channels * sizeof(GLfloat), 0, GL_STATIC_READ);
        gl->glReadPixels(0, 0, width_, height_, GL_RGBA, GL_FLOAT, nullptr);

        data_ = static_cast<GLfloat const*>(gl->glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY));
        
        return {
            data_[((height_ - y) * (width_) + x) * color_channels],
            data_[((height_ - y) * (width_) + x) * color_channels + 1],
            data_[((height_ - y) * (width_) + x) * color_channels + 2],
            data_[((height_ - y) * (width_) + x) * color_channels + 3],
        };
    }

    void cleanup() {
        gl->glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
        is_initialized_ = false;
    }

private:
    unsigned width_, height_;
    GLuint pbo_;
    bool is_initialized_ = false;
    std::unique_ptr<QOpenGLFunctions_4_4_Core> gl;
    const GLfloat* data_;
};

}