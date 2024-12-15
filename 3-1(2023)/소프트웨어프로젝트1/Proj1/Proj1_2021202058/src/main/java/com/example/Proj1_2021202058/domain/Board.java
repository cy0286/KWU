package com.example.Proj1_2021202058.domain;

import lombok.AccessLevel;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.data.annotation.LastModifiedDate;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import javax.persistence.*;
import java.time.LocalDate;

@Getter
@Entity
@NoArgsConstructor(access = AccessLevel.PROTECTED)
@EntityListeners(AuditingEntityListener.class)
public class Board {

    @Id
    @GeneratedValue
    private Long id; // 게시물 ID

    @Column(length = 20, nullable = false)
    private String title; // 게시물 제목

    @Column(columnDefinition = "TEXT", nullable = false)
    private String content; // 게시물 내용
    @Column(nullable = false)
    private String origFilename; // 원본 파일명

    @Column(nullable = false)
    private String filePath; // 파일 경로
    @CreatedDate
    @Column(updatable = false)
    private LocalDate createdDate; // 생성일자

    @LastModifiedDate
    private LocalDate modifiedDate; // 수정일자

    @Builder
    public Board(Long id, String title, String content, String origFilename, String filePath) {
        // Board 객체를 생성하는 빌더 메소드
        this.id = id;
        this.title = title;
        this.content = content;
        this.origFilename = origFilename;
        this.filePath = filePath;
    }
}