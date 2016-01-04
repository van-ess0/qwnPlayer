#include "MusicLibrary.h"

MusicLibrary::MusicLibrary(QObject* parent) : QObject(parent)
{
	m_artistModel = new Models::SubListedListModel(new Artist("empty", NULL));
	m_artistModel->setSorting(true);
}

Models::SubListedListModel* MusicLibrary::getArtistModel() const
{
	return m_artistModel;
}

Models::ListItem* MusicLibrary::getAlbumById(const quint64& id)
{
	Models::ListItem* temp = NULL;
	foreach (Models::ListItem* artist, m_artistModel->toList()) {

		Artist* artist_obj = qobject_cast<Artist*>(artist);
		temp = artist_obj->submodel()->find(id);

		if (temp) {
			break;
		}
	}
	return temp;
}

void MusicLibrary::slotCollectionDataParsed(QList<Artist*> artists)
{
	m_artistModel->clear();
	foreach (Artist* value, artists) {
		m_artistModel->appendRow(value);
	}
}

