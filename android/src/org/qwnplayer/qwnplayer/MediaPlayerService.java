package org.qwnplayer.qwnplayer;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.net.Uri;

import android.net.wifi.WifiManager;
import android.os.Binder;
import android.os.IBinder;
import android.os.PowerManager;
import android.util.Log;

import java.io.IOException;

import android.util.Base64;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;


public class MediaPlayerService extends Service {

    // Native callback functions for MediaPlayerService
    native public void onBufferingUpdateNative(int percent);
    native public void onProgressUpdateNative(int progress);
    native public void onDurationChangedNative(int duration);
    native public void onErrorNative(int what, int extra);
    native public void onInfoNative(int what, int extra);
    native public void onStateChangedNative(int state);

    // Player State
    private class State {
        final static int Uninitialized = 0x1 /* End */;
        final static int Idle = 0x2;
        final static int Preparing = 0x4;
        final static int Prepared = 0x8;
        final static int Initialized = 0x10;
        final static int Started = 0x20;
        final static int Stopped = 0x40;
        final static int Paused = 0x80;
        final static int PlaybackCompleted = 0x100;
        final static int Error = 0x200;
    }

    private volatile int mState = State.Uninitialized;

    /**
     * MediaPlayer OnBufferingListener
     */
    private class MediaPlayerBufferingListener
    implements MediaPlayer.OnBufferingUpdateListener
    {
        private int mBufferPercent = -1;
        @Override
        public void onBufferingUpdate(final android.media.MediaPlayer mp,
                                      final int percent)
        {
            Log.d(TAG, "on buffering update");
            // Avoid updates when percent is unchanged.
            // E.g., we keep getting updates when percent == 100
            if (mBufferPercent == percent)
                return;

            onBufferingUpdateNative((mBufferPercent = percent));
        }

    }

    /**
     * MediaPlayer OnSeekCompleteListener
     */
    private class MediaPlayerSeekCompleteListener
    implements MediaPlayer.OnSeekCompleteListener
    {

        @Override
        public void onSeekComplete(final MediaPlayer mp)
        {
            Log.d(TAG, "on seek complete");
            onProgressUpdateNative(getCurrentPosition());
        }
    }

    /**
     * MediaPlayer OnCompletionListener
     */
    private class MediaPlayerCompletionListener
    implements MediaPlayer.OnCompletionListener
    {
        @Override
        public void onCompletion(final MediaPlayer mp) {

            Log.d(TAG, "on completion");
            ++index;
            if (index >= songs.size()) {
                return;
            }

            String path = songs.get(index);
            setDataSource(path);
            mediaPlayer.prepareAsync();

            setState(State.PlaybackCompleted);
        }
    }

    /**
     * MediaPlayer OnPreparedListener
     */
    private class MediaPlayerPreparedListener
    implements MediaPlayer.OnPreparedListener
    {
        @Override
        public void onPrepared(MediaPlayer mp) {
            Log.d(TAG, "on prepared");
            mp.start();
            wifiLock.acquire();

            setState(State.Prepared);
            onDurationChangedNative(getDuration());
        }
    }

    /**
     * MediaPlayer OnErrorListener
     */
    private class MediaPlayerErrorListener
    implements MediaPlayer.OnErrorListener
    {
        @Override
        public boolean onError(final MediaPlayer mp,
                               final int what,
                               final int extra)
        {
            Log.d(TAG, "on error");
            setState(State.Error);
            onErrorNative(what, extra);
            return true;
        }

    }

    /**
     * MediaPlayer OnInfoListener
     */
    private class MediaPlayerInfoListener
    implements MediaPlayer.OnInfoListener
    {
        @Override
        public boolean onInfo(final MediaPlayer mp,
                              final int what,
                              final int extra)
        {
            Log.d(TAG, "on info");
            onInfoNative(what, extra);
            return true;
        }

    }

    // Change state if needed
    private void setState(int state)
    {
        Log.d(TAG, "set state");
        if (mState == state)
            return;

        mState = state;
        onStateChangedNative(mState);
    }

    // Get current position
    public int getCurrentPosition()
    {
        Log.d(TAG, "get current position");
        int currentPosition = 0;
        if ((mState & (State.Idle
                       | State.Initialized
                       | State.Prepared
                       | State.Started
                       | State.Paused
                       | State.Stopped
                       | State.PlaybackCompleted)) == 0) {
            return currentPosition;
        }

        try {
            currentPosition = mediaPlayer.getCurrentPosition();
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }

        return currentPosition;
    }

    // Get duration
    public int getDuration()
    {
        int duration = 0;
        if ((mState & (State.Prepared
                       | State.Started
                       | State.Paused
                       | State.Stopped
                       | State.PlaybackCompleted)) == 0) {
            return duration;
        }

        try {
            duration = mediaPlayer.getDuration();
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }

        return duration;
    }

    private final IBinder musicBind = new MusicBinder();
    private ArrayList<String> songs = null;
    private int index = 0;

    public void setSongList(ArrayList<String> list) {
        Log.d(TAG, "set songs");
        songs = list;
    }

    public class MusicBinder extends Binder {
        MediaPlayerService getService() {
            Log.d(TAG, "get service");
            return MediaPlayerService.this;
        }
    }

    public MediaPlayerService() {
        Log.d(TAG, "Construct service");
    }

    @Override
    public void onCreate() {
        Log.d(TAG, "on create service");
        super.onCreate();
        mediaPlayer = new MediaPlayer();
        init();

//        Log.d(TAG, "test native call: WHAT=11 EXTRA=1546");
//        onErrorNative(11, 1546);
    }

    public void init(){
        Log.d(TAG, "init media player service");

        setState(State.Idle);

        mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);

//        // Make sure the new media player has the volume that was set on the QMediaPlayer
//        setVolumeHelper(mMuted ? 0 : mVolume);

        mediaPlayer.setOnBufferingUpdateListener(new MediaPlayerBufferingListener());
        mediaPlayer.setOnSeekCompleteListener(new MediaPlayerSeekCompleteListener());
        mediaPlayer.setOnCompletionListener(new MediaPlayerCompletionListener());
        mediaPlayer.setOnPreparedListener(new MediaPlayerPreparedListener());
        mediaPlayer.setOnErrorListener(new MediaPlayerErrorListener());
        mediaPlayer.setOnInfoListener(new MediaPlayerInfoListener());

        // Hold on CPU when smartphone is idle.
        // WAKE_LOCK permission is requiered
        mediaPlayer.setWakeMode(getApplicationContext(), PowerManager.PARTIAL_WAKE_LOCK);

        // Preventing wifi module when smartphone is idle.
        // Use wifiLock.acquire() to prevent
        // Use wifiLock.release() to disable preventing (pause, stop)
        wifiLock = ((WifiManager) getSystemService(Context.WIFI_SERVICE)).
                                    createWifiLock(WifiManager.WIFI_MODE_FULL, "MediaPlayerServiceLock");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d(TAG, "on bind");
        return musicBind;
    }

    @Override
    public boolean onUnbind(Intent intent){
        Log.d(TAG, "on unbind");
        mediaPlayer.stop();
        mediaPlayer.release();
        wifiLock.release();
        return false;
    }

    private MediaPlayer mediaPlayer;
    WifiManager.WifiLock wifiLock;

    private static final String TAG = "MediaPlayerService";

    public void play() {
        Log.d(TAG, "play in service");
        String path = songs.get(index);
        setDataSource(path);
        mediaPlayer.prepareAsync();
    }

    public void start()
    {
        if ((mState & (State.Prepared
                       | State.Started
                       | State.Paused
                       | State.PlaybackCompleted)) == 0) {
            return;
        }

        try {
            Log.d(TAG, "AAAA START");
            setState.start();
            setState(State.Started);
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }
    }

    public void pause()
    {
        if ((mState & (State.Started
                       | State.Paused
                       | State.PlaybackCompleted)) == 0) {
            return;
        }

        try {
            Log.d(TAG, "AAAA PAUSE");
            mediaPlayer.pause();
            setState(State.Paused);
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }
    }

    public void stop()
    {
        if ((mState & (State.Prepared
                       | State.Started
                       | State.Stopped
                       | State.Paused
                       | State.PlaybackCompleted)) == 0) {
            return;
        }

        try {
            Log.d(TAG, "AAAA STOP");
            mediaPlayer.stop();
            setState(State.Stopped);
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }
    }

    public void seekTo(final int msec)
    {
        if ((mState & (State.Prepared
                       | State.Started
                       | State.Paused
                       | State.PlaybackCompleted)) == 0) {
            return;
        }

        try {
            Log.d(TAG, "AAAA SEEK TO");
            mediaPlayer.seekTo(msec);
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }
    }

    public boolean isPlaying()
    {
        boolean playing = false;
        if ((mState & (State.Idle
                       | State.Initialized
                       | State.Prepared
                       | State.Started
                       | State.Paused
                       | State.Stopped
                       | State.PlaybackCompleted)) == 0) {
            return playing;
        }

        try {
            Log.d(TAG, "AAAA IS PLAYING");
            playing = mediaPlayer.isPlaying();
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }

        return playing;
    }

    public void prepareAsync()
    {
        if ((mState & (State.Initialized
                       | State.Stopped)) == 0) {
           return;
        }

        try {
            Log.d(TAG, "AAAA PREPARE ASYNC");
            mediaPlayer.prepareAsync();
            setState(State.Preparing);
        } catch (final IllegalStateException e) {
            Log.d(TAG, "" + e.getMessage());
        }
    }

    public void setDataSource(String path) {
        Log.d(TAG, "set data source");
        Uri uri = Uri.parse(path);

        mediaPlayer.reset();

        try {
            // Check for authority headers
            if (uri.getUserInfo() != null) {
                Log.d(TAG, "protected link");

                // Take userinfo from url path
                // path example: http://user:passwd@host
                Map<String, String> headers = getHeaders(uri.getUserInfo());

                // Use java reflection call the hide API:
                Method method = mediaPlayer.getClass().getMethod("setDataSource", Context.class, Uri.class, Map.class);
                method.invoke(mediaPlayer, getApplicationContext(), uri, headers);
            }
            else {
                Log.d(TAG, "not protected link");
                mediaPlayer.setDataSource(getApplicationContext(), uri);
            }
        } catch (IOException e){
            Log.d(TAG, e.getMessage());
        } catch (IllegalAccessException e) {
            Log.d(TAG, e.getMessage());
        } catch (InvocationTargetException e) {
            Log.d(TAG, e.getMessage());
        } catch (NoSuchMethodException e) {
            Log.d(TAG, e.getMessage());
        }
    }

    private Map<String, String> getHeaders(String userInfo) {
        Log.d(TAG, "get headers");

        Map<String, String> headers = new HashMap<String, String>();

        // Split userinfo by ":"
        String[] arrayTemp = new String[2];
        arrayTemp = userInfo.split(":");

        String basicAuthValue = getBasicAuthValue(arrayTemp[0], arrayTemp[1]);
        headers.put("Authorization", basicAuthValue);
        return headers;
    }

    private String getBasicAuthValue(String usr, String pwd) {
        Log.d(TAG, "get basic auth");

        String credentials = usr + ":" + pwd;
        int flags = Base64.URL_SAFE | Base64.NO_WRAP;
        byte[] bytes = credentials.getBytes();
        return "Basic " + Base64.encodeToString(bytes, flags);
    }

}
