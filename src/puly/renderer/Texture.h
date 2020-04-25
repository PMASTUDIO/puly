#pragma once

#include <memory>
#include <string>

class OpenGLTexture2D;

namespace Puly {
	
	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t Bind(uint32_t slot = 0) const = 0;

	};

	class Texture2D {
	public:
		static std::shared_ptr<Texture> Create(std::string path);
	};
}