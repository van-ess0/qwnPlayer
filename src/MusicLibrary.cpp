#include "MusicLibrary.h"

void MusicLibrary::slotCollectionDataParsed(QList<Artist*> artists) {
    foreach (Artist* value, artists) {
        m_artistModel->appendRow(value);
    }
//		setArtistList(artists);
}

