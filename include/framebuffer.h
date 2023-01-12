#pragma once

#include <vector>
#include <glad/glad.h>

#include "texture.h"

class Framebuffer {
public:
	Framebuffer() {
		glGenFramebuffers(1, &_handle);
	}

	Framebuffer(const Framebuffer&) = delete;

	Framebuffer(Framebuffer&& rhs) noexcept {
		_handle = rhs._handle;
		rhs._handle = 0;
	}

	~Framebuffer() {
		if (_handle != 0) {
			glDeleteFramebuffers(1, &_handle);
			_handle = 0;
		}
	}

	void bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, _handle);
	}

	static void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void attachTexture(const Texture& texture, GLenum attachment, int level = 0) const {
        bind();
		glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture.getHandle(), level);
        unbind();
	}

	void attachTexture2D(const Texture& texture, GLenum attachment, GLenum textarget, int level = 0) const {
        bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER,
			attachment, textarget, texture.getHandle(), level);
        unbind();
	}

	static void checkStatus() {
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	static void drawBuffer(GLenum buffer) {
		glDrawBuffer(buffer);
	}

	static void drawBuffers(const std::vector<GLenum>& buffers) {
		glDrawBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
	}

	static void readBuffer(GLenum buffer) {
		glReadBuffer(buffer);
	}

private:
	GLuint _handle{};
};