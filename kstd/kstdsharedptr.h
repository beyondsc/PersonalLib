#ifndef __KSTDSHAREDPTR__H__
#define __KSTDSHAREDPTR__H__

#include <memory>

namespace kstd
{
	template<class T>
	class KSharedPtr
	{
		typedef ulong count_type;
	private:
		T* px;
		count_type* pn;
	public:
		explicit KSharedPtr(T * p = 0): px(p)
		{
			try  
			{
				pn = new count_type(1);
			}
			catch(...)
			{
				throw;
			}
		}

		~KSharedPtr()
		{
			if(--*pn == 0)
				delete pn;
		}

		KSharedPtr(KSharedPtr const & r): px(r.px)  // never throws
		{
			pn = r.pn;
			++*pn;
		}

		KSharedPtr & operator=(KSharedPtr const & r)
		{
			KSharedPtr(r).swap(*this);
			return *this;
		}


		explicit KSharedPtr(std::auto_ptr<T> & r)
		{ 
			pn = new count_type(1); // may throw
			px = r.release(); // fix: moved here to stop leak if new throws
		} 

		KSharedPtr & operator=(std::auto_ptr<T> & r)
		{
			KSharedPtr(r).swap(*this);
			return *this;
		}

		void reset(T * p = 0)
		{
			assert(p == 0 || p != px);
			KSharedPtr(p).swap(*this);
		}

		T & operator*() const  // never throws
		{
			assert(px != 0);
			return *px;
		}

		T * operator->() const  // never throws
		{
			assert(px != 0);
			return px;
		}

		T * get() const  // never throws
		{
			return px;
		}

		long use_count() const  // never throws
		{
			return *pn;
		}

		bool unique() const  // never throws
		{
			return *pn == 1;
		}

		void swap(KSharedPtr<T> & other)  // never throws
		{
			std::swap(px, other.px);
			std::swap(pn, other.pn);
		}
	};

	template<class T, class U> inline bool operator==(KSharedPtr<T> const & a, KSharedPtr<U> const & b)
	{
		return a.get() == b.get();
	}

	template<class T, class U> inline bool operator!=(KSharedPtr<T> const & a, KSharedPtr<U> const & b)
	{
		return a.get() != b.get();
	}

	template<class T> inline bool operator<(KSharedPtr<T> const & a, KSharedPtr<T> const & b)
	{
		return std::less<T*>()(a.get(), b.get());
	}

	template<class T> void swap(KSharedPtr<T> & a, KSharedPtr<T> & b)
	{
		a.swap(b);
	}

	// get_pointer() enables boost::mem_fn to recognize KSharedPtr

	template<class T> inline T * get_pointer(KSharedPtr<T> const & p)
	{
		return p.get();
	}

};

#endif 

