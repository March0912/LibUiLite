#pragma once

#include <QtCore/qglobal.h>
#include <QScopedPointer>

#ifndef BUILD_STATIC
# if defined(JMUILITE_LIB)
#  define JMUILITE_EXPORT Q_DECL_EXPORT
# else
#  define JMUILITE_EXPORT Q_DECL_IMPORT
# endif
#else
# define JMUILITE_EXPORT
#endif


#define TR_DECLARE_PRIVATE(Class) \
    private: \
    Q_DECLARE_PRIVATE(Class) \
    QScopedPointer<Class##Private> d_ptr;

#define TR_DECLARE_PUBLIC(Class) \
    private: \
    Q_DECLARE_PUBLIC(Class) \
    Class* q_ptr;
