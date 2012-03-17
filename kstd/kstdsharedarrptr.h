#ifndef __KSTDSHAREDARRPTR__H__
#define __KSTDSHAREDARRPTR__H__

namespace kstd
{
	template<class T> 
	class KSharedArrPtr
	{
		typedef ulong count_type;

	private:
		T * px;            // contained pointer
		count_type * pn;   // ptr to reference counter

	public:
		explicit KSharedArrPtr(T * p = 0): px(p)
		{
			try  // prevent leak if new throws
			{
				pn = new count_type(1);
			}
			catch(...)
			{
				throw;
			}
		}

		~KSharedArrPtr()
		{
			if(--*pn == 0)
			{
				delete pn;
			}
		}

		KSharedArrPtr(KSharedArrPtr const & r) : px(r.px)  // never throws
		{
			pn = r.pn;
			++*pn;
		}

		KSharedArrPtr & operator=(KSharedArrPtr const & r)
		{
			KSharedArrPtr(r).swap(*this);
			return *this;
		}

		void reset(T * p = 0)
		{
			assert(p == 0 || p != px);
			KSharedArrPtr(p).swap(*this);
		}

		T * get() const  // never throws
		{
			return px;
		}

		T & operator[](std::ptrdiff_t i) const  // never throws
		{
			assert(px != 0);
			assert(i >= 0);
			return px[i];
		}

		long use_count() const  // never throws
		{
			return *pn;
		}

		bool unique() const  // never throws
		{
			return *pn == 1;
		}

		void swap(KSharedArrPtr<T> & other)  // never throws
		{
			std::swap(px, other.px);
			std::swap(pn, other.pn);
		}

	};  // KSharedArrPtr

	template<class T, class U> inline bool operator==(KSharedArrPtr<T> const & a, KSharedArrPtr<U> const & b)
	{
		return a.get() == b.get();
	}

	template<class T, class U> inline bool operator!=(KSharedArrPtr<T> const & a, KSharedArrPtr<U> const & b)
	{
		return a.get() != b.get();
	}

	template<class T> inline bool operator<(KSharedArrPtr<T> const & a, KSharedArrPtr<T> const & b)
	{
		return std::less<T*>()(a.get(), b.get());
	}

	template<class T> void swap(KSharedArrPtr<T> & a, KSharedArrPtr<T> & b)
	{
		a.swap(b);
	}
};

#endif