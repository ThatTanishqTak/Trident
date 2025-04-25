#include "Application.h"
#include <GLFW/glfw3.h>

// Define static singleton instance
Application* Application::s_Instance = nullptr;

// Constructor: Initializes the application systems
Application::Application()
{
	s_Instance = this;

	Init();
}

// Destructor: Cleans up resources before exit
Application::~Application()
{
	Shutdown();
	s_Instance = nullptr;
}

// Returns the singleton instance
Application& Application::Get()
{
	return *s_Instance;
}

// Main application loop
void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window->GetWindow()))
	{
		Engine::Time::Update();

		m_Renderer->SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		m_Renderer->Clear();

		m_Shader->Bind();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 viewProj = m_Camera->GetViewProjectionMatrix();

		m_Shader->SetUniformMat4("u_Model", model);
		m_Shader->SetUniformMat4("u_ViewProjection", viewProj);

		m_VertexArray->Bind();
		m_Renderer->DrawIndexed(m_VertexArray);

		RenderUI();
		m_CameraController->OnUpdate(Engine::Time::GetDeltaTime());

		glfwPollEvents();
		glfwSwapBuffers(m_Window->GetWindow());
	}
}

// Initialization logic for window, renderer, buffers, and shader
void Application::Init()
{
	Engine::Time::Init();

	m_Window = std::make_shared<Engine::WindowsWindow>();
	m_Window->Init();

	m_Renderer = std::make_shared<Engine::Renderer>();
	m_Renderer->Init();

	m_CameraController = std::make_shared<Engine::CameraController>(1920.0f / 1080.0f);
	m_Camera = std::make_unique<Engine::PerspectiveCamera>(m_CameraController->GetCamera());

	m_ImGuiLayer = std::make_unique<Engine::ImGuiLayer>();
	m_ImGuiLayer->Init(m_Window->GetWindow());

	float vertices[] = {
		// Positions           // Colors (RGBA)
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.5f, 0.5f, 0.5f, 1.0f,
	};

	uint32_t indices[] = {
		0, 1, 2, 2, 3, 0,     // Back face
		4, 5, 6, 6, 7, 4,     // Front face
		4, 5, 1, 1, 0, 4,     // Bottom face
		7, 6, 2, 2, 3, 7,     // Top face
		4, 0, 3, 3, 7, 4,     // Left face
		5, 1, 2, 2, 6, 5      // Right face
	};

	auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
	Engine::BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "a_Position" },
		{ Engine::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);

	auto indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VertexArray = Engine::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = Engine::Shader::Create("Shaders/Basic.vert", "Shaders/Basic.frag");
}

// Clean up resources
void Application::Shutdown()
{
	m_Shader->Unbind();
	m_VertexArray->Unbind();

	m_ImGuiLayer->Shutdown();
	m_Window->Shutdown();
}

void Application::RenderUI()
{
	m_ImGuiLayer->Begin();

	ImGui::Begin("Hello from Trident");
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();

	m_ImGuiLayer->End();
}