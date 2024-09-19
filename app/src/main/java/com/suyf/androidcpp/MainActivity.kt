package com.suyf.androidcpp

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.blankj.utilcode.util.ToastUtils
import com.suyf.androidcpp.databinding.ActivityMainBinding
import com.suyf.androidcpp.jni.JavaMethodBridge
import com.suyf.androidcpp.jni.NativeMethodBridge

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.sampleText.text = stringFromJNI()

        binding.callJniMethod.setOnClickListener {
            ToastUtils.showShort(JavaMethodBridge.javaMethodName("java_name"))
        }
        binding.callMd5.setOnClickListener {
            NativeMethodBridge.callMd5()
        }
    }

    external fun stringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("androidcpp")
        }
    }
}