#pragma once

#define WIN32_LEAN_AND_MEAN

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <array>

namespace playx::ui {

class colorwheel_inside_widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
	explicit colorwheel_inside_widget(QOpenGLWidget* parent = nullptr);

	void initializeGL();
	void paintGL();
public slots:
    void receive_pixel_change(std::array<float, 4> pixel);
private:
    QOpenGLVertexArrayObject object_;
	std::unique_ptr<QOpenGLShaderProgram> program_;
    const QWidget* const parent_;

    std::array<float, 4> selected_color_;

	static GLfloat const vertices_[];

    const char* vertex_shader_ =  R"(
#version 440 core

in vec4 vertex;

void main(){
    gl_Position = vertex;
}
)";
    const char* fragment_shader_ = R"(

#version 440 core

uniform vec2 resolution;
uniform vec3 selected_color;

layout(location = 0) out vec4 FragColor;

vec3 hsv_to_rgb( in vec3 hsv ) {
	vec3 v1 = vec3(5.0, 3.0, 1.0);
	vec3 v2 = mod(v1 + hsv.x / 60.0, 6.0);
	vec3 result = hsv.z - hsv.z * hsv.y * max(
		min(min(v2, 4.0 - v2), 1.0)
		, 0.0);
	return result;	
}

vec3 rgb_to_hsv( in vec3 rgb ) {
	vec3 result;
	float maxv = max(max(rgb.x, rgb.y), rgb.z);
	float minv = min(min(rgb.x, rgb.y), rgb.z);
	
	if (maxv == minv) {
		result.x = 0.;
	}
	if (rgb.x == maxv) {
		result.x = 60. * (0. + (rgb.y - rgb.z) / (maxv - minv)); 
	}
	if (rgb.y == maxv) {
		result.x = 60. * (2. + (rgb.z - rgb.x) / (maxv - minv)); 
	}
	if (rgb.z == maxv) {
		result.x = 60. * (4. + (rgb.x - rgb.y) / (maxv - minv)); 
	}
	if (maxv == 0.) {
		result.y = 0.;
	} else {
		result.y = (maxv - minv) / maxv;
	}
	result.z = maxv;
	return result;
}

void main() {

	vec2 position = ( gl_FragCoord.xy / resolution.xy );
	vec3 base_color = rgb_to_hsv(selected_color);
	vec3 color = hsv_to_rgb(vec3(base_color.x, position.x, position.y));
	FragColor = vec4(color, 1.0);

})";
};

}