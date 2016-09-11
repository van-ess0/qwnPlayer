package org.qwnplayer.qwnplayer;
import org.qtproject.qt5.android.addons.qtactivityapp.QtService;
import android.util.Log;

import java.lang.Override;

public class qwnPlayerService extends QtService
{
    @Override
    public void onCreate()
    {
        Log.w(getClass().getName(), "Starting config editor service");
        super.setActivityClass(qwnPlayerActivity.class);
        super.onCreate();
    }
}
