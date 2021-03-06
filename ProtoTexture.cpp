/*!  \brief  ProtoProtoTexture.cpp: 2D texture class with w,h fields
 ProtoProtoTexture.cpp
 Protobyte Library v02
 
 Created by Ira Greenberg on 7/23/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is templated to allow for varied single collection types
 This class is part of the group common (update)
 Inspiration and assistance from: http://subversion.assembla.com/svn/184/src/LoadImage.cpp, http://www.opengl.org/discussion_boards/showthread.php/168864-HeightMap-to-NormalMap (Stephen A)
 \sa NO LINK
 */

#include "ProtoTexture.h"



std::ostream& operator<<(std::ostream& output, const ProtoTexture& texture) {
    output << "texture2.textureMapImage: " << texture.textureMapImage <<
    ", texture2.w: " << texture.w <<
    ", texture2.h: " << texture.h <<
    ", texture2.textureID: " << texture.textureID;
    return output;
}


ProtoTexture::ProtoTexture() {}

// main cstr
ProtoTexture::ProtoTexture(const std::string& textureMapImage, TextureMapType textureMapType, GLenum image_format, GLint internal_format, GLint level, GLint border) :
textureMapImage(textureMapImage), textureMapType(textureMapType), image_format(image_format), internal_format(internal_format), level(level), border(border) {

    init();
}


bool ProtoTexture::init() {
    // ensure iamge name
    if (textureMapImage != "") {
       
        std::string textureURL = textureMapImage;
    
        // initialize some locals
        //image format
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        //pointer to the image, once loaded
        FIBITMAP* dib(0);
        //pointer to the image data
        BYTE* imageData(0);
        //image width and height
        unsigned int width(0), height(0);
        
        //check the file signature and deduce its format
        const char* fileURL = textureURL.c_str();
        
        switch (textureMapType){
            case DIFFUSE_MAP:
                glGenTextures(1, &textureID);
                // bind the texture
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureID);
                
                fif = FreeImage_GetFileType(fileURL, 0);
                //if still unknown, try to guess the file format from the file extension
                if (fif == FIF_UNKNOWN)
                    fif = FreeImage_GetFIFFromFilename(fileURL);
                //if still unkown, return failure
                if (fif == FIF_UNKNOWN)
                    return false;
                
                //check that the plugin has reading capabilities and load the file
                if (FreeImage_FIFSupportsReading(fif))
                    dib = FreeImage_Load(fif, fileURL);
                //if the image failed to load, return failure
                if (!dib)
                    return false;
                
                //retrieve the image data
                imageData = FreeImage_GetBits(dib);
                //get the image width and height
                width = FreeImage_GetWidth(dib);
                height = FreeImage_GetHeight(dib);
                
                //std::cout << "image width = " << width << std::endl;
                //std::cout << "image height = " << height << std::endl;
                //if this somehow one of these failed (they shouldn't), return failure
                if ((imageData == 0) || (width == 0) || (height == 0))
                    return false;
                
                
                // texture creation/loading code from:
                // http://www.nullterminator.net/gltexture.html
                
                
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                
            
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                
                //Free FreeImage's copy of the data
                FreeImage_Unload(dib);
                
                break; // end Diffuse Map
                // load existing normal map
            case NORMAL_MAP:
                glGenTextures(1, &textureID);
                // bind the texture
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textureID);
                
                fif = FreeImage_GetFileType(fileURL, 0);
                //if still unknown, try to guess the file format from the file extension
                if (fif == FIF_UNKNOWN)
                    fif = FreeImage_GetFIFFromFilename(fileURL);
                //if still unkown, return failure
                if (fif == FIF_UNKNOWN)
                    return false;
                
                //check that the plugin has reading capabilities and load the file
                if (FreeImage_FIFSupportsReading(fif))
                    dib = FreeImage_Load(fif, fileURL);
                //if the image failed to load, return failure
                if (!dib)
                    return false;
                
                //retrieve the image data
                imageData = FreeImage_GetBits(dib);
                //get the image width and height
                width = FreeImage_GetWidth(dib);
                height = FreeImage_GetHeight(dib);
                
                //std::cout << "image width = " << width << std::endl;
                //std::cout << "image height = " << height << std::endl;
                //if this somehow one of these failed (they shouldn't), return failure
                if ((imageData == 0) || (width == 0) || (height == 0))
                    return false;
                
                
                // texture creation/loading code from:
                // http://www.nullterminator.net/gltexture.html
                

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                
                //std::cout << "texture width =" << width << std::endl;
                // give opengl the texture
                // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                
                //Free FreeImage's copy of the data
                FreeImage_Unload(dib);
                
                break; // end Normal Map
                // dynamically generate Normal Map
            case BUMP_MAP:
                glGenTextures(1, &textureID);
                // bind the texture
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textureID);
                
                fif = FreeImage_GetFileType(fileURL, 0);
                //if still unknown, try to guess the file format from the file extension
                if (fif == FIF_UNKNOWN)
                    fif = FreeImage_GetFIFFromFilename(fileURL);
                //if still unkown, return failure
                if (fif == FIF_UNKNOWN)
                    return false;
                
                //check that the plugin has reading capabilities and load the file
                if (FreeImage_FIFSupportsReading(fif))
                    dib = FreeImage_Load(fif, fileURL);
                //if the image failed to load, return failure
                if (!dib)
                    return false;
                
                
                // get grayscale values(aka height map)
                unsigned width = FreeImage_GetWidth(dib);
                unsigned height = FreeImage_GetHeight(dib);
                float* greyVals = new float[width*height]; // rmember to clean up (near line 400)
                
                //manual conversion to greyscale
                for (int i = 0; i < height; ++i){
                    for (int j = 0; j < width; ++j){
                        RGBQUAD col;
                        FreeImage_GetPixelColor(dib, j, i, &col);
                        float r = col.rgbRed;
                        float g = col.rgbGreen;
                        float b = col.rgbBlue;
                        greyVals[i*width + j] = (r*.21 + g*.72 + b*.07) / 255.0f;
                        
                        //greyVals[i*width + j] = (r+g+b)/3 / 255.0;
                        
                    }
                }
                
                FreeImage_Unload(dib);
                
                // eventually create other operator options
                int sobelX[] = {
                    -1, 0, 1,
                    -2, 0, 2,
                    -1, 0, 1
                };
                int sobelY[] = {
                    -1, -2, -1,
                    0, 0, 0,
                    1, 2, 1
                };
                
                // smoother <-  .5  -> bumpier - eventually obviously paramerterize
                float bumpinessFactor = .975;
                
                // allocate for normal map
                FIBITMAP* normalMap = FreeImage_Allocate(width, height, 24);
                
                int TL, T, TR,
                L, C, R,
                BL, B, BR;
                RGBQUAD color;
                
                for (int i = 0, k = 0; i < height; ++i){
                    for (int j = 0; j < width; ++j){
                        int iMin, iMax, jMin, jMax;
                        // within edge safety limit
                        //if (i>0 && i<height - 1 && j>0 && j < width - 1){
                        iMin = i - 1;
                        iMax = i + 1;
                        jMin = j - 1;
                        jMax = j + 1;
                        //}
                        
                        if (i == 0){ // top edge
                            iMin = height - 1;
                        }
                        else if (i == height - 1){ // bottom edge
                            iMax = 0;
                        }
                        
                        if (j == 0){ // left edge
                            jMin = width - 1;
                        }
                        else if (j == width - 1){ // right edge
                            jMax = 0;
                        }
                        
                        TL = iMin*width + jMin; // TL
                        T = iMin*width + j; // T
                        TR = iMin*width + jMax; // TR
                        
                        L = i*width + jMin; // L
                        C = i*width + j; // current
                        R = i*width + jMax; // R
                        
                        BL = iMax*width + jMin; // BL
                        B = iMax*width + j; // B
                        BR = iMax*width + jMax; // BR
                        
                        float x = greyVals[TL] * sobelX[0] + greyVals[T] * sobelX[1] + greyVals[TR] * sobelX[2] + // Tp
                        greyVals[L] * sobelX[3] + greyVals[C] * sobelX[4] + greyVals[R] * sobelX[5] + // Mdl
                        greyVals[BL] * sobelX[6] + greyVals[B] * sobelX[7] + greyVals[BR] * sobelX[8]; // Btm
                        
                        
                        float y = greyVals[TL] * sobelY[0] + greyVals[T] * sobelY[1] + greyVals[TR] * sobelY[2] +
                        greyVals[L] * sobelY[3] + greyVals[C] * sobelY[4] + greyVals[R] * sobelY[5] +
                        greyVals[BL] * sobelY[6] + greyVals[B] * sobelY[7] + greyVals[BR] * sobelY[8];
                        //sqrt(1-(cx*cx+cy*cy))
                        float z = 1.0 / (bumpinessFactor * (1 + pow(2, 1)));
                        
                        //Vec3f v(x * 2, y * 2, z);
                        
                        glm::vec3 v(x, y, z /*1.0f / bumpinessFactor*/);
                        //v.normalize();
                        v = glm::normalize(v);
                        color.rgbRed = (v.x * 0.5f + .5f) * 255;
                        color.rgbGreen = (v.y * 0.5f + .5f) * 255;
                        color.rgbBlue = (v.z * 0.5f + .5f) * 255;
                        /*					if (i < 10 && j < 5) {
                         trace("v.x * 0.5f + .5f =", v.x * 0.5f + .5f);
                         trace("v.y * 0.5f + .5f =", v.y * 0.5f + .5f);
                         trace("v.z * 0.5f + .5f =", v.z * 0.5f + .5f);
                         }*/
                        FreeImage_SetPixelColor(normalMap, j, i, &color);
                    }
                }
                
                delete[] greyVals;
                
                //
                
                // retrieve the image data
                BYTE* normalMapData = FreeImage_GetBits(normalMap);
                
                // check this all actually worked
                //get the image width and height
                width = FreeImage_GetWidth(normalMap);
                height = FreeImage_GetHeight(normalMap);
                
                //if this somehow one of these failed (they shouldn't), return failure
                if ((normalMapData == 0) || (width == 0) || (height == 0))
                    return false;
                
                // if wrap is true, the texture wraps over at the edges (repeat)
                //       ... false, the texture ends at the edges (clamp)
                /*	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                 isWrap ? GL_REPEAT : GL_CLAMP);
                 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                 isWrap ? GL_REPEAT : GL_CLAMP);*/
                
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                
                // build our texture mipmaps
                //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_LUMINANCE, width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, normalMapData);
                //	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
                
                //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR, GL_UNSIGNED_BYTE, normalMapData);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, normalMapData);
                
                // deallocate
                FreeImage_Unload(normalMap);
                break; // end bump map
        } // end switch
        
        //return success
        return true;
    }
    return false;
}

