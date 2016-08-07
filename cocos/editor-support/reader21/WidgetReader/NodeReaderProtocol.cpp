//
//  NodeReaderProtocol.cpp
//  cocos2d_libs
//
//  Created by pipu on 14/11/18.
//
//

#include "editor-support/cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "editor-support/reader21/CSParseBinary_generated.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

// x-studio365 spec, csb batch load support, assets hook functions.
static void onLoadObjectAssetDummy(cocos2d::Node*, cocos2d::ResourceData& assets, int index)
{
}

//static cocos2d::Node* aNodeDef() {
//}
//static cocos2d::Sprite* aSpriteDef() {
//}
//static cocos2d::ui::ImageView* aImageViewDef() {
//}
//static cocos2d::ui::Button* aButtonDef() {
//}
//static cocos2d::ui::CheckBox* CheckBoxDef() {
//}
//static cocos2d::ui::Slider* aSliderDef() {
//}
//static cocos2d::ui::LoadingBar* aLoadingBarDef() {
//}
//static cocos2d::ui::Text* aTextDef() {
//}
//static cocos2d::ui::TextField* aTextFieldDef() {
//}
//static cocos2d::ui::TextAtlas* aTextAtlasDef() {
//}
//static cocos2d::ui::TextBMFont* aTextBMFontDef() {
//}
//static cocos2d::ui::Layout* aLayoutDef() {
//}
//static cocos2d::ui::ScrollView* aScrollViewDef() {
//}
//static cocos2d::ui::ListView* aListViewDef() {
//}
//static cocos2d::ui::PageView* aPageViewDef() {
//}
//static cocos2d::ParticleSystemQuad* aParticleSystemQuadDef() {
//}

template<typename _T>
static _T* object_create_func()
{
    return _T::create();
}

static cocos2d::ParticleSystemQuad* aParticleSystemQuadDef(const std::string& path) {
    return cocos2d::ParticleSystemQuad::create(path);
}

static void onLoadSpriteFramesWithFileDummy(std::string&)
{

}

namespace cocos2d {
    namespace wext {
        void(*onBeforeLoadObjectAsset)(cocos2d::Node*, cocos2d::ResourceData& assets, int index/*= 0*/) = &onLoadObjectAssetDummy;
        void(*onAfterLoadObjectAsset)(cocos2d::Node*, cocos2d::ResourceData& assets, int index/*= 0*/) = &onLoadObjectAssetDummy;
        void(*onLoadSpriteFramesWithFile)(std::string& file) = nullptr;
        cocos2d::Node*(*aNode)();
        cocos2d::Sprite*(*aSprite)();
        cocos2d::ui::ImageView*(*aImageView)();
        cocos2d::ui::Button*(*aButton)();
        cocos2d::ui::CheckBox*(*aCheckBox)();
        cocos2d::ui::Slider*(*aSlider)();
        cocos2d::ui::LoadingBar*(*aLoadingBar)();
        cocos2d::ui::Text*(*aText)();
        cocos2d::ui::TextField*(*aTextField)();
        cocos2d::ui::TextAtlas*(*aTextAtlas)();
        cocos2d::ui::TextBMFont*(*aTextBMFont)();
        cocos2d::ui::Layout*(*aLayout)();
        cocos2d::ui::ScrollView*(*aScrollView)();
        cocos2d::ui::ListView*(*aListView)();
        cocos2d::ui::PageView*(*aPageView)();
        cocos2d::ParticleSystemQuad*(*aParticleSystemQuad)(const std::string&);

        void resetReaderAllHooks()
        {
            onLoadSpriteFramesWithFile = onLoadSpriteFramesWithFileDummy;
            onBeforeLoadObjectAsset = onLoadObjectAssetDummy;
            onAfterLoadObjectAsset = onLoadObjectAssetDummy;

            aNode = object_create_func<Node>;
            aSprite = object_create_func<Sprite>;
            aImageView = object_create_func<ui::ImageView>;
            aButton = object_create_func<ui::Button>;
            aCheckBox = object_create_func<ui::CheckBox>;
            aSlider = object_create_func<ui::Slider>;
            aLoadingBar = object_create_func<ui::LoadingBar>;
            aText = object_create_func<ui::Text>;
            aTextField = object_create_func<ui::TextField>;
            aTextAtlas = object_create_func<ui::TextAtlas>;
            aTextBMFont = object_create_func<ui::TextBMFont>;
            aLayout = object_create_func<ui::Layout>;
            aScrollView = object_create_func<ui::ScrollView>;
            aListView = object_create_func<ui::ListView>;
            aPageView = object_create_func<ui::PageView>;
            aParticleSystemQuad = &aParticleSystemQuadDef;
        }

        static uint8_t _AUTO_INIT_VARS = (resetReaderAllHooks(), 0);
    };
};

cocos2d::ResourceData cocos2d::wext::makeResourceData(const flatbuffers::ResourceData* orig)
{
    cocos2d::ResourceData fileData;
    fileData.file = orig->path()->c_str();
    fileData.plist = orig->plistFile()->c_str();
    fileData.type = orig->resourceType();
    return fileData;
}

cocos2d::ResourceData cocos2d::wext::makeResourceData(const std::string& path, int type)
{
    cocos2d::ResourceData fileData;
    fileData.file = path;
    fileData.type = type;
    return fileData;
}

cocos2d::ResourceData cocos2d::wext::makeResourceData(std::string&& path, int type)
{
    cocos2d::ResourceData fileData;
    fileData.file = std::move(path);
    fileData.type = type;
    return fileData;
}
