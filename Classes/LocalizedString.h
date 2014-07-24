#include "cocos2d.h"

#define LHLocalizedString(__KEY__) LocalizedString::localizedString(__KEY__)

using namespace cocos2d;

class LocalizedString {
    
public:
    LocalizedString();
    
    virtual ~LocalizedString();
    
    static __String* localizedString(const char *key);
    
private:
    static const char* getSystemLang();
    
};