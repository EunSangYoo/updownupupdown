package com.lge.updownupupdown;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.KeyEvent;

public class BRcvr extends BroadcastReceiver {
	
  @Override
  public void onReceive(Context context, Intent intent) { 
    if ("android.intent.action.BOOT_COMPLETED".equals(intent.getAction())) {
      Log.i("BOOTSVC", "Intent received");    

      ComponentName cn = new ComponentName(context.getPackageName(), BootSvc.class.getName());
      ComponentName svcName = context.startService(new Intent("lge.test"));
      if (svcName == null) 
    	  Log.e("BOOTSVC", "Could not start service " + cn.toString());
    }
    else if("intent.action.MEDIA_BUTTON".equals(intent.getAction())){
    	KeyEvent event = (KeyEvent)intent.getParcelableExtra(Intent.EXTRA_KEY_EVENT);
    	if(KeyEvent.KEYCODE_VOLUME_UP == event.getKeyCode()){
    		Log.e("test", "volumeUp");
    		
    	}
    }
  }
}