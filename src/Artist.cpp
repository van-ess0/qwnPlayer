#include "Artist.h"

Artist::Artist(const QString& name, QObject* parent)
	:
	  SubListedListItem(parent)
{
	m_name		= name;
	m_globalId	= GlobalArtistIndex::instance()->getIndex();

	m_albumsModel = QSharedPointer<Models::SubListedListModel>(new Models::SubListedListModel(new Album("empty", 0, "empty", NULL)));
	m_albumsModel->setSorting(true);
}

QString Artist::getName() const {
	return m_name;
}

QVariant Artist::getAlbums() const {
	return QVariant::fromValue< QSharedPointer<Models::SubListedListModel> >(m_albumsModel);
}

void Artist::addAlbum(Album* album) {
	m_albumsModel->appendRow(album);
}

int Artist::id() const
{
	return m_globalId;
}

QVariant Artist::data(int role) const
{
	switch (role) {
		case artistId:
			return this->id();
		case artistName:
			return this->getName();
		case artistAlbums:
			return this->getAlbums();
		default:
			return QVariant();
	}
}

QHash<int, QByteArray> Artist::roleNames() const
{
	QHash<int, QByteArray> roles;

	roles[artistId]		= "artistId";
	roles[artistName]	= "artistName";
	roles[artistAlbums] = "artistAlbums";

	return roles;
}

bool Artist::operator <(const Models::ListItem& nextElem)
{
	return (this->m_name.compare(nextElem.data(ArtistModelItemRoles::artistName).toString()) < 0);
}

Models::ListModel*Artist::submodel() const
{
	return m_albumsModel.data();
}
