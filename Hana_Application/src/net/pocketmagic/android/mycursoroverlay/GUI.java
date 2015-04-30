package net.pocketmagic.android.mycursoroverlay;

import java.util.List;
import java.util.Random;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.support.v4.app.NavUtils;

public class GUI extends Activity{
    private SoundPool sound_pool; 
    private int sound_beep;

    
	static Intent Service_i;
	static boolean flag = true;

	RelativeLayout m_panel;
	
	boolean m_bRunning = false;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Service_i = new Intent(getApplicationContext(), SensorService.class);
        // start cursor service
		cmdTurnCursorServiceOn();
		startService(Service_i);
		
		MediaPlayer player;
		player = MediaPlayer.create(this, R.raw.sound2);
		player.start();

		//android.os.Process.killProcess(mypid);
		//System.exit(0);
		Intent newActivity = new Intent(Intent.ACTION_MAIN); 
		newActivity.addCategory(Intent.CATEGORY_HOME);
		newActivity.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(newActivity);
    }
    /* onDestroy - called when the app is closed */
	@Override public void onDestroy() {
		super.onDestroy();
		Log.d("GUI", "onDestroy called");
		m_bRunning = false;
		// close our cursor service
		//cmdTurnCursorServiceOff();
	}
	

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_gui, menu);
        return true;
    }
    
    /*
     * 	HELPER CURSOR FUNCTIONS
     */
	private void cmdTurnCursorServiceOn() {	
       	Intent i = new Intent();
        i.setAction("net.pocketmagic.android.mycursoroverlay.CursorService");
        startService(i);
	}
	
	private void cmdTurnCursorServiceOff() {
		Intent i = new Intent();
        i.setAction("net.pocketmagic.android.mycursoroverlay.CursorService");
        stopService(i);
	}
	
	private void cmdShowCursor() {
		if (Singleton.getInstance().m_CurService != null)
			Singleton.getInstance().m_CurService.ShowCursor(true);
	}
	
	private void cmdHideCursor() {
		if (Singleton.getInstance().m_CurService != null)
			Singleton.getInstance().m_CurService.ShowCursor(false);
	}
    
}
/*
 * java.lang.RuntimeException: Unable to create service net.pocketmagic.android.mycursoroverlay.CursorService: 
 * android.view.WindowManager$BadTokenException: Unable to add window android.view.ViewRoot$W@464d9bf8 -- 
 * permission denied for this window type
 * needs: 	<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
 */
 
