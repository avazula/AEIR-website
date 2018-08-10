#include "Camera.h"

/// Normal constructor
Camera::Camera(uint p, uint ID, uint wid, uint hei) : priorID(p), cameraID(ID), width(wid), height(hei) {}

/**
 * \brief Gets and returns the camera ID.
 */
uint Camera::getCameraID() const {
    return cameraID;
}

/**
 * \brief Sets a new camera ID.
 * \param cameraID: the new ID to be set.
 */
void Camera::setCameraID(uint cameraID) {
    Camera::cameraID = cameraID;
}

/**
 * \brief Gets and returns the image's width.
 */
uint Camera::getWidth() const {
    return width;
}

/**
 * \brief Sets a new image width.
 * \param width: the new width to be set.
 */
void Camera::setWidth(uint width) {
    Camera::width = width;
}

/**
 * \brief Gets and returns the image's height.
 */
uint Camera::getHeight() const {
    return height;
}

/**
 * \brief Sets a new image height.
 * \param height: the new height to be set.
 */
void Camera::setHeight(uint height) {
    Camera::height = height;
}

uint Camera::getPriorID() const {
    return priorID;
}

void Camera::setPriorID(uint p) {
    priorID = p;
}