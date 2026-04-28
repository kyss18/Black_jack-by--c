package com.API.black_jack.controller;

import org.springframework.web.bind.annotation.RestController;

import com.API.black_jack.domain.data_Game;
import com.API.black_jack.service.Gameservice;

import java.util.List;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;



@RestController
public class Game_Controller {
    public final Gameservice gameservice;
    public Game_Controller(Gameservice gameservice){
        this.gameservice=gameservice;
    }

    @PostMapping("/save")
    public data_Game save(@RequestBody String rawJson) {
        return this.gameservice.add_game(rawJson);
        
    }
    @GetMapping("/history")
    public List<data_Game> get_all_history(){
        return this.gameservice.get_data_game();
    }
    
}
