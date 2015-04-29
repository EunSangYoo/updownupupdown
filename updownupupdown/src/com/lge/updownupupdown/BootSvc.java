package com.lge.updownupupdown;

import java.util.List;


import android.app.ActivityManager;
import android.app.Service;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.widget.Toast;


public class BootSvc extends Service implements OnKeyListener{
	  
	int ret;
	static boolean flag=false;
	static
	{
	    System.loadLibrary("pattern_check");
	}
	
	native int pattern_check();
	
	public class receiver extends BroadcastReceiver{
		
		@Override
		public void onReceive(Context context, Intent intent) {
			Toast.makeText(getApplicationContext(), "hello", 0).show();
			Log.e("TAG", "Media Button");
			if(intent.getAction() == Intent.ACTION_MEDIA_BUTTON){
				Log.e("TAG", "Media Button");
			}
		}
	};
	
	@Override
	  public IBinder onBind(Intent intent) {
	    return null;
	  }

	@Override
	public void onCreate(){
		
		Toast.makeText(getApplicationContext(), "UpDown ON!", 0).show();
		IntentFilter filter = new IntentFilter();
		filter.addAction(Intent.ACTION_MEDIA_BUTTON);
		AudioManager am = (AudioManager)getSystemService(AUDIO_SERVICE);
		am.registerMediaButtonEventReceiver(new ComponentName(getPackageName(),receiver.class.getName()));
		
	}
	
	@Override
	public void onDestroy(){
		AudioManager am = (AudioManager)getSystemService(AUDIO_SERVICE);
		am.unregisterMediaButtonEventReceiver(new ComponentName(getPackageName(),receiver.class.getName()));
	}
	
	public Runnable run1 = new Runnable() {
		
		@Override
		public void run() {
			
			ret = pattern_check();
			Log.e("tag", String.valueOf(ret));
			
			if( ((ret >> 8)&0xFF) == 0xaa )
			{
				if(!flag){
					Intent launchIntent = getPackageManager().getLaunchIntentForPackage("net.pocketmagic.android.mycursoroverlay");
					startActivity(launchIntent);
					flag = true;
				}else{
					Intent i = new Intent();
				    i.setAction("net.pocketmagic.android.mycursoroverlay.SensorService");
				    stopService(i);
				    
					Intent i2 = new Intent();
				    i2.setAction("net.pocketmagic.android.mycursoroverlay.CursorService");
				    stopService(i2);
				    
					MediaPlayer player;
					player = MediaPlayer.create(getApplicationContext(), R.raw.sound2);
					player.start();
					
				    flag = false;
				    
				}
			}

			new Handler().postDelayed(run1, 1000);
		}
	};
	
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		
		  Log.i("BOOTSVC", "Service started at the BOOT_COMPLETED.");
//		  Toast.makeText(getApplicationContext(), "onStartCommand", 0).show();
		  new Handler(Looper.getMainLooper()).post(run1);
								  
		  return START_STICKY;
	}

	@Override
	public boolean onKey(View v, int keyCode, KeyEvent event) {
	     if (event.getAction() == KeyEvent.ACTION_DOWN) 
	     {
	    	 
	        switch(keyCode) 
            {

                default:
                	Toast.makeText(getApplicationContext(), "Key", 0).show();
                break;
            }
        }
	     
		return false;

	} 	  
	
}

