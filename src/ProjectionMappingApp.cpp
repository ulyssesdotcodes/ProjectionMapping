#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ProjectionMappingApp : public App {
  public:
	void setup() override;
	void keyDown(KeyEvent event);
	void mouseDown( MouseEvent event ) override;
	void mouseDrag( MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
	array<vec2, 4> mVertices;
	vec2* mSelectedVertex;

	gl::VboMeshRef mVbo;

	gl::BatchRef mDrawVertex;
	gl::BatchRef mDrawRect;
};

void ProjectionMappingApp::setup()
{
	mVertices[0] = ivec2(100, 100);
	mVertices[1] = ivec2(500, 100);
	mVertices[2] = ivec2(100, 500);
	mVertices[3] = ivec2(500, 500);

	mDrawVertex = gl::Batch::create(geom::Circle().center(vec2(100, 100)).radius(50), gl::getStockShader(gl::ShaderDef().color()));
};

void ProjectionMappingApp::keyDown(KeyEvent event) {
	if (event.getChar() == 'q') {
		quit();
	}
}

void ProjectionMappingApp::mouseDown( MouseEvent event )
{
	float dist = glm::length((vec2) event.getPos() - mVertices[0]);
	float distIndex = 0;

	// Calculate the closest point
	for (int i = 1; i < mVertices.size(); ++i) {
		float newDist = glm::length((vec2) event.getPos() - mVertices[i]);
		if (newDist < dist) {
			dist = newDist;
			distIndex = i;
		}
	}

	mSelectedVertex = &mVertices[distIndex];
}

void ProjectionMappingApp::mouseDrag(MouseEvent event)
{
	*mSelectedVertex = event.getPos();
}

void ProjectionMappingApp::update()
{
}

void ProjectionMappingApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::ScopedColor color(1, 0, 0);

	for (int i = 0; i < mVertices.size(); ++i) {
		gl::ScopedModelMatrix scpModelMatrix;
		gl::translate(mVertices[i]);
		mDrawVertex->draw();
	}
}

CINDER_APP(ProjectionMappingApp, RendererGl(), [&](App::Settings *settings) {
	settings->setFullScreen(true);
})