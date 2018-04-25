# AndroidNDK


## 开发工具: Android Studio

**开发环境: Mac OS**

> 功能简介:
-  导入
```
 static {
		System.loadLibrary("jni");//so 名称
	}
```
- java传递数据给c语言
```
	public native String getString();

	/**
	 * Java把字符串传递给c,c处理后还给java
	 * @param s
	 * @return
	 */
	public native String getString(String s);

	/**
	 * Java把两个int给c语言,c语言处理完还给java
	 * @param i
	 * @param j
	 * @return
	 */
	public native int getInt(int i, int j);

	/**
	 * Java把int数组给c语言, c语言把数组的元素+10,返回给java
	 * @param num
	 * @return
	 */
	public native int[] getIntArray(int[] num);
``
- c传递数据给java语言
```
	public native void callGet();

	/**
	 * C调用Java空方法
	 */
	public void getFromJava() {
		Log.e("getFromJava", "C调用Java空方法");
		if (callJNIBack != null)
			callJNIBack.callBack("C调用Java空方法");
	}

	public native void callSetString();

	/**
	 * C调用Java中带有一个string参数的方法
	 * @param s
	 */
	public void setStringFromJava(String s) {
		Log.e("setStringFromJava", "C调用Java中带有一个string参数的方法");
		if (callJNIBack != null)
			callJNIBack.callBack("C调用Java中string参数的方法:" + s);
	}

	public native void callGetInt();

	/**
	 * C调用Java中两个int参数方法
	 * @param i
	 * @param j
	 * @return
	 */
	public int getIntFromJava(int i, int j) {
		int sum = i + j;
		Log.e("getIntFromJava", "C调用Java中两个int参数方法:" + sum);
		if (callJNIBack != null)
			callJNIBack.callBack("C调用Java中两个int参数方法:" + sum);
		return sum;
	}
```
- 代码回调
```
	public interface CallJNIBack {
		void callBack(String s);
	}

	public void setCallJNIBack(CallJNIBack callJNIBack) {
		this.callJNIBack = callJNIBack;
	}
```
**备注:** [ReadMe.md使用规范](https://www.jianshu.com/p/q81RER)
