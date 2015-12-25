#ifndef QWNMEDIAPLAYER_H
#define QWNMEDIAPLAYER_H

#include <QMediaPlayer>

class QwnMediaPlayer : public QObject
{
	Q_OBJECT
private:
	QMediaPlayer* player;


public:
	explicit QwnMediaPlayer(QObject *parent = 0);

	// Create 'onNameOfSignal' handler in qml for signal 'nameOfSignal'
	// if you want to handle it :)
signals:
//	void testSig();
//	void keyGenerated(bool success);
//public slots:
//	void qmlSlot(QString string);
//	void qmlSlotEmpty();

	void signalPositionChanged(qint64 progress);
	void signalDurationChanged(qint64 duration);

	// connections with qmediaplayer
private slots:
	void slotAudioAvailabilityChanged(bool);

	void slotMediaStatusChanged(QMediaPlayer::MediaStatus);
	void slotBufferStatusChanged(int percentFilled);
	void positionChanged(qint64 progress);
	void durationChanged(qint64 duration);
	void seek(int seconds);
	void stateChanged(QMediaPlayer::State);
	void error(QMediaPlayer::Error);

	// This methods will be called from qml file
public slots:
	void playToggle();
	void nextTrack();
	void prevTrack();
	void shuffleToggle();
	void cycleToggle();
};

#endif // QWNMEDIAPLAYER_H
