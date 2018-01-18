#include "qtopengl_psiswarm.h"
#include "psiswarm_entity.h"
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

namespace argos
{
    static const UInt8 PSISWARM_COMPONENTS_NUMBER = 2;

    CQTOpenGLPsiSwarm::CQTOpenGLPsiSwarm():
            m_unVertices(40)
    {
        // Reserve the needed display lists
        m_unLists = glGenLists(PSISWARM_COMPONENTS_NUMBER);

        // Assign indices for better referencing (later)
        m_unWheelList = m_unLists;
        m_unBodyList  = m_unLists + 1;

        // Create the wheel display list
        glNewList(m_unWheelList, GL_COMPILE);
        RenderWheel();
        glEndList();

        // Create the body display list
        glNewList(m_unBodyList, GL_COMPILE);
        RenderBody();
        glEndList();
    }

    CQTOpenGLPsiSwarm::~CQTOpenGLPsiSwarm()
    {
        glDeleteLists(m_unLists, PSISWARM_COMPONENTS_NUMBER);
    }

    void CQTOpenGLPsiSwarm::Draw(CPsiSwarmEntity& c_entity)
    {
        // Place the body
        glCallList(m_unBodyList);

        // Place the wheels
        glPushMatrix();
        glTranslatef(0.0f, CPsiSwarmEntity::HALF_INTERWHEEL_DISTANCE, 0.0f);
        glCallList(m_unWheelList);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, -CPsiSwarmEntity::HALF_INTERWHEEL_DISTANCE, 0.0f);
        glCallList(m_unWheelList);
        glPopMatrix();
    }

    // TODO: Merge these three functions into one that takes material attributes as arguments?
    void CQTOpenGLPsiSwarm::SetWhitePlasticMaterial()
    {
        const GLfloat pfColor[]     = {   1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
        const GLfloat pfShininess[] = { 100.0f                   };
        const GLfloat pfEmission[]  = {   1.0f, 1.0f, 1.0f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
    }

    void CQTOpenGLPsiSwarm::SetGrayPlasticMaterial()
    {
        const GLfloat pfColor[]     = {   0.5f, 0.5f, 0.5f, 0.6f };
        const GLfloat pfSpecular[]  = {   0.1f, 0.1f, 0.1f, 1.0f };
        const GLfloat pfShininess[] = { 20.0f                    };
        const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
    }

    void CQTOpenGLPsiSwarm::SetBlackPlasticMaterial()
    {
        const GLfloat pfColor[]     = {   0.0f, 0.0f, 0.0f, 0.6f };
        const GLfloat pfSpecular[]  = {   0.1f, 0.1f, 0.1f, 1.0f };
        const GLfloat pfShininess[] = { 20.0f                    };
        const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
    }

    void CQTOpenGLPsiSwarm::RenderWheel()
    {
        // Set material
        SetBlackPlasticMaterial();

        // Right side
        CVector2 cVertex(CPsiSwarmEntity::WHEEL_RADIUS, 0.0f);
        CRadians cAngle(CRadians::TWO_PI / m_unVertices);
        CVector3 cNormal(-1.0f, -1.0f, 0.0f);
        cNormal.Normalize();
        glBegin(GL_POLYGON);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cVertex.GetX(), -CPsiSwarmEntity::HALF_WHEEL_WIDTH, CPsiSwarmEntity::WHEEL_RADIUS + cVertex.GetY());
            cVertex.Rotate(cAngle);
            cNormal.RotateY(cAngle);
        }

        glEnd();

        // Left side
        cVertex.Set(CPsiSwarmEntity::WHEEL_RADIUS, 0.0f);
        cNormal.Set(-1.0f, 1.0f, 0.0f);
        cNormal.Normalize();
        cAngle = -cAngle;
        glBegin(GL_POLYGON);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cVertex.GetX(), CPsiSwarmEntity::HALF_WHEEL_WIDTH, CPsiSwarmEntity::WHEEL_RADIUS + cVertex.GetY());
            cVertex.Rotate(cAngle);
            cNormal.RotateY(cAngle);
        }

        glEnd();

        // Tyre
        cNormal.Set(1.0f, 0.0f, 0.0f);
        cVertex.Set(CPsiSwarmEntity::WHEEL_RADIUS, 0.0f);
        cAngle = -cAngle;
        glBegin(GL_QUAD_STRIP);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
            glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
            glVertex3f(cVertex.GetX(), -CPsiSwarmEntity::HALF_WHEEL_WIDTH, CPsiSwarmEntity::WHEEL_RADIUS + cVertex.GetY());
            glVertex3f(cVertex.GetX(),  CPsiSwarmEntity::HALF_WHEEL_WIDTH, CPsiSwarmEntity::WHEEL_RADIUS + cVertex.GetY());
            cVertex.Rotate(cAngle);
            cNormal.RotateY(cAngle);
        }

        glEnd();
    }

    void CQTOpenGLPsiSwarm::RenderBody()
    {
        // Set material
        SetGrayPlasticMaterial();
        CVector2 cVertex(CPsiSwarmEntity::BODY_RADIUS, 0.0f);
        CRadians cAngle(-CRadians::TWO_PI / m_unVertices);

        // Bottom part
        glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, -1.0f);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
             glVertex3f(cVertex.GetX(), cVertex.GetY(), CPsiSwarmEntity::BODY_ELEVATION);
             cVertex.Rotate(cAngle);
        }

        glEnd();

        // Side surface
        cAngle = -cAngle;
        CVector2 cNormal(1.0f, 0.0f);
        cVertex.Set(CPsiSwarmEntity::BODY_RADIUS, 0.0f);
        glBegin(GL_QUAD_STRIP);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
            glNormal3f(cNormal.GetX(), cNormal.GetY(), 0.0f);
            glVertex3f(cVertex.GetX(), cVertex.GetY(), CPsiSwarmEntity::BODY_ELEVATION + CPsiSwarmEntity::BODY_HEIGHT);
            glVertex3f(cVertex.GetX(), cVertex.GetY(), CPsiSwarmEntity::BODY_ELEVATION);
            cVertex.Rotate(cAngle);
            cNormal.Rotate(cAngle);
        }

        glEnd();

        // Top part
        glBegin(GL_POLYGON);
        cVertex.Set(CPsiSwarmEntity::BODY_RADIUS, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);

        for(GLuint i = 0; i <= m_unVertices; i++)
        {
            glVertex3f(cVertex.GetX(), cVertex.GetY(), CPsiSwarmEntity::BODY_ELEVATION + CPsiSwarmEntity::BODY_HEIGHT);
            cVertex.Rotate(cAngle);
        }

        glEnd();

        // Triangle to set the direction
        SetWhitePlasticMaterial();
        glBegin(GL_TRIANGLES);

        glVertex3f(CPsiSwarmEntity::BODY_RADIUS * 0.7,
                   0.0f,
                   CPsiSwarmEntity::BODY_ELEVATION + CPsiSwarmEntity::BODY_HEIGHT + 0.001f);

        glVertex3f(-CPsiSwarmEntity::BODY_RADIUS * 0.7,
                   CPsiSwarmEntity::BODY_RADIUS * 0.4,
                   CPsiSwarmEntity::BODY_ELEVATION + CPsiSwarmEntity::BODY_HEIGHT + 0.001f);

        glVertex3f(-CPsiSwarmEntity::BODY_RADIUS * 0.7,
                   -CPsiSwarmEntity::BODY_RADIUS * 0.4,
                   CPsiSwarmEntity::BODY_ELEVATION + CPsiSwarmEntity::BODY_HEIGHT + 0.001f);

        glEnd();
    }

    class CQTOpenGLOperationDrawPsiSwarmNormal : public CQTOpenGLOperationDrawNormal
    {
    public:

        void ApplyTo(CQTOpenGLWidget& c_visualization, CPsiSwarmEntity& c_entity)
        {
            static CQTOpenGLPsiSwarm m_cModel;
            c_visualization.DrawRays(c_entity.GetControllableEntity());
            c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
            m_cModel.Draw(c_entity);
        }
    };

    class CQTOpenGLOperationDrawPsiSwarmSelected : public CQTOpenGLOperationDrawSelected
    {
    public:

        void ApplyTo(CQTOpenGLWidget& c_visualization, CPsiSwarmEntity& c_entity)
        {
            c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
        }
    };

    REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawPsiSwarmNormal, CPsiSwarmEntity);

    REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawPsiSwarmSelected, CPsiSwarmEntity);
}
