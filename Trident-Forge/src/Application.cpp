#include "Application.h"
#include <GLFW/glfw3.h>

// Constructor: Initializes the application systems
Application::Application()
{
	Init();
}

// Destructor: Cleans up resources before exit
Application::~Application()
{
	Shutdown();
}

// Main application loop
void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window->GetWindow()))
	{
		// Clear the screen with a black color
		m_Renderer->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Renderer->Clear();

		// Bind shader and vertex array to render the triangle
		m_Shader->Bind();
		m_VertexArray->Bind();
		m_Renderer->DrawIndexed(m_VertexArray); // Issue draw call

		// Render UI (ImGui, overlays, etc.)
		RenderUI();

		// Poll for input and window events
		glfwPollEvents();

		// Swap the front and back buffers
		glfwSwapBuffers(m_Window->GetWindow());
	}
}

// Initialization logic for window, renderer, buffers, and shader
void Application::Init()
{
	// Create and initialize the window
	m_Window = std::make_shared<Engine::WindowsWindow>();
	m_Window->Init();

	// Initialize the rendering system
	m_Renderer = std::make_shared<Engine::Renderer>();
	m_Renderer->Init();

	// Vertex data for a single triangle
	float vertices[] = {
		// Position             // Color (RGBA)
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-left, red
		 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-right, green
		 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f   // Top, blue
	};

	// Index data for triangle
	uint32_t indices[] = { 0, 1, 2 };

	// Create vertex buffer and define its layout
	auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
	Engine::BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "a_Position" },  // Position attribute
		{ Engine::ShaderDataType::Float4, "a_Color" }      // Color attribute
	};
	vertexBuffer->SetLayout(layout);

	// Create index buffer
	auto indexBuffer = Engine::IndexBuffer::Create(indices, 3);

	// Set up vertex array and bind buffers to it
	m_VertexArray = Engine::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	// Load and compile shaders from file
	m_Shader = Engine::Shader::Create("Shaders/Basic.vert", "Shaders/Basic.frag");
}

// Clean up resources
void Application::Shutdown()
{
	m_Window->Shutdown();
}

// Placeholder for user interface rendering (e.g., ImGui)
void Application::RenderUI()
{
	// TODO: Add ImGui or custom UI rendering here
}