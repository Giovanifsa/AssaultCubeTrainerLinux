#ifndef LIBRARY_GLOBAL_H
#define LIBRARY_GLOBAL_H

#define Q_DECL_EXPORT     __attribute__((visibility("default")))
#define Q_DECL_IMPORT     __attribute__((visibility("default")))
#define DECL_LCONSTRUCT   __attribute__ ((constructor))
#define DECL_LDESTROY     __attribute__ ((destructor))

#define LIBRARY_EXPORT Q_DECL_EXPORT
#define LIBRARY_LOAD DECL_LCONSTRUCT
#define LIBRARY_UNLOAD DECL_LDESTROY

#endif // LIBRARY_GLOBAL_H
