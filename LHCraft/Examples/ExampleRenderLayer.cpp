#include "ExampleRenderLayer.h"
#include "Core/Debug/Instrumentor.h"

TestLayer::TestLayer()
{
	CORE_PROFILE_FUNCTION();
	m_VertexArray = Core::VertexArray::Create();

	float vertices[4 * 5] = {
		-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -1.0f, 0.0f, 1.0f};

	std::shared_ptr<Core::VertexBuffer> vertexBuffer = Core::VertexBuffer::Create(vertices, sizeof(vertices));
	Core::BufferLayout layout = {
		{Core::ShaderDataType::Float3, "a_Position"},
		{Core::ShaderDataType::Float2, "a_Color"}};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
	std::shared_ptr<Core::IndexBuffer> indexBuffer = Core::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Camera = std::make_unique<Core::ProjectionCamera>(45.0f, 1200.0f / 720.0f, 0.1f, 1000.0f);

	m_Texture = Core::Texture2D::Create("/Users/amyalex/Documents/Production_Projects/LHVoxelEngineV2/LHCraft/assets/awesomeface.png");

	m_Shader = Core::Shader::Create("Core/Shaders/vertex.vs", "Core/Shaders/fragment.fs");

	m_Shader->SetInt("u_Texture", 0);
}

void TestLayer::OnUpdate(Core::TimeStep ts)
{
	CORE_PROFILE_FUNCTION();

	m_Camera->OnUpdate(ts);

	Core::RenderCommands::SetClearColor({0.1, 0.3, 0.9, 1.0});
	Core::RenderCommands::Clear();

	Core::Renderer::BeginScene(*m_Camera);

	m_Texture->Bind();
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			glm::vec3 pos(x, y, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.1f));
			Core::Renderer::Submit(m_Shader, m_VertexArray, transform);
			// CORE_LOG_TRACE("Submitting Vertex for render");
		}
	}
}

void TestLayer::OnEvent(Core::Event &event)
{
	m_Camera->OnEvent(event);
}
