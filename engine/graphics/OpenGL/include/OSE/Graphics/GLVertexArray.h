#pragma once

#include "OSE/Graphics/GLVertexLayout.h"
#include "OSE/Graphics/GLBuffer.h"

#include <OSE/Graphics/GraphicsResource.h>
#include <OSE/TypeDefs.h>

#include <memory>
#include <unordered_map>

namespace OSE {

    class GLVertexArray : public GraphicsResource<ResourceType::VertexLayout>
    {
        struct GLVertexArrayObject
        {
            uint handle{ 0 };

            GLVertexArrayObject();
            ~GLVertexArrayObject();
        };

        GLVertexLayout m_Layout;
        std::unordered_map<int64, std::unique_ptr<GLVertexArrayObject>> m_VAOs;

        int64 GetVAOHandle(const GLBuffer& vbo, const GLBuffer* ibo);

        size_t BindInternal(const GLBuffer& vbo, const GLBuffer* ibo, size_t count);
        void MakeVAOInternal(const GLBuffer& vbo, const GLBuffer* ibo);

        void BindVerbose(const GLBuffer& vbo, const GLBuffer* ibo);

    public:
        GLVertexArray(const GLVertexLayout& layout);
        ~GLVertexArray();

        void MakeVAO(const GLBuffer& vbo);
        void MakeVAO(const GLBuffer& vbo, const GLBuffer& ibo);

        size_t Bind(const GLBuffer& vbo);
        size_t BindIndexed(const GLBuffer& vbo, const GLBuffer& ibo);

        void Dispose() override;
    };

}