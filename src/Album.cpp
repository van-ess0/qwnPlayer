#include "Album.h"

Album::Album(const QString& name,
			 const quint32 year,
			 const QString& cover,
			 QObject* parent)
	:
	  SubListedListItem(parent)
{
	m_name		= name;
	m_year		= year;
	m_cover		= cover;
	m_globalId	= GlobalAlbumIndex::instance()->getIndex();

	m_tracksModel = QSharedPointer<Models::ListModel>(new Models::ListModel(new Track(0, "empty", "empty", "empty", NULL)));
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
			return this->id();
		case albumName:
			return this->getName();
		case albumYear:
			return this->getYear();
		case albumTracks:
			return this->getTracks();
		case albumCover:
			return this->getCover();
		default:
			return QVariant();
	}
}

QHash<int, QByteArray> Album::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[albumId]		= "albumId";
	roles[albumName]	= "albumName";
	roles[albumYear]	= "albumYear";
	roles[albumTracks]	= "albumTracks";
	roles[albumCover]	= "albumCover";

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
