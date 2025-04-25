#include "Application.h"

Application::Application()
{
    Init(); // Initialize the application
}

Application::~Application()
{
    Shutdown(); // Clean up resources
}

void Application::Run()
{
    // Main loop runs while the window is open
    while (!glfwWindowShouldClose(m_Window.GetWindow()))
    {
        // Set background color and clear
        m_Renderer->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        m_Renderer->Clear();

        m_Shader->Bind();
        m_VertexArray->Bind();

        // Render scene
        m_Renderer->DrawIndexed(m_VertexArray);

        // Render userinterface
        RenderUI();

        // Poll for and process events
        glfwPollEvents();

        // Swap front and back buffers
        glfwSwapBuffers(m_Window.GetWindow());
    }
}

void Application::Init()
{
    m_Window.Init();
    
    m_Renderer = std::make_shared<Engine::Renderer>();
    m_Renderer->Init();

    float vertices[] = {
        // Position         // Color
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
    Engine::BufferLayout layout = {
        { Engine::ShaderDataType::Float3, "a_Position" },
        { Engine::ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->SetLayout(layout);

    auto indexBuffer = Engine::IndexBuffer::Create(indices, 3);

    m_VertexArray = Engine::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // Load shaders from files
    m_Shader = Engine::Shader::Create("Shaders/Basic.vert", "Shaders/Basic.frag");
}

void Application::Shutdown()
{
    m_Window.Shutdown(); // Clean up the window
}

void Application::RenderUI()
{
    // Here goes ImGui code
}