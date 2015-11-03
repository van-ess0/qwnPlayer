#include "Album.h"

Album::Album(const QString& name,
			 const quint32 year,
			 QObject *parent)
	:
	  m_name(name),
	  m_year(year),
	  QObject(parent)
{

}

