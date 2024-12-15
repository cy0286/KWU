package com.example.Proj1_2021202058.repository;

import com.example.Proj1_2021202058.domain.Board;
import org.springframework.data.jpa.repository.JpaRepository;
public interface Repository extends JpaRepository<Board, Long> {
}
