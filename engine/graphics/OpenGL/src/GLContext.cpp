#include "OSE/Graphics/GLContext.h"

namespace OSE {

    template<class R>
    GLContext::Resources<R>::Resources(int32 maxSize) : m_MaxSize{ maxSize }, m_Data{ maxSize }
    {
    }

    //template<class R>
    //R* GLContext::Resources<R>::Retrieve(int32 index) const
    //{
    //    if (index >= 0 && index < m_MaxSize)
    //        return m_Data[index].get();

    //    return nullptr;
    //}

    template<class R>
    bool GLContext::Resources<R>::HasNext() const
    {
        return m_NextIndex < m_MaxSize;
    }

    template<class R>
    int32 GLContext::Resources<R>::PutNext(GLContext::Resources<R>::RUPtr resource)
    {
        int32 putIndex = m_NextIndex;
        m_Data[putIndex] = std::move(resource);

        do
            m_NextIndex++;
        while (m_NextIndex < m_MaxSize && m_Data[m_NextIndex] != nullptr);

        return putIndex;
    }

    template<class R>
    void GLContext::Resources<R>::Remove(int32 index)
    {
        m_Data[index] = nullptr;
        if (index < m_NextIndex)
            m_NextIndex = index;
    }

    template<class R>
    void GLContext::Resources<R>::Clear()
    {
        m_Data.clear();
        m_MaxSize = 0;
        m_NextIndex = 0;
    }

    ProgramHandle GLContext::Create(const std::vector<ShaderDescriptor>& shaderDescriptors)
    {
        ProgramHandle handle = ProgramHandle::Invalid;
        if (m_ProgramResources.HasNext())
        {
            std::unique_ptr<GLProgram> program = GLProgram::Create(shaderDescriptors);
            GLProgram& programRef = *program;

            int32 index = m_ProgramResources.PutNext(std::move(program));
            handle = ProgramHandle{ index };
            programRef.rid = handle;
        }

        return handle;
    }

    void GLContext::Dispose(ProgramHandle handle)
    {
        if (handle)
            m_ProgramResources.Remove(handle.GetID());
    }

    BufferHandle GLContext::Create(BufferType type, const BufferDescriptor& desc, BufferDataDescriptor* dataDesc)
    {
        BufferHandle handle = BufferHandle::Invalid;
        if (m_BufferResources.HasNext())
        {
            std::unique_ptr<GLBuffer> buffer = std::unique_ptr<GLBuffer>{ new GLBuffer{ type, desc.size, desc.byteSize, desc.isStatic } };
            GLBuffer& bufferRef = *buffer;

            if (dataDesc)
            {
                buffer->Bind();
                buffer->Write(dataDesc->data, dataDesc->length, dataDesc->offset, dataDesc->discardAll);
                GLBuffer::Unbind(*buffer);
            }

            int32 index = m_BufferResources.PutNext(std::move(buffer));
            handle = BufferHandle{ index };
            bufferRef.rid = handle;
        }

        return handle;
    }

    void GLContext::Dispose(BufferHandle handle)
    {
        if (handle)
            m_BufferResources.Remove(handle.GetID());
    }

    VertexLayoutHandle GLContext::Create(const std::vector<VertexAttributeDescriptor>& attributeDescriptors)
    {
        VertexLayoutHandle handle = VertexLayoutHandle::Invalid;
        if (m_VertexArrayResources.HasNext())
        {
            GLVertexLayout layout{ attributeDescriptors };
            std::unique_ptr<GLVertexArray> vertArray = std::unique_ptr<GLVertexArray>{ new GLVertexArray{ layout } };
            GLVertexArray& vertArrayRef = *vertArray;

            int32 index = m_VertexArrayResources.PutNext(std::move(vertArray));
            handle = VertexLayoutHandle{ index };
            vertArrayRef.rid = handle;
        }

        return handle;
    }

    void GLContext::Dispose(VertexLayoutHandle handle)
    {
        if (handle)
            m_VertexArrayResources.Remove(handle.GetID());
    }

    GLContext::GLContext():
        m_ProgramResources{ 50 }, m_BufferResources{ 500 }, m_VertexArrayResources{ 50 }
    {

    }

    void GLContext::Terminate()
    {
        m_ProgramResources.Clear();
        m_BufferResources.Clear();
        m_VertexArrayResources.Clear();
    }
}