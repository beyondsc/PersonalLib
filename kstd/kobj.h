#ifndef __KOBJ__H__
#define __KOBJ__H__

class ICount
{
public:
	virtual ~ICount() {}
	virtual ulong AddRef() = 0;
	virtual ulong Release() = 0;
};

#endif