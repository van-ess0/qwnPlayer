#ifndef GLOBALINDEX_H
#define GLOBALINDEX_H

#include <QObject>
#include "SingletonTemplate.h"

class GlobalIndex : public QObject
{
private:
	quint64 m_index;

public:
	GlobalIndex() {
		m_index = 0;
	}
	~GlobalIndex() {
	}
	virtual quint64 getIndex() {
		return m_index++;
	}
};

#define NEW_GLOBAL_INDEX(CLASS_NAME) \
	class CLASS_NAME : \
		public GlobalIndex, \
		public SingletonTemplate<CLASS_NAME> \
	{};

#endif // GLOBALINDEX_H
