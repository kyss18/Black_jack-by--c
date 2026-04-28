package com.API.black_jack.domain;

import java.time.LocalDateTime;
import java.util.UUID;

import org.hibernate.annotations.CreationTimestamp;

import com.fasterxml.jackson.annotation.JsonInclude;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name="data_blackjack")
public class data_Game {
    
    @Id                        // Đây là primary key
    @GeneratedValue(strategy = GenerationType.IDENTITY)            // Tự động tăng (1, 2, 3...)
    private Long id;
    
    @Column(unique = true)
   private String gameSession = UUID.randomUUID().toString().substring(0, 8);
    @Column(columnDefinition = "LONGTEXT") 
    private String jsonData;
     @CreationTimestamp                    // Tự động lưu thời gian tạo
    private LocalDateTime createdAt;

    public Long getId() {
        return id;
    }
    public void setId(Long id) {
        this.id = id;
    }
    public String getJsonData() {
        return jsonData;
    }
    public void setJsonData(String jsonData) {
        this.jsonData = jsonData;
    }

    
}
