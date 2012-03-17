#ifndef __KDEF__H__
#define __KDEF__H__

#ifdef TLIB_EXPORTS
#define EXPORT_DECL __declspec(dllexport)
#else
#define EXPORT_DECL __declspec(dllimport)
#endif

#endif