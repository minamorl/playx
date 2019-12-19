#include "colorwheel_widget.h"

#include <QSurfaceFormat>
#include <QWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QDesktopWidget>

#include <memory>
#include <iostream>
#include <cmath>

namespace playx::ui {


const GLfloat colorwheel_widget::vertices_[] = {
	-1.0f, 1.0f,
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f
};

const char* colorwheel_widget::vertex_shader_ = R"(
attribute highp vec4 vertex;

void main(){
    gl_Position = vertex;
}
)";

const char* colorwheel_widget::fragment_shader_ = R"(
#ifdef GL_ES
precision mediump float;
#endif

#define TWO_PI 6.28318530718

#extension GL_OES_standard_derivatives : enable

// uniform float time;
// uniform vec2 mouse;
uniform vec2 resolution;

vec3 hsv_to_rgb( in vec3 hsv ) {
	vec3 v1 = vec3(5.0, 3.0, 1.0);
	vec3 v2 = mod(v1 + hsv.x / 60.0, 6.0);
	vec3 result = hsv.z - hsv.z * hsv.y * max(
		min(min(v2, 4.0 - v2), 1.0)
		, 0.0);
	return result;	
}

void main( void ) {
	vec2 position = gl_FragCoord.xy / resolution.x;
	vec2 to_center = vec2(0.5) - position;
	float angle = (atan(to_center.x, to_center.y) / TWO_PI + 0.5) * 360.0;
	float len = length(to_center);

	vec3 col = hsv_to_rgb(vec3(angle, 1.0, 1.0));
	
	gl_FragColor = vec4(col, 1.0);
}
)";

colorwheel_widget::colorwheel_widget(QWidget* parent)
	: QOpenGLWidget(parent)
{
	context_ = std::make_unique<QOpenGLContext>();

	QSurfaceFormat fmt;
	fmt.setVersion(4, 0);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(fmt);
	
	context_->create();

	setMouseTracking(true);
	
	setFixedSize(200, 200);
	setAutoFillBackground(false);
}

void colorwheel_widget::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	program_ = std::make_unique<QOpenGLShaderProgram>(this);
	program_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader_);
	program_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader_);
	program_->link();

}
void colorwheel_widget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program_->bind();


	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertex_location = program_->attributeLocation("vertex");
	program_->enableAttributeArray(vertex_location);
	program_->setAttributeArray(vertex_location, vertices_, 2);

	std::cout << vertex_location << std::endl;

	int resolution_location = program_->uniformLocation("resolution");
	program_->setUniformValue(resolution_location, QVector2D(width(), height()));

	std::cout << resolution_location << std::endl;


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

		auto const window_point = QPoint(
			geometry().x() + x,
			geometry().y() + y
		);
		
		float pixel[] = {0, 0, 0, 0};

		qDebug() << window_point;
		if (std::pow(x - width / 2, 2) + std::pow(y - height / 2, 2) <= std::pow(width / 2, 2)) {
			glReadPixels(window_point.x(), window_point.y(), 1, 1, GL_RGBA, GL_FLOAT, &pixel);
			for (auto p : pixel) {
				qDebug() << p;
			}
		}
	}
}

}