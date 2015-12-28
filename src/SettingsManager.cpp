#include "SettingsManager.h"

SettingsManager::SettingsManager(QObject* parent) :
    QObject(parent) {
	m_filename = "";
}

void SettingsManager::setFile(QString filepath) {
	m_filename = filepath;
}
