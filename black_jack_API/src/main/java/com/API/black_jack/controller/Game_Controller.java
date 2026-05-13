package com.API.black_jack.controller;

import org.springframework.web.bind.annotation.RestController;

import com.API.black_jack.domain.data_Game;
import com.API.black_jack.service.Gameservice;

import java.util.List;

import org.apache.catalina.connector.Response;
import org.springframework.http.HttpStatus;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.ResponseEntity;
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
    public ResponseEntity<data_Game> save(@RequestBody String rawJson) {
        data_Game game= this.gameservice.add_game(rawJson);
        return ResponseEntity.status(HttpStatus.CREATED).body(game);
        
    }
    @GetMapping("/history")
    public ResponseEntity<List<data_Game>> get_all_history(){
        List<data_Game> game_history=this.gameservice.get_data_game();
        return ResponseEntity.ok(game_history);
    }
    
}
