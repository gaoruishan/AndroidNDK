package com.gaoruishan.androidndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements JNI.CallJNIBack{

	private JNI jni;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		jni = new JNI();
		jni.setCallJNIBack(this);
	}

	/**
	 * 获得C字符串
	 * @param view
	 */
	public void getStringFromC(View view) {
		show(jni.getString());
	}

	/**
	 * 获得处理后的C字符串
	 * @param view
	 */
	public void getDealStringFromC(View view) {
		show(jni.getString("java"));
	}

	/**
	 * 获得处理两个int相加
	 * @param view
	 */
	public void getAddIntFromC(View view) {
		show("结果：" + jni.getInt(2, 3));
	}

	/**
	 * 获得处理两个int相加
	 * @param view
	 */
	public void getAddArrayFromC(View view) {
		String s = new String(), s1 = new String();
		int arr[] = {1, 2, 3, 4, 5};
		int newArr[] = jni.getIntArray(arr);
		for (int i = 0; i < arr.length; i++) {
			s += arr[i] + " ";
			s1 += newArr[i] + " ";
		}
		show(s + "->结果：" + s1);
	}

	/**
	 * C调用Java空方法
	 * @param view
	 */
	public void callGet(View view) {
		jni.callGet();
	}

	/**
	 * C调用Java中带有一个string参数的方法
	 * @param view
	 */
	public void callSetString(View view) {
		jni.callSetString();
	}

	/**
	 * C调用Java中两个int参数方法
	 * @param view
	 */
	public void callGetInt(View view) {
		jni.callGetInt();
	}

	//	显示
	private void show(String s) {
		Toast.makeText(this, s, Toast.LENGTH_SHORT).show();
	}

	@Override
	public void callBack(String s) {
		show(s);
	}
}
