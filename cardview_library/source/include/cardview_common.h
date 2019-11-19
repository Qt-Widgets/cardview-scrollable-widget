#ifndef CARDVIEW_COMMON_H
#define CARDVIEW_COMMON_H

#include <QtGlobal>

#if defined(CARDVIEW_LIBRARY)
#  define CARDVIEW_EXPORT Q_DECL_EXPORT
#else
#  define CARDVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // CARDVIEW_COMMON_H
