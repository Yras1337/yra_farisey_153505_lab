#ifndef VECLIB_GLOBAL_H
#define VECLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VECLIB_LIBRARY)
#  define VECLIB_EXPORT Q_DECL_EXPORT
#else
#  define VECLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // VECLIB_GLOBAL_H
