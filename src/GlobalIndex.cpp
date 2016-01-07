#include "GlobalIndex.h"

GlobalIndex::GlobalIndex()
{
	m_index = 0;
}

GlobalIndex::~GlobalIndex()
{
}

quint64 GlobalIndex::getIndex()
{
	return m_index++;
}
