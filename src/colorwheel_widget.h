#pragma once

#define WIN32_LEAN_AND_MEAN

#include "colorwheel_inside_widget.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <memory>
#include <vector>
#include <array>

namespace playx::ui {

class colorwheel_widget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
	explicit colorwheel_widget(QWidget* parent = nullptr);

	void initializeGL();
	void paintGL();

signals:
	void send_pixel_value(std::array<float, 4> pixel);

protected:
	void mouseMoveEvent(QMouseEvent *event);

private:
	QOpenGLVertexArrayObject object_;
	std::unique_ptr<QOpenGLShaderProgram> program_;
	std::unique_ptr<QOpenGLContext> context_;

	static const char* vertex_shader_;
    static const char* fragment_shader_;
	static GLfloat const vertices_[];

	const QWidget* const parent_;
	std::unique_ptr<colorwheel_inside_widget> inside_widget_;
};

}