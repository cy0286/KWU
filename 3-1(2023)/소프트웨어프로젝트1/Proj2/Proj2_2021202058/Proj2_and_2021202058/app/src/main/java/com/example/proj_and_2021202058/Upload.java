package com.example.proj_and_2021202058;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class Upload extends AppCompatActivity {

    private ImageView imageView; // ImageView 객체 선언

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_upload); // activity_upload 레이아웃 설정

        imageView = findViewById(R.id.picture); // ImageView 초기화
        imageView.setOnClickListener(view -> openGallery()); // 이미지뷰 클릭 시 openGallery() 메서드 호출

        Button Returnbutton = findViewById(R.id.Return);
        Returnbutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish(); // 액티비티 종료 버튼 클릭 이벤트 처리
            }
        });
    }

    private void openGallery() {
        Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(intent, 1); // 갤러리 열기 위한 암시적 인텐트 실행 및 결과 처리
    }
}