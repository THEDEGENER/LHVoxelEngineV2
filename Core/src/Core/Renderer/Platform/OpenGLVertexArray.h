#pragma once

#include "Core/Renderer/VertexArray.h"

namespace Core
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() override { return m_IndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		unsigned int m_VertexArrayID;
		unsigned int m_VertexBufferIndex = 0;
	};
}