#include "Album.h"

Album::Album(const QString& name,
			 const quint32 year,
			 const QString& cover,
			 const quint64& artistId,
			 QObject* parent)
	:
	  SubListedListItem(parent)
{
	m_name		= name;
	m_year		= year;
	m_cover		= cover;
	m_globalId	= GlobalAlbumIndex::instance()->getIndex();
	m_artistId	= artistId;
	m_tracksModel = QSharedPointer<Models::ListModel>(new Models::ListModel(new Track(0, "empty", "empty", "empty", 0, NULL)));
	m_tracksModel->setSorting(true);
}

QString Album::getName() const
{
	return m_name;
}

quint32 Album::getYear() const
{
	return m_year;
}

QVariant Album::getTracks() const
{
	return QVariant::fromValue< QSharedPointer<Models::ListModel> >(m_tracksModel);
}

QString Album::getCover() const
{
	return m_cover;
}

quint64 Album::getArtistId() const
{
	return m_artistId;
}

void Album::addTrack(Track* track)
{
	m_tracksModel->appendRow(track);
}

int Album::id() const
{
	return m_globalId;
}

QVariant Album::data(int role) const
{
	switch (role) {
		case albumId:
			return id();
		case albumName:
			return getName();
		case albumYear:
			return getYear();
		case albumTracks:
			return getTracks();
		case albumCover:
			return getCover();
		case albumArtistId:
			return getArtistId();
		default:
			return QVariant();
	}
}

QHash<int, QByteArray> Album::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[albumId]			= "albumId";
	roles[albumName]		= "albumName";
	roles[albumYear]		= "albumYear";
	roles[albumTracks]		= "albumTracks";
	roles[albumCover]		= "albumCover";
	roles[albumArtistId]	= "albumArtistId";

	return roles;
}

bool Album::operator <(const Models::ListItem& nextElem)
{
	return m_year < nextElem.data(AlbumModelItemRoles::albumYear).toUInt();
}

Models::ListModel* Album::submodel() const
{
	return m_tracksModel.data();
}
