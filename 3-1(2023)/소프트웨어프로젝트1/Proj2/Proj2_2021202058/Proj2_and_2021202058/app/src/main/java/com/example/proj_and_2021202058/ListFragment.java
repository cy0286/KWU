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
import android.widget.ListView;
import android.widget.TextView;

public class ListFragment extends Fragment {

    private ListView listview;

    @Nullable
    @Override
    public ListView onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // 레이아웃 파일을 inflate하여 GridView 초기화
        listview = (ListView)inflater.inflate(R.layout.fragment_list_, container, false);
        // 리스트 어댑터 생성
        ListFragment.ListAdapter listAdapter = new ListFragment.ListAdapter(getActivity());
        // 리스트뷰에 어댑터 설정
        listview.setAdapter(listAdapter);
        // 리스트 뷰 반환
        return listview;
    }

    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        // 추가적인 뷰 설정이나 초기화 수행
    }

    public class ListAdapter extends BaseAdapter {
        Context context;
        String[] text = {
                "test1","test2","test3","test4","test5","test6",
                "test7","test8","test9","test10","test11","test12","test13","test14","test15"

        };
        public ListAdapter(Context c){
            context = c; // 어댑터의 생성자
        }
        public int getCount(){
            return text.length; // 아이템 개수 반환
        }
        public Object getItem(int position){
            return text[position]; // 해당 위치의 아이템 반환
        }
        public long getItemId(int position){
            return position; // 아이템 ID 반환
        }
        public View getView(int position,View convertView,ViewGroup parent){
            // 텍스트뷰 생성
            TextView textView = new TextView(context);
            // 텍스트 설정
            textView.setText(text[position]);
            // 텍스트 크기 설정
            textView.setTextSize(65);
            // 설정된 텍스트뷰 반환
            return textView;
        }
    }
}