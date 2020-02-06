#ifndef _ResourceViewer_H_
#define _ResourceViewer_H_

#include "../QwerkE_Common/Libraries/imgui/imgui.h"
#include "../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>
#include <map>
#include <vector>

namespace QwerkE {

    typedef unsigned int ALuint;

    class Resources;
    class ShaderProgram;
    class Scene;
    class GameObject;
    class FrameBufferObject;
    class Mesh;
    class Texture;
    class Material;
    class MaterialEditor;

    class ResourceViewer
    {
    public:
        ResourceViewer();
        ~ResourceViewer();

        void Draw();

    private:
        int m_CurrentResource = 0;

        MaterialEditor* m_MaterialEditor = nullptr;
        bool m_ShowMatEditor = false;
        std::string m_MatName = gc_DefaultStringValue;

        const std::map<std::string, ShaderProgram*>* m_Shaders = nullptr;
        const std::map<std::string, Material*>* m_Materials = nullptr;
        const std::map<std::string, Texture*>* m_Textures = nullptr;
        const std::map<std::string, Mesh*>* m_Meshes = nullptr;
        const std::map<std::string, ALuint>* m_Sounds = nullptr;
        // const std::map<std::string, GLuint>* m_Fonts = nullptr;
        // const std::map<std::string, int>* m_Levels = nullptr;

        // Model viewing
        unsigned char m_ItemsPerRow = 4;
        ImVec2 m_ImageSize = ImVec2(64, 64);

        FrameBufferObject* m_FBO;
        std::vector<GLuint> m_ModelImageHandles;
        void DrawModelThumbnails();

        GameObject* m_Subject = nullptr; // model to draw
        GameObject* m_TagPlane = nullptr; // asset tag plane
        Scene* m_ViewerScene = nullptr;
    };

}
#endif // !_ResourceViewer_H_
