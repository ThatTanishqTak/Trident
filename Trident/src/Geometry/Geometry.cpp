#include "Geometry.h"

#include "Renderer/BufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

#include <cmath>
#include <vector>

namespace Engine
{
    namespace
    {
        struct Geometries
        {
            std::shared_ptr<VertexArray> Cube;
            std::shared_ptr<VertexArray> Sphere;
            std::shared_ptr<VertexArray> Quad;
            std::shared_ptr<VertexArray> Plane;
        } s_Geometries;

        static std::shared_ptr<VertexArray> CreateGeometry(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
        {
            auto vertexBuffer = VertexBuffer::Create(const_cast<float*>(vertices.data()), static_cast<uint32_t>(vertices.size() * sizeof(float)));
            BufferLayout layout =
            { 
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color"},
                {ShaderDataType::Float3, "a_Normal"} 
            };
            vertexBuffer->SetLayout(layout);

            auto indexBuffer =
                IndexBuffer::Create(const_cast<uint32_t*>(indices.data()), static_cast<uint32_t>(indices.size()));

            auto vao = VertexArray::Create();
            vao->AddVertexBuffer(vertexBuffer);
            vao->SetIndexBuffer(indexBuffer);
            
            return vao;
        }

        static void BuildCube()
        {
            if (s_Geometries.Cube)
            {
                return;
            }

            float verts[] =
            {
                // Back face
                -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f, 0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,
                0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f, -0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,
                // Front face
                -0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f,
                0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, -0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f,
                // Left face
                -0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, -1.f, 0.f, 0.f, -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, -1.f, 0.f, 0.f,
                -0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, -1.f, 0.f, 0.f, -0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, -1.f, 0.f, 0.f,
                // Right face
                0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f,
                0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f,
                // Bottom face
                -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f, 0.f, 0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f, 0.f,
                0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f, 0.f, -0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f, 0.f,
                // Top face
                -0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.5f, 0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f,
                0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, -0.5f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f
            };

            uint32_t ind[] =
            { 
                0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,  8,  9,  10, 10, 11, 8,
                12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20 
            };

            std::vector<float> v(std::begin(verts), std::end(verts));
            std::vector<uint32_t> i(std::begin(ind), std::end(ind));
            s_Geometries.Cube = CreateGeometry(v, i);
        }

        static void BuildQuad()
        {
            if (s_Geometries.Quad)
            {
                return;
            }

            float verts[] =
            {
                -0.5f, -0.5f,  0.0f,   1.0f,  0.0f, 0.f, 1.f,  0.f,  0.f, 1.f, 0.5f, -0.5f, 0.f, 0.f,
                 1.0f,  0.0f,  1.0f,   0.0f,  0.0f, 1.f, 0.5f, 0.5f, 0.f, 0.f, 0.f,  1.f,   1.f, 0.f,
                 0.0f,  1.0f, -0.5f,   0.5f,  0.0f, 1.f, 1.f,  1.f,  1.f, 0.f, 0.f,  1.f 
            };

            uint32_t ind[] = { 0, 1, 2, 2, 3, 0 };

            std::vector<float> v(std::begin(verts), std::end(verts));
            std::vector<uint32_t> i(std::begin(ind), std::end(ind));
            s_Geometries.Quad = CreateGeometry(v, i);
        }

        static void BuildPlane()
        {
            if (s_Geometries.Plane)
            {
                return;
            }

            float verts[] =
            { 
                -0.5f, 0.f, -0.5f, 1.f, 0.f,  0.f, 1.f,  0.f, 1.f,  0.f, 0.5f, 0.f, -0.5f, 0.f,
                1.f,   0.f, 1.f,   0.f, 1.f,  0.f, 0.5f, 0.f, 0.5f, 0.f, 0.f,  1.f, 1.f,   0.f,
                1.f,   0.f, -0.5f, 0.f, 0.5f, 1.f, 1.f,  1.f, 1.f,  0.f, 1.f,  0.f
            };

            uint32_t ind[] = { 0, 1, 2, 2, 3, 0 };

            std::vector<float> v(std::begin(verts), std::end(verts));
            std::vector<uint32_t> i(std::begin(ind), std::end(ind));
            s_Geometries.Plane = CreateGeometry(v, i);
        }

        static void BuildSphere()
        {
            if (s_Geometries.Sphere)
            {
                return;
            }

            const unsigned int segments = 20;
            const unsigned int rings = 20;
            
            std::vector<float> vertices;
            std::vector<uint32_t> indices;

            for (unsigned int y = 0; y <= rings; ++y)
            {
                for (unsigned int x = 0; x <= segments; ++x)
                {
                    float xSegment = static_cast<float>(x) / segments;
                    float ySegment = static_cast<float>(y) / rings;
                    float xPos = std::cos(xSegment * 2.0f * static_cast<float>(3.14159265358979323846f)) * std::sin(ySegment * static_cast<float>(3.14159265358979323846f));
                    float yPos = std::cos(ySegment * static_cast<float>(3.14159265358979323846f));
                    float zPos = std::sin(xSegment * 2.0f * static_cast<float>(3.14159265358979323846f)) * std::sin(ySegment * static_cast<float>(3.14159265358979323846f));

                    vertices.push_back(xPos);
                    vertices.push_back(yPos);
                    vertices.push_back(zPos);
                    vertices.push_back(1.f);
                    vertices.push_back(1.f);
                    vertices.push_back(1.f);
                    vertices.push_back(1.f);
                    vertices.push_back(xPos);
                    vertices.push_back(yPos);
                    vertices.push_back(zPos);
                }
            }

            bool oddRow = false;
            for (unsigned int y = 0; y < rings; ++y)
            {
                if (!oddRow)
                {
                    for (unsigned int x = 0; x <= segments; ++x)
                    {
                        indices.push_back(y * (segments + 1) + x);
                        indices.push_back((y + 1) * (segments + 1) + x);
                    }
                }
                else
                {
                    for (int x = segments; x >= 0; --x)
                    {
                        indices.push_back((y + 1) * (segments + 1) + x);
                        indices.push_back(y * (segments + 1) + x);
                    }
                }
                oddRow = !oddRow;
            }

            s_Geometries.Sphere = CreateGeometry(vertices, indices);
        }
    }

    const std::shared_ptr<VertexArray>& Geometry::GetCube()
    {
        BuildCube();
        
        return s_Geometries.Cube;
    }

    const std::shared_ptr<VertexArray>& Geometry::GetSphere()
    {
        BuildSphere();
        
        return s_Geometries.Sphere;
    }

    const std::shared_ptr<VertexArray>& Geometry::GetQuad()
    {
        BuildQuad();
        
        return s_Geometries.Quad;
    }

    const std::shared_ptr<VertexArray>& Geometry::GetPlane()
    {
        BuildPlane();
        
        return s_Geometries.Plane;
    }

    void Geometry::Shutdown()
    {
        s_Geometries.Cube.reset();
        s_Geometries.Sphere.reset();
        s_Geometries.Quad.reset();
        s_Geometries.Plane.reset();
    }
}