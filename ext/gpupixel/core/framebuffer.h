#pragma once

#include "gpupixel_macros.h"

NS_GPUPIXEL_BEGIN

typedef struct {
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
} TextureAttributes;

class Framebuffer {
public:
    Framebuffer(int width, int height, bool onlyGenerateTexture = false, const TextureAttributes textureAttributes = defaultTextureAttribures);
    ~Framebuffer();

    GLuint getTexture() const { return _texture; }
    GLuint getFramebuffer() const { return _framebuffer; }

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    const TextureAttributes &getTextureAttributes() const { return _textureAttributes; };
    bool hasFramebuffer() { return _hasFB; };

    void active();
    void inactive();

    static TextureAttributes defaultTextureAttribures;

private:
    int _width, _height;
    TextureAttributes _textureAttributes;
    bool _hasFB;
    GLuint _texture;
    GLuint _framebuffer;

    void _generateTexture();
    void _generateFramebuffer();
};

NS_GPUPIXEL_END
