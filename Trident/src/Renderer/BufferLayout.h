#pragma once

#include "Renderer/ShaderDataType.h"
#include <string>
#include <vector>

namespace Engine
{
    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;
                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;
                case ShaderDataType::Bool: return 1;
            }

            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout()
        {

        }

        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator Begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator End() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator Begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator End() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;

            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;

                m_Stride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };
}