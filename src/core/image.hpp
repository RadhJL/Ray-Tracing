#ifndef __ISICG_ISIR_IMAGE__
#define __ISICG_ISIR_IMAGE__

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <vector>
#include "defines.hpp"

namespace ISICG_ISIR
{
	class ImageJPG
	{
	public:
		ImageJPG(const uint width, const uint height, const uint nbChannels = 3,
				 const uint quality = 100)
			: _width(width), _height(height), _nbChannels(nbChannels),
			  _quality(quality), _pixels(_width*_height * nbChannels)
		{
		}

		uint getWidth() const
		{
			return _width;
		}
		uint getHeight() const
		{
			return _height;
		}

		// color channels should be between 0 and 1
		void setPixel(const uint i, const uint j, const Vec3f &color)
		{
			const uint pixelId = (i + j * _width) * _nbChannels;
			_pixels[pixelId] = uchar(color.r * 255);
			_pixels[pixelId+1] = uchar(color.g * 255);
			_pixels[pixelId+2] = uchar(color.b * 255);
		}

		void save(const std::string &path)
		{
			stbi_write_jpg(path.c_str(), _width, _height, _nbChannels,
						   _pixels.data(), _quality);
		}

	private:
		uint _width;
		uint _height;
		uint _nbChannels;
		uint _quality;

		std::vector<uchar> _pixels;
	};
} 

#endif 
