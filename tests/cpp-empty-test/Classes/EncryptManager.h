#ifndef  _ENCRYPTMANAGER_H_
#define  _ENCRYPTMANAGER_H_
#include <string>
#include <unordered_map>

class FileUtilsEncrypt;

class  EncryptManager {
    friend class FileUtilsEncrypt;
public:
    static EncryptManager *getInstance();

    void setEncryptEnabled(bool bVal, const std::string& key);
    bool isEncryptEnabled(void) const { return _encryptEnabled; }

protected:
    void setupHookFuncs();

private:
    bool _encryptEnabled = false;
    std::string _encryptKey;
    /// file index support, TODO: implement.
public:
    void enableFileIndex(const std::string& indexFile);
private:
    std::string _indexFilename;
    std::unordered_map<std::string, std::string> _indexFileMap;
};

#endif
