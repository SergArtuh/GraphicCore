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
	void Framebuffer::SetTextures2d(const Texture2D& texture, const int location) {
		if (!IsValid()) {
			Init();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, GetId());


		GLenum drawBuffer = GL_COLOR_ATTACHMENT0 + location;

		glBindTexture(GL_TEXTURE_2D, texture.GetId());

		glFramebufferTexture(GL_FRAMEBUFFER, drawBuffer, texture.GetId(), 0);

		GLenum drawBuffers[1] = { drawBuffer };
		glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

		GLenum fbState = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fbState != GL_FRAMEBUFFER_COMPLETE) {
			LOG_WARNING("Fail to attach texture to framebuffer: Err code %d", fbState);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
}
