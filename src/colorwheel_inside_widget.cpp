#include "colorwheel_inside_widget.h"

namespace playx::ui {

const GLfloat colorwheel_inside_widget::vertices_[] = {
	-1.0f, 1.0f,
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f
};

colorwheel_inside_widget::colorwheel_inside_widget(QOpenGLWidget* parent)
	: QOpenGLWidget(parent)
	, parent_(parent)
	, picker_(playx::core::color_picker(110, 110))
{

	setMouseTracking(true);
	
	setFixedSize(110, 110);
	setAutoFillBackground(false);

    selected_color_ = {0.0f, 1.0f, 0.486275f, 1.0f};

}

void colorwheel_inside_widget::initializeGL()
{
	initializeOpenGLFunctions();

	QSurfaceFormat fmt;
	fmt.setVersion(4, 4);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(fmt);

	program_ = std::make_unique<QOpenGLShaderProgram>();
	program_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader_);
	program_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader_);
	program_->link();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	picker_.initialize();

}
void colorwheel_inside_widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_->bind();


	// Tell OpenGL programmable pipeline how to locate vertex position data
	int vertex_location = program_->attributeLocation("vertex");
	program_->enableAttributeArray(vertex_location);
	program_->setAttributeArray(vertex_location, vertices_, 2);

	int resolution_location = program_->uniformLocation("resolution");
	program_->setUniformValue(resolution_location, QVector2D(width(), height()));

    int selected_color_location = program_->uniformLocation("selected_color");
	program_->setUniformValue(selected_color_location, QVector3D(selected_color_.at(0), selected_color_.at(1), selected_color_.at(2)));
    /*
	int default_bg_color_location = program_->uniformLocation("default_bg_color");
	auto bg_color = QWidget::palette().color(QWidget::backgroundRole());
	program_->setUniformValue(default_bg_color_location
		, QVector3D(bg_color.redF(), bg_color.greenF(), bg_color.blueF()));
    */

	glDrawArrays(GL_QUADS, 0, 4);

	program_->disableAttributeArray(vertex_location);
	
	program_->release();
}

void colorwheel_inside_widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) {
		auto const x = event->x();
		auto const y = event->y();

		makeCurrent();
		app_state_->brush_state().color(picker_.pick(x, y));
		doneCurrent();
	}
}

void colorwheel_inside_widget::receive_pixel_change(std::array<float, 4> pixel) {
    selected_color_ = pixel;
    
    update();
}

}
