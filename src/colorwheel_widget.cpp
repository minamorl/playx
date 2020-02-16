#include "colorwheel_widget.h"
#include "colorwheel_inside_widget.h"

#include <QSurfaceFormat>
#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QStackedLayout>

#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <iostream>
#include <cmath>
#include <array>

namespace playx::ui {


const GLfloat colorwheel_widget::vertices_[] = {
	-1.0f, 1.0f,
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f
};

const char* colorwheel_widget::vertex_shader_ = R"(
#version 440 core

in vec4 vertex;

void main(){
    gl_Position = vertex;
}
)";

const char* colorwheel_widget::fragment_shader_ = R"(
#version 440 core

uniform vec2 resolution;
uniform vec3 default_bg_color;
layout(location = 0) out vec4 FragColor;

const float TWO_PI = 6.28318530718;

vec3 hsv_to_rgb( in vec3 hsv ) {
	vec3 v1 = vec3(5.0, 3.0, 1.0);
	vec3 v2 = mod(v1 + hsv.x / 60.0, 6.0);
	vec3 result = hsv.z - hsv.z * hsv.y * max(
		min(min(v2, 4.0 - v2), 1.0)
		, 0.0);
	return result;	
}

void main() {
	vec2 position = gl_FragCoord.xy / resolution.y;
	vec2 to_center = vec2(0.5) - position;
	float angle = (atan(to_center.x, to_center.y) / TWO_PI + 0.5) * 360.0;
	float len = length(to_center);

	vec3 col = hsv_to_rgb(vec3(angle, 1.0, 1.0));
	
   	if (len < 0.4 || len > 0.5)
        FragColor = vec4(default_bg_color, 0.);
    else
		FragColor = vec4(col, 1.0);
}

)";

colorwheel_widget::colorwheel_widget(QWidget* parent)
	: QOpenGLWidget(parent)
	, parent_(parent)
	, picker_(playx::core::color_picker(200, 200))

{
	context_ = std::make_unique<QOpenGLContext>();
	inside_widget_ = std::make_unique<colorwheel_inside_widget>(this);
	
	setFixedSize(200, 200);

	connect(this, &colorwheel_widget::send_pixel_value, inside_widget_.get(), &colorwheel_inside_widget::receive_pixel_change);

	// centering inside_widget_
	inside_widget_->move((width() - inside_widget_->width()) / 2, (height() - inside_widget_->height()) / 2);
}

void colorwheel_widget::initializeGL()
{
	initializeOpenGLFunctions();
	
	QSurfaceFormat fmt;
	fmt.setVersion(4, 4);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(fmt);
	
	context_->create();

	setMouseTracking(true);
	
	setAutoFillBackground(false);

	program_ = std::make_unique<QOpenGLShaderProgram>();
	program_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader_);
	program_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader_);
	program_->link();

	picker_.initialize();
}
void colorwheel_widget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program_->bind();


	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertex_location = program_->attributeLocation("vertex");
	program_->enableAttributeArray(vertex_location);
	program_->setAttributeArray(vertex_location, vertices_, 2);

	int resolution_location = program_->uniformLocation("resolution");
	program_->setUniformValue(resolution_location, QVector2D(width(), height()));

	int default_bg_color_location = program_->uniformLocation("default_bg_color");
	auto bg_color = QWidget::palette().color(QWidget::backgroundRole());
	program_->setUniformValue(default_bg_color_location
		, QVector3D(bg_color.redF(), bg_color.greenF(), bg_color.blueF()));


	glDrawArrays(GL_QUADS, 0, 4);

	program_->disableAttributeArray(vertex_location);
	
	program_->release();
}

void colorwheel_widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) {
		auto const x = event->x();
		auto const y = event->y();

		auto const width = this->width();
		auto const height = this->height();

		glm::vec2 position = glm::vec2{x, y} / static_cast<float>(width);
		glm::vec2 to_center = glm::vec2(0.5, 0.5) - position;
		float len = glm::length(to_center);
		
		if (len >= 0.4 && len <= 0.5) {
			makeCurrent();
			auto pixel = picker_.pick(x, y);
			doneCurrent();

			std::cout << "pixel: " << pixel[0] << " " << pixel[1] << " " << pixel[2];
			if (pixel.at(3) == 1.0) {
				send_pixel_value(pixel);
			}
		}
	}
}

}