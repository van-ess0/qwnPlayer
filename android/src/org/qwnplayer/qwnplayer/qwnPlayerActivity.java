package org.qwnplayer.qwnplayer;
import org.qtproject.qt5.android.addons.qtactivityapp.QtServiceActivity;
import org.qtproject.qt5.android.addons.qtactivityapp.QtService;
import android.os.Bundle;
import android.content.Intent;
import android.content.ComponentName;
import android.util.Log;

import java.lang.Override;

public class qwnPlayerActivity extends QtServiceActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        Log.w(getClass().getName(), "Starting config editor");
        super.setServiceClass(qwnPlayerService.class);
        super.onCreate(savedInstanceState);
    }
}
