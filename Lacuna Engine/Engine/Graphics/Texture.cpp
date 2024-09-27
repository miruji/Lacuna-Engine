#include "Texture.h"

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > TILE
LE::Texture::Tile::Tile(std::string values)
{
    // convert to const char* for faster processing
    const char* cstr = values.c_str();
    char* endptr;
    // use std::strtof for faster conversion from string to float
    this->x = std::strtof(cstr, &endptr); cstr = endptr + 1;
    this->y = std::strtof(cstr, &endptr); cstr = endptr + 1;
    this->w = std::strtof(cstr, &endptr); cstr = endptr + 1;
    this->h = std::strtof(cstr, nullptr);
}
LE::Texture::Tile::Tile()
{
}
LE::Texture::Tile::~Tile()
{
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > texture
LE::Texture::Texture(std::string name, int w, int h, GLuint pitch, GLuint num)
    : name(std::move(name)), w(w), h(h), pitch(pitch), num(num)
{
}
LE::Texture::Texture()
{
}
LE::Texture::~Texture()
{
}
void LE::Texture::del()
{
    tilemap.clear();
    glDeleteTextures(1, &num);
}
void LE::Texture::rotate(int degree)
{
    if (degree > 360 || degree < -360) return;

    glBindTexture(GL_TEXTURE_2D, num);
    std::unique_ptr<GLubyte[]> pixels(new GLubyte[w * h * 4]);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());

    FIBITMAP* b = FreeImage_ConvertFromRawBits(pixels.get(), w, h, pitch, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);
    FIBITMAP* rotatedImage = FreeImage_Rotate(b, degree);
    FreeImage_Unload(b);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(rotatedImage));

    FreeImage_Unload(rotatedImage);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void LE::Texture::flip(bool axis)
{
    if (axis != 0 && axis != 1) return;

    glBindTexture(GL_TEXTURE_2D, num);
    std::unique_ptr<GLubyte[]> pixels(new GLubyte[w*h*4]);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());

    FIBITMAP* b = FreeImage_ConvertFromRawBits(pixels.get(), w, h, pitch, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

         if (axis == 0) FreeImage_FlipHorizontal(b);
    else if (axis == 1) FreeImage_FlipVertical(b);
    else
    {
        FreeImage_Unload(b);
        glBindTexture(GL_TEXTURE_2D, 0);
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(b));

    FreeImage_Unload(b);
    glBindTexture(GL_TEXTURE_2D, 0);
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > no texture
std::vector<std::string> LE::loadTextures(std::vector<Texture>& textures, const std::vector<std::string>& loadNames, const std::string& loadMode)
{
    std::vector<std::string> result;
    result.reserve(loadNames.size());

    for (const auto& name : loadNames)
    {
        textures.emplace_back(loadTexture(name, loadMode));
        result.emplace_back("i1|"+std::to_string(textures.size()-1) + ": "+name);
    }
    return result;
}
LE::Texture LE::loadTexture(std::string loadName, std::string loadMode)
{
    // TO:DO: if file name lower or upper ?
    std::string Name = noFileType(getFileName(loadName)[0])[0];
    std::string FileType;
    
    // load
    GLuint n;
    int nWidth, nHeight, nPitch;
    {
        FIBITMAP* basic = FreeImage_Load(
            FreeImage_GetFileType(loadName.c_str(), 0),
            loadName.c_str());

        FIBITMAP* rotated = FreeImage_Rotate(basic,180); // rotate
        FreeImage_Unload(basic);
        FreeImage_FlipHorizontal(rotated);               // horizontal

        glGenTextures(1, &n);
        glBindTexture(GL_TEXTURE_2D, n);
        if (loadMode == "Texture")
        {
            nWidth = FreeImage_GetWidth(rotated);
            nHeight = FreeImage_GetHeight(rotated);
            if (nWidth >= 64 || nHeight >= 64)
            {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            else
            {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
        }
        else
        if (loadMode == "Icon")
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
            //float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
            //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        if (loadMode == "Texture")
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else
        if (loadMode == "Icon")
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        }
        
        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(rotated);
        FreeImage_Unload(rotated);
            nWidth = FreeImage_GetWidth(pImage);
            nHeight = FreeImage_GetHeight(pImage);
            nPitch = FreeImage_GetPitch(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, 0x80E1, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        //if (LoadMode == "TEXTURE")
        //{
            glewInit();                         // TO:DO: MIPMAP
            glGenerateMipmap(GL_TEXTURE_2D);    // TO:DO: MIPMAP
        //}

        FreeImage_Unload(pImage);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    return Texture(Name, nWidth, nHeight, nPitch, n);
}
LE::mi LE::searchTexture(const std::vector<Texture>& textures, const std::string& name)
{
    for_er(i, 0, i < textures.size(), i++, textures[i].name == name, i);
    return -1;
}
LE::mi LE::searchTexture(const std::vector<Texture>& textures, const mi& num)
{
    for_er(i, 0, i < textures.size(), i++, textures[i].num == num, static_cast<LE::mi>(i));
    return -1;
}
LE::mi LE::getTextureNum(const std::vector<Texture>& textures, const std::string& name)
{
    for_er(i, 0, i < textures.size(), i++, textures[i].name == name, textures[i].num);
    return -1;
}
LE::mi LE::getTextureNum(const std::vector<Texture>& textures, const mi& num)
{
    const int result = searchTexture(textures, num);
    return (result >= 0) ? textures[result].num : -1;
}