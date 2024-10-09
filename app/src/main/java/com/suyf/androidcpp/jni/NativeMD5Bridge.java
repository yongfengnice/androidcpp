package com.suyf.androidcpp.jni;

/**
 * @author：yongfeng
 * @data：2024/9/19 17:19
 */
public class NativeMD5Bridge {

    public static native String calculateMD5(String origin);

    public static native String calOpensslMd5(String origin);
}
