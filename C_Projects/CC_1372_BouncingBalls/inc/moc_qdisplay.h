/****************************************************************************
** QDisplay meta object code from reading C++ file 'qdisplay.h'
**
** Created: Tue Oct 28 12:10:08 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.3   edited Aug 5 16:40 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "qdisplay.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *QDisplay::className() const
{
    return "QDisplay";
}

QMetaObject *QDisplay::metaObj = 0;
static QMetaObjectCleanUp cleanUp_QDisplay( "QDisplay", &QDisplay::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString QDisplay::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QDisplay", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString QDisplay::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "QDisplay", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* QDisplay::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"timerDone", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "timerDone()", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"QDisplay", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_QDisplay.setMetaObject( metaObj );
    return metaObj;
}

void* QDisplay::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "QDisplay" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool QDisplay::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: timerDone(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool QDisplay::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool QDisplay::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool QDisplay::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
