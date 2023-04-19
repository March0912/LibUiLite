#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(JMUILITE_LIB)
#  define JMUILITE_EXPORT Q_DECL_EXPORT
# else
#  define JMUILITE_EXPORT Q_DECL_IMPORT
# endif
#else
# define JMUILITE_EXPORT
#endif
