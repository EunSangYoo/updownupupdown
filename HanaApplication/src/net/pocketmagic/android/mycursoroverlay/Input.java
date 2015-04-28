package net.pocketmagic.android.mycursoroverlay;

import android.app.Instrumentation;
import android.os.SystemClock;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.Toast;

public class Input {

	static { System.loadLibrary("hana"); }
	public native void hanaInput(int x, int y);

	public void testGesture(final int x, final int y) {
		//final Instrumentation inst = new Instrumentation();
		Log.i("Input", "thread outside");
		new Thread() {
			public void run() {
				hanaInput(x,y);
			}
		}.start();

	}

}
