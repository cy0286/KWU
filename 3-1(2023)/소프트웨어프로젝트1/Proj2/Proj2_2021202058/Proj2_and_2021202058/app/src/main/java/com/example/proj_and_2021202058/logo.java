package com.example.proj_and_2021202058;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

public class logo extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_logo);

        // 로고 화면이 표시되는 동안 지연(2초) 후 MainActivity로 이동하는 핸들러 설정
        Handler handler = new Handler();
        handler.postDelayed(new Runnable(){
            @Override
            public void run() {
                // MainActivity로 이동하는 Intent 생성
                Intent intent = new Intent (getApplicationContext(), MainActivity.class);
                startActivity(intent);
                // 현재 액티비티 종료
                finish();
            }
        },2000); // 2초의 지연 시간 설정
    }
    @Override
    protected void onPause(){ // 액티비티가 일시 정지되면
        super.onPause();
        finish(); // 액티비티 종료
    }
}