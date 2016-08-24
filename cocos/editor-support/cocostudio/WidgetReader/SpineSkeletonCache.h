#include <cocos2d.h>
#include <spine/spine.h>
#include <spine/spine-cocos2dx.h>

#include "NodeReaderProtocol.h"

using namespace spine;

class CC_STUDIOP_DLL SpineSkeletonCache
{
public:
    class SkeletonData : public cocos2d::Ref
    {
    public:
        SkeletonData(spSkeletonData* d, spAttachmentLoader* loader) : data(d), attachmentLoader(loader) {}
        ~SkeletonData()
        {
            if (data != nullptr)
                spSkeletonData_dispose(data);
            if (attachmentLoader != nullptr)
                spAttachmentLoader_dispose(attachmentLoader);
        }
        spAttachmentLoader* attachmentLoader;
        spSkeletonData* data;
    };

    static void setErrorLogFunc(void(*)(const char* pszFormat, ...));

    static SpineSkeletonCache* getInstance();

    SkeletonData* addData(const char* dataFile, const char* atlasFile, float scale);

    void removeData(const char* dataFile);

    void removeAllData(void);
    void removeAllUnusedData(void);

public:
    std::map<std::string, SkeletonData*> cache_;
};

