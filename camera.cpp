#include "camera.h"

using namespace std;

Camera::Camera(GLfloat fovy, GLint width, GLint hight, GLfloat near_plane, GLfloat far_plane) :
        fovy(fovy), width(width), hight(hight), near_plane(near_plane), far_plane(far_plane)
{
    this->yaw = 90.0f;
    this->pitch = 0.0f;
    this->howCell = 3;
    this->isProcedure = 1;
};

void Camera::setCamera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    this->position = position;
    this->target = target;
    this->up = up;
}

void Camera::getUniformsLight(GLuint shaderId)
{
    //DirectionalLight
    this->dirLightColor = glGetUniformLocation(shaderId, "gDirLight.color");
    this->dirLightIntensity = glGetUniformLocation(shaderId, "gDirLight.ambient_intensity");
    this->dirLightDirection = glGetUniformLocation(shaderId, "gDirLight.direction");
    this->dirLightDiffuseIntensity = glGetUniformLocation(shaderId, "gDirLight.diffuse_intensity");

    //SpecularLight
    this->EyeWorldPos = glGetUniformLocation(shaderId, "gEyeWorldPos");
    this->MatSpecularIntensityLoc = glGetUniformLocation(shaderId, "gMatSpecularIntensity");
    this->SpecularPowerLoc = glGetUniformLocation(shaderId, "gSpecularPower");

    //PointsLight
    this->numPointLightsLocation = glGetUniformLocation(shaderId, "gNumPointsLights");
}

void Camera::setUniformsLight()
{
    //DirectionalLight
    glUniform3f(this->dirLightColor, this->light.color.x, this->light.color.y, this->light.color.z);
    glUniform1f(this->dirLightIntensity,  this->light.ambient_intensity);
    glm::vec3 direction = glm::normalize(this->light.direction);
    glUniform3f(this->dirLightDirection, direction.x, direction.y, direction.z);
    glUniform1f(this->dirLightDiffuseIntensity,  this->light.diffuse_intensity);

    //SpecularLight
    glUniform3f(this->EyeWorldPos, this->position.x, this->position.y, this->position.z);
    glUniform1f(this->MatSpecularIntensityLoc, 1.0f);
    glUniform1f(this->SpecularPowerLoc, 64.0f);

    //PointsLight
    //glUniform1i(this->numPointLightsLocation, NumLights);

   /* for (unsigned int i = 0 ; i < NumLights ; i++) {
        glUniform3f(this->pointLightsLocation[i].color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
        glUniform1f(this->pointLightsLocation[i].ambientIntensity, pLights[i].AmbientIntensity);
        glUniform1f(this->pointLightsLocation[i].diffuseIntensity, pLights[i].DiffuseIntensity);
        glUniform3f(this->pointLightsLocation[i].position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
        glUniform1f(this->pointLightsLocation[i].atten.constant, pLights[i].Attenuation.Constant);
        glUniform1f(this->pointLightsLocation[i].atten.linear, pLights[i].Attenuation.Linear);
        glUniform1f(this->pointLightsLocation[i].atten.exp, pLights[i].Attenuation.Exp);
    }*/
}

void Camera::lightRender()
{

}

void Camera::zoom(float value)
{
	fovy += value;
	if (fovy <= 10) { fovy = 10; }
	else if (fovy >= 150) { fovy = 150; }
}

void Camera::rotate()
{
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->target = glm::normalize(front);
}

void Camera::set_light_param(glm::vec3 color, float ambient_intensity, glm::vec3 direction, float diffuse_intensity)
{
    this->light.color = color;
    this->light.ambient_intensity = ambient_intensity;
    this->light.direction = direction;
    this->light.diffuse_intensity = diffuse_intensity;
}

void Camera::key_callback_special(unsigned char key)
{
    GLfloat rotateSpeed = 5.0f;
    GLfloat transSpeed = 5.0f;
    switch(key)
    {
        case GLUT_KEY_UP:
                    this->pitch += rotateSpeed;
                    this->rotate();
                    break;
        case GLUT_KEY_DOWN:
                    this->pitch -= rotateSpeed;
                    this->rotate();
                    break;
        case GLUT_KEY_LEFT:
                    this->yaw -= rotateSpeed;
                    this->rotate();
                    break;
        case GLUT_KEY_RIGHT:
                    this->yaw += rotateSpeed;
                    this->rotate();
                    break;
        case GLUT_KEY_F1:
                    this->isProcedure = !this->isProcedure;
                    break;
    }
}

void Camera::key_callback(bool is_key_press[128])
{
    GLfloat cameraSpeed = 5.0f;
    GLfloat zoomSpeed = 5.0f;
    for (int i = 0; i < 128; i++)
    {
        if (is_key_press[i])
		{
            switch (i)
            {
                case KEY_W:
                    this->position += cameraSpeed * this->target;
                    break;
                case KEY_S:
                    this->position -= cameraSpeed * this->target;
                    break;
                case KEY_D:
                    this->position += glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
                    break;
                case KEY_A:
                    this->position -= glm::normalize(glm::cross(this->target, this->up)) * cameraSpeed;
                    break;
                case KEY_Q:
                    this->zoom(-zoomSpeed);
                    break;
                case KEY_E:
                    this->zoom(zoomSpeed);
                    break;
                case KEY_Z:
                    this->light.ambient_intensity -= 0.05f;
                    break;
                case KEY_X:
                    this->light.ambient_intensity += 0.05f;
                    break;
                case KEY_C:
                    this->light.diffuse_intensity -= 0.05f;
                    break;
                case KEY_V:
                    this->light.diffuse_intensity += 0.05f;
                    break;
                case KEY_B:
                    this->howCell -= 1;
                    break;
                case KEY_N:
                    this->howCell += 1;
                    break;
                case 27:
                    exit(0);
                    break;
            }
		}
    }
}

glm::mat4 Camera::get_mat()
{
    glm::mat4 view = glm::lookAt(this->position, this->position + this->target, this->up);
	glm::mat4 projection = glm::perspective(this->fovy, (GLfloat)this->width / (GLfloat)this->hight, this->near_plane, this->far_plane);
	return projection * view;
}
