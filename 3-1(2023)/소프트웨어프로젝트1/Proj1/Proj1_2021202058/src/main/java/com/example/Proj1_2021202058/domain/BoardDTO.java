package com.example.Proj1_2021202058.domain;

import lombok.*;
import java.time.LocalDate;

@Getter
@Setter
@ToString
@NoArgsConstructor
public class BoardDTO {
    private Long id; // 게시물 ID
    private String title; // 게시물 제목
    private String content; // 게시물 내용
    private String origFilename; // 원본 파일명
    private String filePath; // 파일 경로
    private LocalDate createdDate; // 생성일시
    private LocalDate modifiedDate; // 수정일시

    public Board toEntity() {
        // BoardDTO 객체를 Board 엔티티로 변환하는 메소드
        Board build = Board.builder()
                .id(id)
                .title(title)
                .content(content)
                .origFilename(origFilename)
                .filePath(filePath)
                .build();
        return build;
    }
    public int getTitlelen(){
        // 제목의 길이를 반환하는 메소드
        return title.length();
    }
    public int getContenttlen() {
        // 내용의 길이를 반환하는 메소드
        return content.length();
    }

    @Builder
    public BoardDTO(Long id, String title, String content, String origFilename, String filePath, LocalDate createdDate, LocalDate modifiedDate) {
        // BoardDTO 객체를 생성하는 빌더 메소드
        this.id = id;
        this.title = title;
        this.content = content;
        this.origFilename = origFilename;
        this.filePath = filePath;
        this.createdDate = createdDate;
        this.modifiedDate = modifiedDate;
    }
}