/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __cocos2d_libs__NodeReaderProtocol__
#define __cocos2d_libs__NodeReaderProtocol__

#include "editor-support/cocostudio/CocosStudioExport.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

#if (defined(WIN32) && defined(_WINDOWS)) || defined(WINRT) || defined(WP8)
#ifdef __MINGW32__
#include <string.h>
#endif

#if defined(CC_STATIC)
#define CC_STUDIO_DLL
#else
#if defined(_USRSTUDIOPDLL)
#define CC_STUDIOP_DLL     __declspec(dllexport)
#else         /* use a DLL library */
#define CC_STUDIOP_DLL     __declspec(dllimport)
#endif
#endif

 /* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif
#elif defined(_SHARED_)
#define CC_STUDIOP_DLL     __attribute__((visibility("default")))
#else
#define CC_STUDIOP_DLL
#endif

namespace flatbuffers
{
    class FlatBufferBuilder;
    template<typename T> struct Offset;
    
    class Table;

    struct ResourceData; // x-studio365 spec, csb batch load support, assets hook functions.
}

namespace tinyxml2
{
    class XMLElement;
}

namespace cocos2d
{
    class Node;
}

namespace cocostudio
{
    class CC_STUDIO_DLL NodeReaderProtocol
    {
    public:
        NodeReaderProtocol() {};
        virtual ~NodeReaderProtocol() {};
        
        virtual flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(const tinyxml2::XMLElement* objectData,
                                                                                     flatbuffers::FlatBufferBuilder* builder) = 0;
        virtual void setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOptions) = 0;
        virtual cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions) = 0;
    };
}

// x-studio365 spec, csb batch load support, assets hook functions.
namespace cocos2d {

    // builtin ui predecl
    class Sprite;
    class ParticleSystemQuad;
    namespace ui {
        class ImageView;

        class Button;
        class CheckBox;
        class Slider;
        class LoadingBar;

        class Text;
        class TextField;
        class TextAtlas;
        class TextBMFont;

        class Layout;
        class ScrollView;
        class ListView;
        class PageView;
    }
    namespace wext {
		CC_STUDIOP_DLL extern void(*onLoadSpriteFramesWithFile)(std::string& file);

		CC_STUDIOP_DLL extern cocos2d::ResourceData makeResourceData(const flatbuffers::ResourceData* data);
		CC_STUDIOP_DLL extern cocos2d::ResourceData makeResourceData(const std::string& path, int type = 0);
		CC_STUDIOP_DLL extern cocos2d::ResourceData makeResourceData(std::string&& path, int type = 0);
		CC_STUDIOP_DLL extern void resetReaderAllHooks();

        /// Assets Hooks
		CC_STUDIOP_DLL extern void(*onBeforeLoadObjectAsset)(cocos2d::Node*, cocos2d::ResourceData& assets, int index/*= 0*/);
		CC_STUDIOP_DLL extern void(*onAfterLoadObjectAsset)(cocos2d::Node*, cocos2d::ResourceData& assets, int index/*= 0*/);

        // Object creator Hooks
		CC_STUDIOP_DLL extern cocos2d::Node*(*aNode)();
		CC_STUDIOP_DLL extern cocos2d::Sprite*(*aSprite)();
		CC_STUDIOP_DLL extern cocos2d::ui::ImageView*(*aImageView)();
        CC_STUDIOP_DLL extern cocos2d::ui::Button*(*aButton)();
        CC_STUDIOP_DLL extern cocos2d::ui::CheckBox*(*aCheckBox)();
        CC_STUDIOP_DLL extern cocos2d::ui::Slider*(*aSlider)();
        CC_STUDIOP_DLL extern cocos2d::ui::LoadingBar*(*aLoadingBar)();
        CC_STUDIOP_DLL extern cocos2d::ui::Text*(*aText)();
        CC_STUDIOP_DLL extern cocos2d::ui::TextField*(*aTextField)();
        CC_STUDIOP_DLL extern cocos2d::ui::TextAtlas*(*aTextAtlas)();
        CC_STUDIOP_DLL extern cocos2d::ui::TextBMFont*(*aTextBMFont)();
        CC_STUDIOP_DLL extern cocos2d::ui::Layout*(*aLayout)();
        CC_STUDIOP_DLL extern cocos2d::ui::ScrollView*(*aScrollView)();
        CC_STUDIOP_DLL extern cocos2d::ui::ListView*(*aListView)();
        CC_STUDIOP_DLL extern cocos2d::ui::PageView*(*aPageView)();
        CC_STUDIOP_DLL extern cocos2d::ParticleSystemQuad*(*aParticleSystemQuad)(const std::string&);
    };
};

#endif /* defined(__cocos2d_libs__NodeReaderProtocol__) */
