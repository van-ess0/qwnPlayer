#include "Artist.h"

Artist::Artist(const QString& name,
			   QObject *parent)
	:
	  m_name(name),
	  QObject(parent)
{

}

