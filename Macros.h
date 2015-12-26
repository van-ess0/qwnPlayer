#ifndef MACROS_H
#define MACROS_H

#include <QObject>

#define QML_PROPERTY_READONLY(VALUE_TYPE, NAME) \
	Q_PROPERTY(VALUE_TYPE NAME READ NAME) \
	public: \
		VALUE_TYPE NAME() const { \
			return m_##NAME ; \
		} \
	private: \
		VALUE_TYPE m_##NAME ;

#define QML_PROPERTY(VALUE_TYPE, NAME, SET_NAME, NAME_CHANGED) \
	Q_PROPERTY(VALUE_TYPE NAME READ NAME WRITE SET_NAME NOTIFY NAME_CHANGED) \
	Q_SIGNALS: void NAME_CHANGED(); \
	public: \
		VALUE_TYPE NAME() const { \
			return m_##NAME ; \
		} \
		void SET_NAME(const VALUE_TYPE& value) { \
			if (value != m_##NAME) { \
				m_##NAME = value; \
				emit NAME_CHANGED(); \
				} \
			} \
	private: \
		VALUE_TYPE m_##NAME ;

#define GET_STRING(NAME, KEY, DEFAULT_VALUE) \
	virtual QString get##NAME() const { \
		QSettings settings(m_filename, QSettings::IniFormat); \
		return settings.value(KEY, DEFAULT_VALUE).toString(); \
	}

#define SET_STRING(NAME, KEY) \
	virtual void set##NAME(const QString& value)  { \
		QSettings settings(m_filename, QSettings::IniFormat); \
		settings.setValue(KEY, value); \
		settings.sync(); \
	}

#define GET_SET_STRING(NAME, KEY, DEFAULT_VALUE) \
	GET_STRING(NAME, KEY, DEFAULT_VALUE) \
	SET_STRING(NAME, KEY)


#endif // MACROS_H
