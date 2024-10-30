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
