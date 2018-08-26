#ifndef ISTRING_H
#define ISTRING_H
#include <intfparam.h>
#include <provreq.h>
class IString
{
public:
	virtual ~IString(){}
	virtual int strcmp(char * str1,char * str2)= 0;
	virtual int strcmpRom(char * str1,char ROM * str2)= 0;
	virtual int strncmp(char * str1,char * str2,int num)= 0;
	virtual int strncmpRom(char * str1,char ROM * str2,int num)= 0;
	virtual int strlen(char * str)= 0;
	virtual int strlenRom(char ROM * str)= 0;
	virtual char* strcpy(char * dest,char * source)= 0;
	virtual char* strcpyRom(char * dest,char ROM * source)= 0;
	virtual char* strncpy(char * dest,char * source,int num)= 0;
	virtual char* strncpyRom(char * dest,char ROM * source,int num)= 0;
	virtual char* strcat(char * dest,char * source)= 0;
	virtual char* strcatRom(char * dest,char ROM * source)= 0;
	virtual char* strncat(char * dest,char * source,int num)= 0;
	virtual char* strstr(char * book,char * word)= 0;
	virtual char* strchr(char * book,int letter)= 0;
};


#define IStringImpl(Comp,intf)    \
virtual int intf ## _strcmp(char * str1,char * str2);\
virtual int intf ## _strcmpRom(char * str1,char ROM * str2);\
virtual int intf ## _strncmp(char * str1,char * str2,int num);\
virtual int intf ## _strncmpRom(char * str1,char ROM * str2,int num);\
virtual int intf ## _strlen(char * str);\
virtual int intf ## _strlenRom(char ROM * str);\
virtual char* intf ## _strcpy(char * dest,char * source);\
virtual char* intf ## _strcpyRom(char * dest,char ROM * source);\
virtual char* intf ## _strncpy(char * dest,char * source,int num);\
virtual char* intf ## _strncpyRom(char * dest,char ROM * source,int num);\
virtual char* intf ## _strcat(char * dest,char * source);\
virtual char* intf ## _strcatRom(char * dest,char ROM * source);\
virtual char* intf ## _strncat(char * dest,char * source,int num);\
virtual char* intf ## _strstr(char * book,char * word);\
virtual char* intf ## _strchr(char * book,int letter);\
class Comp ## _ ## intf : public IString \
{\
private:\
    Comp *m_parent; \
public: \
    Comp ## _ ## intf( Comp *parent) \
    {\
        m_parent = parent;\
    }\
virtual int strcmp(char * str1,char * str2){ return m_parent->intf ## _strcmp(str1,str2);}\
virtual int strcmpRom(char * str1,char ROM * str2){ return m_parent->intf ## _strcmpRom(str1,str2);}\
virtual int strncmp(char * str1,char * str2,int num){ return m_parent->intf ## _strncmp(str1,str2,num);}\
virtual int strncmpRom(char * str1,char ROM * str2,int num){ return m_parent->intf ## _strncmpRom(str1,str2,num);}\
virtual int strlen(char * str){ return m_parent->intf ## _strlen(str);}\
virtual int strlenRom(char ROM * str){ return m_parent->intf ## _strlenRom(str);}\
virtual char* strcpy(char * dest,char * source){ return m_parent->intf ## _strcpy(dest,source);}\
virtual char* strcpyRom(char * dest,char ROM * source){ return m_parent->intf ## _strcpyRom(dest,source);}\
virtual char* strncpy(char * dest,char * source,int num){ return m_parent->intf ## _strncpy(dest,source,num);}\
virtual char* strncpyRom(char * dest,char ROM * source,int num){ return m_parent->intf ## _strncpyRom(dest,source,num);}\
virtual char* strcat(char * dest,char * source){ return m_parent->intf ## _strcat(dest,source);}\
virtual char* strcatRom(char * dest,char ROM * source){ return m_parent->intf ## _strcatRom(dest,source);}\
virtual char* strncat(char * dest,char * source,int num){ return m_parent->intf ## _strncat(dest,source,num);}\
virtual char* strstr(char * book,char * word){ return m_parent->intf ## _strstr(book,word);}\
virtual char* strchr(char * book,int letter){ return m_parent->intf ## _strchr(book,letter);}\
};\
Comp ## _ ## intf i__ ## intf;


#endif
