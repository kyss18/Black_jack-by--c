package com.API.black_jack.repository;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.API.black_jack.domain.data_Game;

@Repository
public interface Game_repository extends JpaRepository<data_Game,Long>{

}