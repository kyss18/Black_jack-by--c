package com.API.black_jack.service;

import java.util.List;

import org.springframework.stereotype.Service;

import com.API.black_jack.domain.data_Game;
import com.API.black_jack.repository.Game_repository;

@Service
public class Gameservice {
    private final Game_repository game_repository;
    public Gameservice(Game_repository game_repository){
        this.game_repository=game_repository;
    }
    public data_Game add_game(String rawJson){
        data_Game game=new data_Game();
        game.setJsonData(rawJson);
        return this.game_repository.save(game);
    }
    public List<data_Game> get_data_game(){
        List<data_Game> game=this.game_repository.findAll();
        return game;
    }
    
}
