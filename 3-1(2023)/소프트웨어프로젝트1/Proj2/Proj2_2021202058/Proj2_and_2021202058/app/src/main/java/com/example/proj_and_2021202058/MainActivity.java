package com.example.proj_and_2021202058;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.google.android.material.bottomnavigation.BottomNavigationView;

public class MainActivity extends AppCompatActivity {

    private BottomNavigationView mBottomNV; // BottomNavigationView 객체 선언

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // activity_main 레이아웃 설정

        mBottomNV = findViewById(R.id.nav_view); // BottomNavigationView 초기화
        mBottomNV.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                BottomNavigate(menuItem.getItemId()); // BottomNavigationView의 아이템 선택 이벤트 처리
                return true;
            }
        });

        mBottomNV.setSelectedItemId(R.id.navigation_1); // 초기에 첫 번째 아이템 선택

        Button UploadButton = (Button) findViewById(R.id.UploadButton);
        UploadButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(),Upload.class); // Upload 액티비티로 이동하는 버튼 클릭 이벤트 처리
                startActivity(intent);
            }
        });
    }

    private void BottomNavigate(int id){
        String tag = String.valueOf(id); // 아이템 ID를 문자열로 변환하여 tag로 사용
        FragmentManager fragmentManager = getSupportFragmentManager(); // FragmentManager 객체 가져오기
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction(); // FragmentTransaction 객체 생성

        Fragment currentFragment = fragmentManager.getPrimaryNavigationFragment(); // 현재 표시되는 프래그먼트 가져오기
        if (currentFragment != null) {
            fragmentTransaction.remove(currentFragment); // 현재 프래그먼트 제거
        }

        Fragment fragment = fragmentManager.findFragmentByTag(tag); // 태그로 해당 프래그먼트 찾기
        if (fragment == null) {
            if (id == R.id.navigation_1) {
                fragment = new ImageFragment(); // 아이템 ID에 따라 해당하는 프래그먼트 생성
            } else if (id == R.id.navigation_2){
                fragment = new ListFragment(); // 아이템 ID에 따라 해당하는 프래그먼트 생성
            }else {
                fragment = new SettingFragment(); // 아이템 ID에 따라 해당하는 프래그먼트 생성
            }

            fragmentTransaction.add(R.id.content_layout, fragment, tag);
        } else {
            fragmentTransaction.show(fragment); // 프래그먼트를 보여줌
        }

        fragmentTransaction.setPrimaryNavigationFragment(fragment); // 프래그먼트를 현재 표시되는 프래그먼트로 설정
        fragmentTransaction.setReorderingAllowed(true); // 프래그먼트 재정렬 허용
        fragmentTransaction.commitNow(); // 변경사항 즉시 커밋
    }
}
