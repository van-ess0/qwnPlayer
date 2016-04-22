/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "NotificationClient.h"

#include <QDebug>


static NotificationClient* androidMediaPlayer;

NotificationClient::NotificationClient(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));

    m_mediaPlayerService =
            QtAndroid::androidActivity().callObjectMethod("getMediaPlayerService",
                                                          "()Lorg/qwnplayer/qwnplayer/MediaPlayerService;"
                                                          );
    androidMediaPlayer = this;
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification) {
        return;
    }
    qDebug() << notification;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::play()
{
    qDebug() << "PLAY";
#ifdef Q_OS_ANDROID
//    QtAndroid::androidActivity().callMethod<void>("play", "()V");
    m_mediaPlayerService.callMethod<void>("start", "()V");
#endif
}

void NotificationClient::pause()
{
    qDebug() << "PAUSE";
#ifdef Q_OS_ANDROID
    m_mediaPlayerService.callMethod<void>("pause", "()V");
#endif
}

void NotificationClient::stop()
{
    qDebug() << "STOP";
#ifdef Q_OS_ANDROID
    m_mediaPlayerService.callMethod<void>("stop", "()V");
#endif
}

void NotificationClient::seekTo(qint32 msec)
{
    qDebug() << "SEEK TO: " << msec;
#ifdef Q_OS_ANDROID
    m_mediaPlayerService.callMethod<void>("seekTo", "(I)V", jint(msec));
#endif
}

int NotificationClient::getCurrentPosition()
{
    qDebug() << "GET CURRENT POSITION";
#ifdef Q_OS_ANDROID
    return m_mediaPlayerService.callMethod<jint>("getCurrentPosition");
#endif
    return 0;
}

int NotificationClient::getDuration()
{
    qDebug() << "GET DURATION";
#ifdef Q_OS_ANDROID
    return m_mediaPlayerService.callMethod<jint>("getDuration");
#endif
    return 0;
}

bool NotificationClient::isPlaying()
{
    qDebug() << "IS PLAYING";
#ifdef Q_OS_ANDROID
    return m_mediaPlayerService.callMethod<jboolean>("isPlaying");
#endif
    return false;
}

void NotificationClient::updateAndroidNotification()
{
    qDebug() << "HERE: " << m_notification;
#ifdef Q_OS_ANDROID
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
	QAndroidJniObject::callStaticMethod<void>("org/qwnplayer/qwnplayer/NotificationClient",
                                       "notify",
                                       "(Ljava/lang/String;)V",
									   javaNotification.object<jstring>());

#endif
}

static void onErrorNative(JNIEnv *env, jobject thiz, jint what, jint extra)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;
//    Q_EMIT (*mediaPlayers)[i]->error(what, extra);
    qDebug() << "ERROR WHAT: " << what << " EXTRA: " << extra;
    Q_EMIT androidMediaPlayer->error(what, extra);
}

static void onBufferingUpdateNative(JNIEnv *env, jobject thiz, jint percent)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;

//    Q_EMIT (*mediaPlayers)[i]->bufferingChanged(percent);
    qDebug() << "PERCENT: " << percent;
    Q_EMIT androidMediaPlayer->bufferingChanged(percent);
}

static void onProgressUpdateNative(JNIEnv *env, jobject thiz, jint progress)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;

//    Q_EMIT (*mediaPlayers)[i]->progressChanged(progress);
    qDebug() << "PROGRESS: " << progress;
    Q_EMIT androidMediaPlayer->progressChanged(progress);
}

static void onDurationChangedNative(JNIEnv *env, jobject thiz, jint duration)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;

//    Q_EMIT (*mediaPlayers)[i]->durationChanged(duration);
    qDebug() << "DURATION: " << duration;
    Q_EMIT androidMediaPlayer->durationChanged(duration);
}

static void onInfoNative(JNIEnv *env, jobject thiz, jint what, jint extra)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;

//    Q_EMIT (*mediaPlayers)[i]->info(what, extra);
    qDebug() << "INFO WHAT: " << what << " EXTRA: " << extra;
    Q_EMIT androidMediaPlayer->info(what, extre);
}

static void onStateChangedNative(JNIEnv *env, jobject thiz, jint state)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);
//    QReadLocker locker(rwLock);
//    const int i = mediaPlayers->indexOf(reinterpret_cast<AndroidMediaPlayer *>(id));
//    if (Q_UNLIKELY(i == -1))
//        return;

//    Q_EMIT (*mediaPlayers)[i]->stateChanged(state);
    qDebug() << "STATE: " << state;
    Q_EMIT androidMediaPlayer->stateChanged(state);
}

bool NotificationClient::initJNI(JNIEnv *env)
{
    jclass clazz = env->FindClass("org/qwnplayer/qwnplayer/MediaPlayerService");

    static const JNINativeMethod methods[] = {
        {"onBufferingUpdateNative", "(I)V", reinterpret_cast<void *>(onBufferingUpdateNative)},
        {"onProgressUpdateNative", "(I)V", reinterpret_cast<void *>(onProgressUpdateNative)},
        {"onDurationChangedNative", "(I)V", reinterpret_cast<void *>(onDurationChangedNative)},
        {"onErrorNative", "(II)V", reinterpret_cast<void *>(onErrorNative)},
        {"onInfoNative", "(II)V", reinterpret_cast<void *>(onInfoNative)},
        {"onStateChangedNative", "(I)V", reinterpret_cast<void *>(onStateChangedNative)}
    };

    if (clazz && env->RegisterNatives(clazz,
                                      methods,
                                      sizeof(methods) / sizeof(methods[0])) != JNI_OK) {
            return false;
    }

    return true;
}



