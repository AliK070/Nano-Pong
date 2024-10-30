#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define SPEED_POT A2
#define PADDLE_RATE 64
#define BALL_RATE 16
#define PADDLE_HEIGHT 12
#define SCORE_LIMIT 9
#define MCU_X 12
#define PLAYER_X 115

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

bool game_over = false, win = false;
uint8_t player_score = 0, mcu_score = 0;
uint8_t ball_x = 53, ball_y = 20;
int8_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update, paddle_update;

uint8_t mcu_y = 16, player_y = 16;
uint8_t ball_speed = 5; // Starting speed of the ball

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    showLoadingScreen();
    resetGame();
}

void loop() {
    if (game_over) {
        handleGameOver();
    } else {
        updateBall();
        updatePaddles();
        drawScores();  
    }
}

void showLoadingScreen() {
    display.setCursor(40, 28);
    display.print("Hello!");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, 28);
    display.print("Welcome to Pong - AK!");
    display.display();
    delay(2000);
    display.clearDisplay();
    drawCourt();
}

void resetGame() {
    ball_x = 53; ball_y = 20;
    ball_dir_x = 1; ball_dir_y = 1;
    mcu_y = 16; player_y = 16; 
    mcu_score = 0; player_score = 0;
    game_over = false;
    ball_update = millis();
    paddle_update = millis();
    drawCourt();
}

void updateBall() {
    if (millis() > ball_update) {
        display.drawPixel(ball_x, ball_y, BLACK);
        
        // Update ball position
        ball_x += ball_dir_x;
        ball_y += ball_dir_y;

        // Check for wall collisions
        if (ball_x <= 0 || ball_x >= 127) {
            handleBallWallCollision();
            return;
        }

        if (ball_y <= 10 || ball_y >= 54) {
            ball_dir_y = -ball_dir_y;
            ball_y += ball_dir_y;
        }

        // Check paddle collisions
        if ((ball_x == PLAYER_X && ball_y >= player_y && ball_y <= player_y + PADDLE_HEIGHT) ||
            (ball_x == MCU_X && ball_y >= mcu_y && ball_y <= mcu_y + PADDLE_HEIGHT)) {
            ball_dir_x = -ball_dir_x;
            ball_x += ball_dir_x;
        }

        // Draw new ball position
        display.drawPixel(ball_x, ball_y, WHITE);
        ball_update += (BALL_RATE / ball_speed); 
    }
}

void handleBallWallCollision() {
    if (ball_x <= 0) {
        player_score++;
    } else {
        mcu_score++;
    }

    ball_speed += 20; 

    ball_dir_x = -ball_dir_x;
    ball_x += ball_dir_x;

    checkGameOver();
}

void updatePaddles() {
    if (millis() > paddle_update) {
        paddle_update += PADDLE_RATE;
        moveMcuPaddle();
        movePlayerPaddle();
    }
}

void moveMcuPaddle() {
    display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, BLACK);
    if (mcu_y + (PADDLE_HEIGHT / 2) < ball_y) mcu_y++;
    else if (mcu_y + (PADDLE_HEIGHT / 2) > ball_y) mcu_y--;
    mcu_y = constrain(mcu_y, 11, 53 - PADDLE_HEIGHT);
    display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, WHITE);
}

void movePlayerPaddle() {
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);
    if (digitalRead(UP_BUTTON) == LOW) player_y--;
    if (digitalRead(DOWN_BUTTON) == LOW) player_y++;
    player_y = constrain(player_y, 11, 53 - PADDLE_HEIGHT);
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);
}

void checkGameOver() {
    if (player_score >= SCORE_LIMIT || mcu_score >= SCORE_LIMIT) {
        win = player_score > mcu_score;
        game_over = true;
    }
}

void handleGameOver() {
    display.clearDisplay();
    display.setCursor(40, 28);
    display.print(win ? "YOU WIN!!" : "YOU LOSE!");
    display.setCursor(28, 48);
    display.print("Your Points: ");
    display.print(player_score);
    display.display();
    delay(5000);
    display.clearDisplay();
    display.setCursor(30, 28);
    display.print("Restarting...");
    display.display();
    delay(2000);
    display.clearDisplay();
    resetGame();
}

void drawScores() {
    display.fillRect(0, 0, 128, 8, BLACK);
    display.setCursor(0, 0);
    display.print(mcu_score);
    display.print("|");
    display.print(player_score);
    display.print("        Speed: ");
    display.print(ball_speed);
    display.display();
}

void drawCourt() {
    display.drawRect(0, 10, 128, 54, WHITE);
}
