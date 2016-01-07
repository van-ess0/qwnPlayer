#include "MusicLibrary.h"

MusicLibrary::MusicLibrary(QQmlContext *context, QObject* parent) : QObject(parent)
{
	m_artistModel = new Models::SubListedListModel(new Artist("empty", NULL));
	m_artistModel->setSorting(true);
	context->setContextProperty("artistModel", m_artistModel);
}

Models::SubListedListModel* MusicLibrary::getArtistModel() const
{
	return m_artistModel;
}

Track* MusicLibrary::getTrack(const quint64& artistId, const quint64& albumId, const quint64& trackId) const
{
	return qobject_cast<Track*>(getAlbum(artistId, albumId)->submodel()->find(trackId));
}

Album* MusicLibrary::getAlbum(const quint64& albumId) const
{
	Models::ListItem* temp = NULL;
	foreach (Models::ListItem* artist, m_artistModel->toList()) {

		Artist* artist_obj = qobject_cast<Artist*>(artist);
		temp = artist_obj->submodel()->find(albumId);

		if (temp) {
			break;
		}
	}

	return qobject_cast<Album*>(temp);
}

Album* MusicLibrary::getAlbum(const quint64& artistId, const quint64& albumId) const
{
	return qobject_cast<Album*>(getArtist(artistId)->submodel()->find(albumId));
}

Artist* MusicLibrary::getArtist(const quint64& artistId) const
{
	return qobject_cast<Artist*>(m_artistModel->find(artistId));
}

void MusicLibrary::slotCollectionDataParsed(QList<Artist*> artists)
{
	m_artistModel->clear();
	foreach (Artist* value, artists) {
		m_artistModel->appendRow(value);
	}
}

