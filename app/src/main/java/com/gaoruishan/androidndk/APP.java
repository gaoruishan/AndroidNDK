package com.gaoruishan.androidndk;

import android.app.Application;
import android.content.Context;

/**
 * @作者:gaoruishan
 * @时间:2016/9/27/16:01
 * @邮箱:grs0515@163.com
 */
public class APP extends Application {

	private static APP ourInstance = new APP();
	private Context mContext;

	public static APP getInstance() {
		return ourInstance;
	}

	public Context getContext() {
		return mContext;
	}

	@Override
	public void onCreate() {
		super.onCreate();
		mContext = this;
	}
}
