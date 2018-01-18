#ifndef QTOPENGL_PSISWARM_H
#define QTOPENGL_PSISWARM_H

namespace argos
{
    class CQTOpenGLPsiSwarm;
    class CPsiSwarmEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos
{
    class CQTOpenGLPsiSwarm
    {
    public:

        CQTOpenGLPsiSwarm();
        virtual ~CQTOpenGLPsiSwarm();

        virtual void Draw(CPsiSwarmEntity& c_entity);

    protected:

        void SetWhitePlasticMaterial();
        void SetGrayPlasticMaterial();
        void SetBlackPlasticMaterial();

        void RenderWheel();
        void RenderBody();

    private:

        GLuint m_unLists; // Start of the display list index
        GLuint m_unWheelList; // Wheel display list
        GLuint m_unBodyList; // Body display list
        GLuint m_unVertices; // Number of vertices to use for round objects (e.g. wheels)
    };
}

#endif
