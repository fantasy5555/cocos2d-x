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

#include "editor-support/cocostudio/WidgetReader/SpineSkeletonReader/SpineSkeletonReader.h"
#include "editor-support/spine/SkeletonDataCache.h"

#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "platform/CCFileUtils.h"

#include "editor-support/cocostudio/CSParseBinary_generated.h"
#include "editor-support/cocostudio/FlatBuffersSerialize.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"


#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"

USING_NS_CC;
using namespace flatbuffers;

namespace cocostudio
{
    IMPLEMENT_CLASS_NODE_READER_INFO(SpineSkeletonReader)

        SpineSkeletonReader::SpineSkeletonReader()
    {

    }

    SpineSkeletonReader::~SpineSkeletonReader()
    {

    }

    static SpineSkeletonReader* _instanceSpriteReader = nullptr;

    SpineSkeletonReader* SpineSkeletonReader::getInstance()
    {
        if (!_instanceSpriteReader)
        {
            _instanceSpriteReader = new (std::nothrow) SpineSkeletonReader();
        }

        return _instanceSpriteReader;
    }

    void SpineSkeletonReader::purge()
    {
        CC_SAFE_DELETE(_instanceSpriteReader);
    }

    void SpineSkeletonReader::destroyInstance()
    {
        CC_SAFE_DELETE(_instanceSpriteReader);
    }

    Offset<Table> SpineSkeletonReader::createOptionsWithFlatBuffers(const tinyxml2::XMLElement *objectData,
        flatbuffers::FlatBufferBuilder *builder)
    {
        auto temp = NodeReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
        auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

        std::string dataFile;
        std::string atlasFile;
        std::string animation;
        std::string skin = "default";
        bool loop = false;
        float timeScale = 1.0f;

        cocos2d::BlendFunc blendFunc = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;

        // attributes
        const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
        while (attribute)
        {
            std::string name = attribute->Name();
            std::string value = attribute->Value();

            if (name == "DataFile")
            {
                dataFile = std::move(value);
            }
            else if (name == "AtlasFile")
            {
                atlasFile = std::move(value);
            }
            else if (name == "Animation")
            {
                animation = std::move(value);
            }
            else if (name == "Skin")
            {
                skin = std::move(value);
            }
            else if (name == "Loop")
            {
                loop = (value == "True" ? true : false);
            }
            else if (name == "TimeScale")
            {
                timeScale = atof(value.c_str());
            }

            attribute = attribute->Next();
        }
#if 0
        // FileData
        const tinyxml2::XMLElement* child = objectData->FirstChildElement();
        while (child)
        {
            std::string name = child->Name();

            if (name == "DataFile")
            {
                std::string texture = "";
                std::string texturePng = "";

                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Path")
                    {
                        path = value;
                    }
                    else if (name == "Type")
                    {
                        resourceType = getResourceType(value);
                    }
                    else if (name == "Plist")
                    {
                        plistFile = value;
                        texture = value;
                    }

                    attribute = attribute->Next();
                }

                if (resourceType == 1)
                {
                    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                    fbs->_textures.push_back(builder->CreateString(texture));
                }
            }
            else if (name == "BlendFunc")
            {
                const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();

                while (attribute)
                {
                    name = attribute->Name();
                    std::string value = attribute->Value();

                    if (name == "Src")
                    {
                        blendFunc.src = atoi(value.c_str());
                    }
                    else if (name == "Dst")
                    {
                        blendFunc.dst = atoi(value.c_str());
                    }

                    attribute = attribute->Next();
                }
            }

            child = child->NextSiblingElement();
        }
#endif

        flatbuffers::BlendFunc f_blendFunc(blendFunc.src, blendFunc.dst);

        auto options = CreateSpineSkeletonOptions(*builder,
            nodeOptions,
            builder->CreateString(dataFile),
            builder->CreateString(atlasFile),
            builder->CreateString(animation),
            builder->CreateString(skin),
            loop,
            timeScale);

            return *(Offset<Table>*)(&options);
    }

    void SpineSkeletonReader::setPropsWithFlatBuffers(cocos2d::Node *node,
        const flatbuffers::Table* spriteOptions)
    {
        Node** ppResult = (Node**)(node);

        auto options = (SpineSkeletonOptions*)spriteOptions;

        auto sharedData = spine::SkeletonDataCache::getInstance()->addData(options->dataFile()->c_str(), options->atlasFile()->c_str(), 1.0f/*TODO:*/);
        auto implNode = spine::SkeletonAnimation::createWithData(sharedData->data);
        implNode->setAnimation(0, options->animation()->c_str(), options->loop());
        implNode->setSkin(options->animation()->c_str());
        
        *ppResult = implNode;

        auto nodeReader = NodeReader::getInstance();
        nodeReader->setPropsWithFlatBuffers(implNode, (Table*)(options->nodeOptions()));

        // set Node Options
        auto nodeOptions = options->nodeOptions();

        GLubyte alpha = (GLubyte)nodeOptions->color()->a();
        GLubyte red = (GLubyte)nodeOptions->color()->r();
        GLubyte green = (GLubyte)nodeOptions->color()->g();
        GLubyte blue = (GLubyte)nodeOptions->color()->b();

        implNode->setScaleX(nodeOptions->scale()->scaleX());
        implNode->setScaleY(nodeOptions->scale()->scaleY());

        implNode->setColor(Color3B(red, green, blue));
        implNode->setOpacity(alpha);

        /*bool flipX = nodeOptions->flipX() != 0;
        bool flipY = nodeOptions->flipY() != 0;

        if (flipX != false)
            sprite->setFlippedX(flipX);
        if (flipY != false)
            sprite->setFlippedY(flipY);*/
    }

    Node* SpineSkeletonReader::createNodeWithFlatBuffers(const flatbuffers::Table *spriteOptions)
    {
        Node* node = nullptr;
        // Sprite* sprite = wext::aSprite(); // Sprite::create();
        // #Hack
        setPropsWithFlatBuffers((Node*)(&node), (Table*)spriteOptions);

        return node;
    }

    int SpineSkeletonReader::getResourceType(std::string key)
    {
        if (key == "Normal" || key == "Default")
        {
            return 	0;
        }

        FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
        if (fbs->_isSimulator)
        {
            if (key == "MarkedSubImage")
            {
                return 0;
            }
        }
        return 1;
    }
}
