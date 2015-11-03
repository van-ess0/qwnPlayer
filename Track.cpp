#include "Track.h"

Track::Track(const quint32 number,
			 const QString& title,
			 const QString& type,
			 const QString& path,
			 QObject *parent)
	:
	  m_number(number),
	  m_title(title),
	  m_audioType(type),
	  m_serverPath(path),
	  QObject(parent)
{

}

