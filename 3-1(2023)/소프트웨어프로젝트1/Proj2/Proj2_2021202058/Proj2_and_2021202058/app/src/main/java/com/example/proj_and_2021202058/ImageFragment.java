package com.example.proj_and_2021202058;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

public class ImageFragment extends Fragment {

    private GridView gridview;

    @Nullable
    @Override
    public GridView onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // 레이아웃 파일을 inflate하여 GridView 초기화
        gridview = (GridView)inflater.inflate(R.layout.fragment_image, container, false);
        // 커스텀 그리드 어댑터의 인스턴스 생성
        ImageAdapter gridAdapter = new ImageAdapter(getActivity());
        // 그리드 뷰에 어댑터를 설정
        gridview.setAdapter(gridAdapter);
        // 그리드 뷰 반환
        return gridview;
    }

    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        // 추가적인 뷰 설정이나 초기화 수행
    }

    public class ImageAdapter extends BaseAdapter{
        Context context;
        Integer[] images = {
                R.drawable.r1,R.drawable.r2,R.drawable.r3,
                R.drawable.r4,R.drawable.r5,R.drawable.r6,
                R.drawable.r7,R.drawable.r8,R.drawable.r9,
                R.drawable.r10,R.drawable.r11,R.drawable.r12,
                R.drawable.r13,R.drawable.r14,R.drawable.r15
        };
        public ImageAdapter(Context c){
            context = c; // 어댑터의 생성자
        }
        public int getCount(){
            return images.length; // 아이템 개수 반환
        }
        public Object getItem(int position){
            return images[position]; // 해당 위치의 아이템 반환
        }
        public long getItemId(int position){
            return position; // 아이템 ID 반환
        }

        public View getView(int position,View convertView,ViewGroup parent){ // 각 아이템의 뷰 반환
            ImageView imageView = new ImageView(context);
            imageView.setLayoutParams(new ViewGroup.LayoutParams(400,340));
            imageView.setScaleType(ImageView.ScaleType.FIT_XY);
            // 현재 위치에 해당하는 이미지의 리소스를 설정
            imageView.setImageResource(images[position]);
            // 설정된 이미지 뷰 반환
            return imageView;
        }
    }
}