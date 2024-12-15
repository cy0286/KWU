package com.example.Proj1_2021202058.controller;

import com.example.Proj1_2021202058.domain.BoardDTO;
import com.example.Proj1_2021202058.service.BoardService;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.StringUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.util.Arrays;
import java.util.List;

@Controller
public class BoardController { // 게시물 관련 기능 담당 컨트로러
    private BoardService boardService;

    public BoardController(BoardService boardService) {
        // Boardservice 객체를 주입 받아 멤버 변수에 할당하는 생성자
        this.boardService = boardService;
    }

    @GetMapping(value = {"/", "/index.html"})
    public String list(Model model) {
        // 해당 경로로 get 요청이 들어왔을 때 호출되는 메소드
        List<BoardDTO> boardDTOList = boardService.getFileList(); // getFileList() 메소드를 호출해 게시물 리스트 가져옴
        model.addAttribute("postList",boardDTOList); // postList 이름으로 게시물 리스트를 모델에 추가함
        return "index.html"; // 렌더링 위해 해당 view 이름 반환
    }

    @GetMapping("/post")
    public String post() {
        // 해당 경로로 get 요청이 들어왔을 때 호출되는 메소드
        return "upload.html";
    }
    @PostMapping("/post")
    public String write(@RequestParam(value = "file", required = false) MultipartFile files, BoardDTO boardDTO) {
        // 해당 경로로 post 요청이 들어왔을 때 호출되는 메소드
        try {
            if (files != null && !files.isEmpty()) { // 변수가 null이 아니고 파일이 비어있지 않다면
                String origFilename = files.getOriginalFilename(); // 업로드된 파일 원본 파일 이름을 가져옴
                String extension = StringUtils.getFilenameExtension(origFilename); // 파일 이름에서 확장자 추출
                if(!isImage(extension)) { // 이미지 확장자가 아니면
                    return "redirect:/"; // 홈으로 리다이렉트
                }
                String savePath = System.getProperty("user.dir") + "\\src/main/resources/static"; // 파일 저장할 경로 설정(static 폴더)
                String filePath = savePath + "\\" + origFilename; // 파일 경로 설정
                files.transferTo(new File(filePath)); // 업로드된 파일을 지정된 경로로 전송

                if(boardDTO.getTitlelen() > 20) {
                    // 제목이 20자를 초과하면 홈으로 리다이렉트
                    return "redirect:/";
                }
                if(boardDTO.getContenttlen() > 100) {
                    // 내용이 100자를 초과하면 홈으로 리다이렉트
                    return "redirect:/";
                }
                boardDTO.setOrigFilename(origFilename); // BoardDTO 객체의 원본 파일 이름 속성 설정
                boardDTO.setFilePath(filePath); // BoardDTO 객체의 파일 경로 속성 설정
                boardService.saveFile(boardDTO); // BoardService 를 사용해 게시물 저장
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return "redirect:/"; // 홈으로 리다이렉트
    }
    @GetMapping("/post/{id}")
    public String detail(Model model, @PathVariable("id") Long id) {
        // 게시물의 상세 정보를 보여주는 메소드
        BoardDTO boardDTO = boardService.getFile(id);  // 경로의 ID 값을 매개변수로 받아 게시물의 상세 정보를 가져옴
        model.addAttribute("post", boardDTO); // 모델에 post 이름으로 게시물 정보 추가
        return "create.html"; // 렌더링 위해 해당 view 이름 반환
    }
    @GetMapping("/post/edit/{id}")
    public String edit(Model model, @PathVariable("id") Long id) {
        // 게시물 수정하기 위한 화면을 보여주는 메소드       
        BoardDTO boardDTO = boardService.getFile(id); // 경로의 ID 값을 매개변수로 받아 게시물의 상세 정보를 가져옴
        model.addAttribute("post", boardDTO); // 모델에 post 이름으로 게시물 정보 추가
        return "imageview.html"; // 렌더링 위해 해당 view 이름 반환
    }
    @PutMapping("/post/edit/{id}")
    public String update(@RequestParam(value = "file", required = false) MultipartFile files, @PathVariable("id") Long id, BoardDTO boardDTO) {
        // 게시물 업데이트 위한 메소드
        try {
            if (files != null && !files.isEmpty()) {//업로드된 파일이 존재하면
                String origFilename = files.getOriginalFilename();
                String extension = StringUtils.getFilenameExtension(origFilename);
                if(!isImage(extension)){ // 업로드된 파일이 이미지가 아니면
                    return "redirect:/"; // 홈으로 리다이렉트
                }
                String savePath = System.getProperty("user.dir") + "\\src/main/resources/static";
                String filePath = savePath + "\\" + origFilename;
               
                files.transferTo(new File(filePath)); // 파일 저장

                // BoardDTO에 파일 정보 설정
                boardDTO.setOrigFilename(origFilename);
                boardDTO.setFilePath(filePath);
            }
            else {
                // 파일이 업로드되지 않았을 경우 기존 파일 정보 사용
                BoardDTO oldFile = boardService.getFile(id);
                boardDTO.setOrigFilename(oldFile.getOrigFilename());
                boardDTO.setFilePath(oldFile.getFilePath());
            }
            if(boardDTO.getTitlelen() > 20) {
                // 제목이 20자를 초과하면 홈으로 리다이렉트
                return "redirect:/";
            }
            if(boardDTO.getContenttlen() > 100) {
                // 내용이 100자를 초과하면 홈으로 리다이렉트
                return "redirect:/";
            }
            boardService.saveFile(boardDTO); // BoardDTO를 DB에 저장
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return "redirect:/"; // 처리 후 홈으로 리다이렉트
    }
    @DeleteMapping("/post/{id}")
    public String delete(@PathVariable("id") Long id) {
        // 게시물 삭제 메소드
        boardService.deletePost(id); // ID를 기준으로 게시물 삭제
        return "redirect:/"; // 삭제 후 홈으로 리다이렉트
    }
    private boolean isImage(String extension){
        // 이미지 확장자 확인 메소드
        List<String> imageExtensions = Arrays.asList("jpg", "jpeg", "png"); // 이미지 확장자 리스트 생성
        return imageExtensions.contains(extension.toLowerCase()); // 인자로 받은 확장자를 소문자로 변환하여 리스트에 포함되어 있는지 확인
    }
}