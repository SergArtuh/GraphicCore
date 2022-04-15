#include "Framebuffer.h"

#include "Texture2d.h"
#include "helper.h"


#include "common/Logger.h"

namespace llr
{
	Framebuffer::~Framebuffer() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_bufferId != UNUSED) {
			Denit();
		}
	}
	Framebuffer::Framebuffer(const Framebuffer& r) : m_bufferId(r.m_bufferId) {
		m_referenceCounter.Increase();
	}
	Framebuffer& Framebuffer::operator=(const Framebuffer& r) {
		m_referenceCounter.Increase();

		m_bufferId = r.m_bufferId;
		m_referenceCounter = r.m_referenceCounter;

		return *this;
	}

	Framebuffer Framebuffer::MakeDefault()
	{
		Framebuffer fb;
		fb.m_bufferId = 0;
		return fb;
	}

	void Framebuffer::Init() {
		glGenFramebuffers(1, &m_bufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_bufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Framebuffer::Denit() {
		glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;
	}


	void Framebuffer::Clear() {
		glBindFramebuffer(GL_FRAMEBUFFER, GetId());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, GetId());
	}

	void Framebuffer::Update() {
		if (!IsValid()) {
			Init();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, GetId());

		std::vector<GLenum> drawBuffers;

		for (auto tex : m_textures2d) {
			GLenum drawbufferId = GL_COLOR_ATTACHMENT0 + tex.first;
			glFramebufferTexture(GL_FRAMEBUFFER, drawbufferId, tex.second.GetId(), 0);
			drawBuffers.push_back(drawbufferId);
		}

		glDrawBuffers(drawBuffers.size(), drawBuffers.data());

		GLenum fbState = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fbState != GL_FRAMEBUFFER_COMPLETE) {
			LOG_WARNING("Fail to attach texture to framebuffer: Err code %d", fbState);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::SetTextures2d(const Texture2D& texture, CI32 location) {
		m_textures2d.emplace(location, texture);
		Update();
	}
}
