#include "staticobject.h"
#include "ode/ode.h"

StaticObject::StaticObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, string modelName, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->pos = pos;

    /* Set up graphics objects */
    m_model.loadModel(modelName);

    double normalizedScale = 1.0/ m_model.getNormalizedScale();
    m_model.setScale(normalizedScale * scale.x, normalizedScale * scale.y, normalizedScale * scale.z);
    m_model.setRotation(0,rot.x,1,0,0);
    m_model.setRotation(1,rot.y,0,1,0);
    m_model.setRotation(2,rot.z,0,0,1);
    m_model.setPosition(pos.x, pos.y, pos.z);

    this->vertices.resize(m_model.getMeshCount());
    this->indices.resize(m_model.getMeshCount());

    glm::mat4 r = glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0, 0, 1)) *
            glm::rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1, 0, 0)) *
            glm::rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0, 0, 1));

    glm::mat4 transformMatrix = glm::translate(pos) * r * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

    for (int i = 0; i < m_model.getMeshCount(); i++)
    {
        this->vertices.at(i) = m_model.getMesh(i).getVertices();
        this->indices.at(i) = m_model.getMesh(i).getIndices();

        for (auto& vec : this->vertices.at(i)) vec = transformMatrix * glm::vec4(vec, 1.f);

        dTriMeshDataID data = dGeomTriMeshDataCreate();
        dGeomTriMeshDataBuildSingle(data, &this->vertices.at(i).at(0), 3 * sizeof(float), std::size(this->vertices.at(i)),
                                    &this->indices.at(i).at(0), std::size(this->indices.at(i)), 3 * sizeof(this->indices.at(0).at(0)));

        m_geom = dCreateTriMesh(s, data, 0, 0, 0);
    }

    ofLog() << __func__;
    ofLog() << m_model.getMeshNames().at(0);
    ofLog() << m_model.getMeshCount();
}

void StaticObject::update()
{

}

void StaticObject::draw()
{
    /* Get data from ODE */
    //const dReal* thePos = dBodyGetPosition(m_body);
    //const dReal* oderot = dBodyGetQuaternion(m_body);

    /* Set the position */
    //setPosition(glm::vec3(thePos[0],thePos[1], thePos[2]));

    /* Get ODEs rotation quaternion, convert it to an OF one,
     * and then collect the angle and vector from that: */
   // m_rotation = ofQuaternion(oderot[1], oderot[2], oderot[3], oderot[0]);
    //float rotationAmount;
   // ofVec3f rotationAngle;
   // m_rotation.getRotate(rotationAmount, rotationAngle);

    /* Draw the model */
    /* Save the current state of the graphics transform stack: */
    ofPushMatrix();

    /* Translate to the correct position: */
    ofTranslate(pos.x,pos.y,pos.z);

    /* Rotate by the correct amount: */
   // ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
   //model.setPosition(pos_ode[0], pos_ode[1], pos_ode[2]);

    /* Draw the model: */
    m_model.drawFaces();

    /* Restore the transformation matrix: */
    ofPopMatrix();
}
