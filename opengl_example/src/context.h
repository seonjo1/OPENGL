#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

// main의 내용에서 그림을 그리는 렌더링 부분을 분리시키는 클래스
CLASS_PTR(Context)
class Context
{
public:
	static ContextUPtr Create();
	void Render();
private:
	Context() {}
	bool Init();
	ProgramUPtr m_program;

	VertexLayoutUPtr m_vertexLayout;
	BufferUPtr m_vertexBuffer;
	BufferUPtr m_indexBuffer;
	TextureUPtr m_texture;
	TextureUPtr m_texture2;
};

#endif