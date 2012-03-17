#ifndef __KSTDPTR__H__
#define __KSTDPTR__H__

#include "kcountobj.h"

namespace kstd
{
	enum enum_create_instance { create_instance };

	template <class E>
	class KStdPtr
	{
	protected:
		E* _ptr;

	public:
		KStdPtr()			{ _ptr = NULL; }
		KStdPtr(enum_create_instance f) { _ptr = new E; }

		KStdPtr(E* p)
		{
			_ptr = p;
			if (_ptr)
				_ptr->AddRef();
		}
		KStdPtr(const KStdPtr<E>& p)
		{
			_ptr = p._ptr;
			if (_ptr)
				_ptr->AddRef();
		}

		~KStdPtr()
		{
			if (_ptr)
				_ptr->Release();
		}

		void attach(E* p)
		{
			if (_ptr)
				_ptr->Release();
			_ptr = p;
		}

		E* detach()
		{
			E* tmp = _ptr;
			_ptr = NULL;
			return tmp;
		}

		void clear()
		{
			if (_ptr)
			{
				_ptr->Release();
				_ptr = NULL;
			}
		}

		E* operator=(E* p)
		{
			if (p)
				p->AddRef();
			if (_ptr)
				_ptr->Release();
			return _ptr = p;
		}

		E* operator=(const KStdPtr<E>& p)
		{
			if (p._ptr)
				p._ptr->AddRef();
			if (_ptr)
				_ptr->Release();
			return _ptr = p._ptr;
		}

		E& operator*() const
		{ return *_ptr; }

		operator E*() const
		{ return _ptr; }

		E** operator&() // The assert on operator& usually indicates a bug.
		{ assert(_ptr == NULL); return &_ptr; }

		E* operator->() const
		{ return _ptr; }

		BOOL operator!() const
		{ return _ptr == NULL; }

		BOOL operator==(E* p) const
		{ return _ptr == p; }

		BOOL operator!=(E* p) const
		{ return _ptr != p; }
	};

	template <class T>
	class KObjectPtr : public KStdPtr< KCountObj<T> >
	{
	public:
		KObjectPtr(enum_create_instance _createInst)
		{
			_ptr = new KCountObj<T>;
		}
	};

};
#endif