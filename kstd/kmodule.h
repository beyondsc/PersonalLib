#ifndef __KMODULE__H__
#define __KMODULE__H__

namespace kstd
{
	class KModule
	{
	protected:
		HMODULE m_hLib;

	private:
		KModule(const KModule&);
		KModule& operator=(const KModule&);

	public:
		KModule()
		{
			m_hLib = NULL;
		}
		KModule(LPCSTR szDllName, DWORD uFlags = 0)
		{
			m_hLib = LoadLibraryExA(szDllName, NULL, uFlags);
		}
		KModule(LPCWSTR szDllName, DWORD uFlags = 0)
		{
			m_hLib = LoadLibraryExW(szDllName, NULL, uFlags);
		}

		~KModule()
		{
			if (m_hLib)
				FreeLibrary(m_hLib);
		}
	
		STDMETHODIMP Load(LPCSTR szDllName, DWORD uFlags = 0)
		{
			assert(!m_hLib);

			if (m_hLib)
				FreeLibrary(m_hLib);
			m_hLib = LoadLibraryExA(szDllName, NULL, uFlags);
			return m_hLib ? S_OK : E_FAIL;
		}

		STDMETHODIMP_(void*) GetProc(LPCSTR szProc, void** ppv)
		{
			*ppv = GetProcAddress(m_hLib, szProc);
			return *ppv;
		}
		STDMETHODIMP_(void) Free()
		{
			if (m_hLib)
			{
				FreeLibrary(m_hLib);
				m_hLib = NULL;
			}
		}
		operator HMODULE() const
		{
			return m_hLib;
		}
	};
};
#endif