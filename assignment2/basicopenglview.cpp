#include "basicopenglview.h"
#include <QMessageBox>
#include <QtCore>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <QMouseEvent>

void BasicOpenGLView::initializeGL()
{
#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Glew could not initialize" << std::endl;
    }
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    std::cout<<glGetString(GL_VERSION)<<std::endl;
#else
    if(this->format().majorVersion() < 3 && this->format().minorVersion() < 2)
    {
        QMessageBox msgBox;
        msgBox.setText("The OpenGL version available on this computer is too old.");
        msgBox.setInformativeText("OpenGL 3.2 or higher required to run this application.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
        QCoreApplication::quit();
    }
#endif

    /**
     *  @todo assignment two
     *  initialize the mViewMatrix and mProjectionMatrix with starting values here
     */
    // Arbitrary camera values
    Vector3 eye = Vector3(0.0f, 0.0f, 2.0f);
    Vector3 gaze = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    mViewMatrix = mViewMatrix.buildViewMatrix(eye, gaze, up);

    // Arbitrary l, r, b, t, n, f values for orthographic projection
    float ortho_left = -1.5;
    float ortho_right = 1.5;
    float ortho_bottom = -1.5;
    float ortho_top = 1.5;
    float ortho_near = -0.1;
    float ortho_far = -500.0;
    mProjectionMatrix = mProjectionMatrix.buildOrthoProjectionMatrix(ortho_left, ortho_right, ortho_bottom, ortho_top, ortho_near, ortho_far);

    //float fov = 90.0;
    //float aspectRatio = (float) width() / (float) height();
    //float perspec_near = 0.1;
    //float perspec_far = -4.0;
    //mProjectionMatrix = mProjectionMatrix.buildPerspectiveProjectionMatrix(fov, aspectRatio, perspec_near, perspec_far);
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /**
     *  @todo assignment two
     *  mProjectionMatrix has to be updated in here, when the window is
     *  resized with the values depending on the selected method (orthographic
     *  or perspective)
     *  Hint: for the swap between projection methods to work properly you will also
     *  need to add a function that responds to the switch in the UI
     */
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
	float eventX = (float)event->x() / width();
    float eventY = 1.0f - (float) event->y() / height();
	
    eventX -= 0.5f;
    eventY -= 0.5f;
    eventX *= 2.0f;
    eventY *= 2.0f;
	
	Vector3 curPoint(eventX, eventY);
	
	if(mFirstFrameDragging)
	{
		mLastMousePos = curPoint;
		mFirstFrameDragging = false;
		return;
	}
	
	Vector3 difference;
	for(size_t i = 0; i < 3; ++i)
	{
		difference.elements[i] = curPoint.elements[i] - mLastMousePos.elements[i];
	}

    /**
     *  @todo assignment two
     *  use the mouse input to modify mViewMatrix to work as an arc-ball interface,
     *  or to rotate the viewer in the XZ plane, depending on the selected mode in the
     *  UI (Arc Ball or World crawler)
     */

	mLastMousePos = curPoint;
}

void BasicOpenGLView::keyPressEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
}

void BasicOpenGLView::keyReleaseEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
}
