# Nano-Pong

## A bit about the project:
I decided to get some OLED screens from a vendor, to test them out I used an Arduino Nano paired up
with this OLED screen and two buttons. The toughest part about this project is really just the code itself, understanding how the ball travles and how it colides with the walls was a bit tough. Its a good screen, but I should have bough a slightly bigger one. 

## Materials needed: 

- Two push buttons, I would recommend bigger buttons that support keycaps, as it will be easier for you to use.
- An OLED Screen, mines in this case is is 0.96 inches in length. 
- A board to power all of these components, either an Arduino Nano or Uno, whatever works.

## The code explained: 

The game features two paddels, one that is controlled by the player and the other is a simple AI, you 
must score 9 points to win. 

The code includes the necessary libraries for SPI communication, I2C, and graphics display (Adafruit_GFX and Adafruit_SSD1306). The constants are pin defnitions and the rate of speed for the paddle and ball movement, the paddle height, score limit, and paddle positions.

Here are all of the functions with reasoning, should be quite obvious: 

```C 

//Functions
showLoadingScreen(); // Displays a welcome message before starting the game.

resetGame(); // Resets all game variables to their initial states.

updateBall(); // Handles ball movement, wall collisions, and paddle collisions. It updates the ball's position based on its current direction and speed.

handleBallWallCollision(); // Increments the score of the player or the opponent when the ball hits the wall and resets the ball position.

updatePaddles(); // Manages the movement of both the player and the AI paddle.

moveMcuPaddle(); // Moves the AI paddle based on the ball’s vertical position.

movePlayerPaddle(); // Reads button inputs to move the player’s paddle up or down.

checkGameOver(); // Checks if either player has reached the score limit.

handleGameOver(); // Displays the game result and resets the game after a delay.

drawScores(); // Updates and displays the current scores and ball speed.

drawCourt(); // Draws the game court boundaries.

```
## Putting it Together: 

Here are a few images on how everything should look. Its quite messy and my breadboard ended up being squished but it should roughly look like what I designed over here: 

### Image One:
![20241030_184108](https://github.com/user-attachments/assets/abbcf968-a1a9-4a17-9315-e03126457049)


### Image Two: 
![20241030_184156](https://github.com/user-attachments/assets/c5ac86a6-616c-4b1a-be53-fc8bdb832f08)

