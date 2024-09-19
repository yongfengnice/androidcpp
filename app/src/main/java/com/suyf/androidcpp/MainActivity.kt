package com.suyf.androidcpp

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.suyf.androidcpp.databinding.ActivityMainBinding
import com.suyf.androidcpp.jni.NativeCjsonBridge
import com.suyf.androidcpp.jni.NativeMD5Bridge

class MainActivity : AppCompatActivity() {

    companion object {
        init {
            System.loadLibrary("androidcpp")
        }
    }

    private lateinit var binding: ActivityMainBinding

    private val testJson = """
            {
                "address": "guangzhou",
                "age": 30,
                "name": "zhangsan"
            }
        """.trim()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.sampleText.text = stringFromJNI()

        binding.callMd5.setOnClickListener {
            Log.d("Suyf", "onCreate: ${NativeMD5Bridge.calculateMD5("hello,cpp")}")
            Log.d("Suyf", "onCreate: ${NativeMD5Bridge.calculateMD5("hello,world")}")
        }

        binding.callParseJson.setOnClickListener {
            NativeCjsonBridge.parseJson(testJson)
        }

    }

    private external fun stringFromJNI(): String

}