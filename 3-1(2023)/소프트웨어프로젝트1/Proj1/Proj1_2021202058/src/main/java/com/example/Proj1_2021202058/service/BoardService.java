package com.example.Proj1_2021202058.service;

import com.example.Proj1_2021202058.domain.Board;
import com.example.Proj1_2021202058.domain.BoardDTO;
import com.example.Proj1_2021202058.repository.Repository;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.ArrayList;
import java.util.List;

@Service
public class BoardService {
    private Repository repository;

    public BoardService(Repository repository) {
        this.repository = repository;
    }

    @Transactional
    public Long saveFile(BoardDTO boardDTO) {
        // 게시물 저장 메소드
        return repository.save(boardDTO.toEntity()).getId();
    }

    @Transactional
    public List<BoardDTO> getFileList() {
        // 게시물 목록 조회 메소드
        List<Board> boardList = repository.findAll(Sort.by(Sort.Direction.DESC,"createdDate"));
        List<BoardDTO> boardDTOList = new ArrayList<>();

        for(Board board : boardList) {
            // 게시물 엔티티를 DTO로 변환해 목록에 추가
            BoardDTO boardDTO = BoardDTO.builder()
                    .id(board.getId())
                    .title(board.getTitle())
                    .content(board.getContent())
                    .origFilename((board.getOrigFilename()))
                    .filePath(board.getFilePath())
                    .createdDate(board.getCreatedDate())
                    .modifiedDate(board.getModifiedDate())
                    .build();
            boardDTOList.add(boardDTO);
        }
        return boardDTOList;
    }
    @Transactional
    public BoardDTO getFile(Long id) {
        // 게시물 상세 조회 메소드
        Board board = repository.findById(id).get();

        BoardDTO boardDTO = BoardDTO.builder()
                .id(id)
                .title(board.getTitle())
                .content(board.getContent())
                .origFilename(board.getOrigFilename())
                .filePath(board.getFilePath())
                .build();
        return boardDTO;
    }
    @Transactional
    public void deletePost(Long id) {
        // 게시물 삭제 메소드
        repository.deleteById(id);
    }
}