#include "Camera.h"

Camera::Camera() : position_(0.0, 0.0, 0.0), lookAt_(0.0, 0.0, 0.0), up_(0.0, 1.0, 0.0)
{
	projection_.setToIdentity();
}

Camera::~Camera()
{}

void Camera::setPerspective(float fov, float aspect, float near, float far)
{
	projection_.setToIdentity();
	projection_.perspective(fov, aspect, near, far);
}

void Camera::setPosition(const QVector3D& position)
{
	position_ = position;
}

QVector3D Camera::position() const
{
	return position_;
}

void Camera::translateCamera(const QVector3D& delta)
{
	// TODO:  Implement camera translation

	setPosition(delta);
}

void Camera::zoomCamera(float x, float y)
{

}

void Camera::rotateCamera(float yaw, float pitch)
{
	QVector3D upVector, rightVector, cameraDir, focusPoint, focusVector;

	//point to rotate about
	focusPoint = QVector3D(0.0f , 0.0f , 0.0f);

	//direction of the camera
	cameraDir = (position_ - focusPoint);
	cameraDir.normalize();
	
	//right & up vector
	rightVector = QVector3D::crossProduct(up_, cameraDir);
	rightVector.normalize();
	upVector = QVector3D::crossProduct(cameraDir, rightVector);
	upVector.normalize();

	//make the focus point the and set the focus vector to be position minus point
	focusVector = position_ - focusPoint;
	focusVector.normalize();

	QMatrix4x4 yawMatrix, pitchMatrix;

	yawMatrix.rotate(yaw, upVector);
	yawMatrix.rotate(pitch, rightVector);

	QMatrix4x4 multiply = yawMatrix * pitchMatrix;
	
	QVector3D newFocusPoint;
	newFocusPoint = focusVector * multiply * 0.1;

	translateCamera(newFocusPoint + focusVector);
	setLookAt(newFocusPoint);
}

void Camera::setGazeVector(const QVector3D& gaze)
{
	lookAt_ = gaze + position_;
	lookAt_.normalize();
}

QVector3D Camera::gazeVector() const
{
	QVector3D gaze = lookAt_ - position_;
	gaze.normalize();
	return gaze;
}

QVector3D Camera::lookAt() const
{
	return lookAt_;
}

QVector3D Camera::upVector() const
{
	return up_;
}

void Camera::setLookAt(const QVector3D& lookAt)
{
	lookAt_ = lookAt;
}

void Camera::translateLookAt(const QVector3D& delta)
{
	lookAt_ += delta;
}

QMatrix4x4 Camera::getViewMatrix() const
{
	QMatrix4x4 ret;
	ret.setToIdentity();
	ret.lookAt(position_, lookAt_, up_);
	return ret;
}

QMatrix4x4 Camera::getProjectionMatrix() const
{
	return projection_;
}