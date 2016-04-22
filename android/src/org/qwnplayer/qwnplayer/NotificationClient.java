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

package org.qwnplayer.qwnplayer;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;

import java.util.ArrayList;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.IBinder;

import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.util.Log;


import java.util.ArrayList;

public class NotificationClient extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;
    private static final String TAG = "NotificationClient";

    public NotificationClient()
    {
        Log.d(TAG, "on construct");
        m_instance = this;
    }

    public static void notify(String s)
    {
        Log.d(TAG, "notify");
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle("qwnPlayer");
        }

        m_builder.setContentText(s);
        Notification notification = m_builder.getNotification();
        notification.flags = Notification.FLAG_ONGOING_EVENT;
        m_notificationManager.notify(1, notification);
    }



    private MediaPlayerService myMediaPlayer;
    private Intent playIntent;
    private boolean musicBound = false;

    private ServiceConnection musicConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.d(TAG, "on service connected");
            MediaPlayerService.MusicBinder musicBinder = (MediaPlayerService.MusicBinder) service;
            myMediaPlayer = musicBinder.getService();


            ArrayList<String> songs = new ArrayList<String>();
            songs.add("http://degree:Fcnhjabpbrf95@217.197.0.52:83/owncloud/remote.php/webdav/Music/Stone%20Sour/2012%20-%20House%20Of%20Gold%20And%20Bones%20-%20Part%201/07.%20My%20Name%20Is%20Allen.mp3");
            songs.add("http://degree:Fcnhjabpbrf95@217.197.0.52:83/owncloud/remote.php/webdav/Music/Guns%20N'%20Roses/1987%20-%20Appetite%20For%20Destruction/01.%20Welcome%20To%20The%20Jungle.mp3");
            songs.add("http://degree:Fcnhjabpbrf95@217.197.0.52:83/owncloud/remote.php/webdav/Music/Stone%20Sour/2012%20-%20House%20Of%20Gold%20And%20Bones%20-%20Part%201/09.%20Influence%20Of%20A%20Drowsy%20God.mp3");

            myMediaPlayer.setSongList(songs);

            musicBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            musicBound = false;
        }
    };


    @Override
    public void onStart(){
        Log.d(TAG, "on start");
        super.onStart();

        if (playIntent == null){
            Log.d(TAG, "create play intent");
            playIntent = new Intent(this, MediaPlayerService.class);
            bindService(playIntent, musicConnection, Context.BIND_AUTO_CREATE);
            startService(playIntent);
        }
    }

    @Override
    protected void onDestroy() {
        Log.d(TAG, "on destroy");
        stopService(playIntent);
        myMediaPlayer = null;
        super.onDestroy();
    }


    public void play() {
        Log.d(TAG, "play");
        myMediaPlayer.play();
    }

    public MediaPlayerService getMediaPlayerService() {
        Log.d(TAG, "getMediaPlayerService");
        return myMediaPlayer;
    }

}
