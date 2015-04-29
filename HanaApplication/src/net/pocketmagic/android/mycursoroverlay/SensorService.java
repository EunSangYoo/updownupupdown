package net.pocketmagic.android.mycursoroverlay;

import java.util.List;

import android.app.ActivityManager;
import android.app.Service;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class SensorService extends Service{
	static { System.loadLibrary("hana"); }
	
	boolean m_bRunning = false;
	int accelXValue;
	int accelYValue;
	int ix, iy;
	Input input = new Input();
	boolean proxiValue=false;
	
	private SensorManager mSensorManager;
	private Sensor accSensor;
	private Sensor proxSensor; 
	
	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return null;
	}
	public void onStart(Intent intent, int startId) {
		 
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		accSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		proxSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT); 
		
		SensorEventListener mySensorListener = new SensorEventListener(){
			public void onSensorChanged(SensorEvent event){
				Sensor sensor = event.sensor;
				if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER){
					accelXValue = (int) event.values[0];
					accelYValue = (int) event.values[1];
				}else if(event.sensor.getType() == Sensor.TYPE_LIGHT){
					Log.d("debug", "event.values[0] = " + event.values[0]);
					if(event.values[0]>10) return;
					// Toast.makeText(getApplicationContext(),"Touch", Toast.LENGTH_LONG).show();
					input.testGesture(ix, iy);
				}
			}
			public void onAccuracyChanged(Sensor sensor, int accuracy) {
				// TODO Auto-generated method stub
			}
		};
		
		mSensorManager.registerListener(mySensorListener, accSensor, 
				SensorManager.SENSOR_DELAY_FASTEST);
		mSensorManager.registerListener(mySensorListener, proxSensor, 
				SensorManager.SENSOR_DELAY_FASTEST);
	
		//Toast.makeText(getApplicationContext(),"Hello", Toast.LENGTH_LONG).show();
		int last_x = 0, last_y = 0;
		int new_x, new_y;
		m_bRunning = true;
		
		Thread t = new Thread(){
			int last_x = 0, last_y = 0;
			int new_x, new_y;
			public void run() 
		        {		
					while (m_bRunning) {
						new_x = 1530; new_y = 1930;
						//int ix = new_x/2, iy = new_y/2;
						ix = new_x/2;
						iy = new_y/2;
						while ((ix!=new_x || iy!=new_y) && m_bRunning) {
							
							ix -= accelXValue;
							if(ix<0) ix=1;
							if(ix>1530) ix=1529;
							
							iy += accelYValue;
							if(iy<0) iy=1;
							// if(iy>1930) iy=1929;
							if (iy>2200) iy = 2199;
							
							if(Singleton.getInstance().m_CurService!=null)
								Singleton.getInstance().m_CurService.Update(ix, iy, true);
							try {
								Thread.sleep(5);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}

						}
						last_x = new_x; last_y = new_y;
						
					}
					
		        }
		};
		t.start();
	}
	
	public void onDestroy() {

	}
	/*
	public void onSensorChanged(SensorEvent event) {
		// TODO Auto-generated method stub
		Sensor sensor = event.sensor;
		if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER){
			accelXValue = (int) event.values[0];
			accelYValue = (int) event.values[1];
		}
	}
	*/

}
