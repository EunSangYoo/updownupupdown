package net.pocketmagic.android.mycursoroverlay;

import java.util.Random;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import android.os.Bundle;
import android.app.Activity;
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
	static Intent Service_i;
	static boolean flag = true;

	RelativeLayout m_panel;
	
	boolean m_bRunning = false;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        m_panel  = new RelativeLayout(this);
        m_panel.setBackgroundResource(R.drawable.back);
        setContentView(m_panel);
        
        // build a minimalistic interface
        LinearLayout panelV = new LinearLayout(this);
        panelV.setOrientation(LinearLayout.VERTICAL);
        RelativeLayout.LayoutParams lp_iv = new RelativeLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		lp_iv.addRule(RelativeLayout.CENTER_IN_PARENT);
		m_panel.addView(panelV, lp_iv);
		
        Button bStop = new Button(this);
        Service_i = new Intent(getApplicationContext(), SensorService.class);
        bStop.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Toast.makeText(getApplicationContext(),"Hello", Toast.LENGTH_LONG).show();
				
				if(flag){
					flag = false;
					startService(Service_i);
					System.exit(0);
				}
			}
		});
        
        bStop.setText("STOP");
        panelV.addView(bStop);
        
        
        Button bHide = new Button(this);
        bHide.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Toast.makeText(getApplicationContext(),"Hi touch", Toast.LENGTH_LONG).show();
			}
		});
        bHide.setText("HIDE");
        panelV.addView(bHide);
        
        DisplayMetrics metrics = new DisplayMetrics();
		try {
			WindowManager winMgr = (WindowManager)getSystemService(Context.WINDOW_SERVICE) ;
	       	winMgr.getDefaultDisplay().getMetrics(metrics);
		}
		catch (Exception e) { //default to a HVGA 320x480 and let's hope for the best
			e.printStackTrace();
		} 

        // start cursor service
		cmdTurnCursorServiceOn();
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
 
