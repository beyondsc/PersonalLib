#ifndef __KCOUNTOBJ__H__
#define __KCOUNTOBJ__H__

#ifndef K_VALID_REFCOUNT
#define K_VALID_REFCOUNT(nRef)	assert((unsigned)(nRef) < 2000000000)
#endif

#ifndef K_INVALID_REFCOUNT
#define K_INVALID_REFCOUNT		2147483647
#endif

namespace kstd
{
	template<class T>
	class KCountObj : public T
	{
	private:
		ulong m_nRef;

	public:
		KCountObj() : m_nRef(1) {}

		ulong AddRef()
		{
			K_VALID_REFCOUNT(m_nRef);
			return ++m_nRef;
		}

		ulong Release()
		{
			K_VALID_REFCOUNT(m_nRef);
			ulong l = --m_nRef;
			if (l == 0)
			{
				m_nRef = K_INVALID_REFCOUNT;
				delete this;
			}
			return l;
		}
	};
};

#endif