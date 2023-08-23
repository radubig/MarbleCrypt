# MarbleCrypt
#### OOP Project 2023

Made by Colțoș Radu-Mihai

#### Looking for the OOP Tasks file? You can find it [here](POO_tasks.md).

## Description
MarbleCrypt is a <i> fun, fun </i> game where you can collect your very own <i> Super Crypto Aesthetic Marble </i> NFTs!

You can obtain Marbles either by buying them with <b>$MTK</b> or by fusing two other basic marbles into a brand new one!

And these marbles aren't just for looks - they generate $MTK based on a daily yield, so in time, they become more valuable and you can even turn a profit by collecting as many marbles as you can!

Are you getting too many duplicates? No problem! At any time, you may choose to burn one of your marbles, to instantly get back some tokens for buying another one.

However, be careful of demand! The price for new marbles increases exponentialy with demand, so the more you buy, the more expensive they get!

Try to collect all the 136 marbles!

## Features implemented
- Graphical interface
- **[NEW]** Save system
  - The game automatically saves your progress when you close the app
  - You can also manually save by pressing `S`
  - Marbles can generate up to a day's worth of **$MTK** while away, so open the game once a day to collect your tokens! 
- Generate new basic marbles by buying them with **$MTK**
  - Click on the shop icon to buy a new marble, or press `B`
- Fuse two basic marbles into a new, better one
  - Right-click on two marbles to select them, then click the `Fuse marbles!` button
- Collect the current yield of the marbles
  - You can press each marble to collect its individual yield
  - You can also press the `Collect all` button to collect all yields
- Burning
  - If you feel that you no longer need a particular marble, you can burn it and get back some tokens for buying other marbles
  - The amount received depends on the current price of a marble and the rarity of the marble burned
  - You can also trigger the burning of a selected marble by pressing `Backspace`
- Resizable window
- Scrolling

##### Cheats:
- `A` : Add some money to your wallet
- `G` : Generate one marble of each rarity

<small> To enable cheats, run <code>./MarbleCrypt -cheats</code> .</small>

## References & Dependencies
- [SFML](https://www.sfml-dev.org/)

## Special thanks to
- [Daniel Ghindea](https://github.com/Ghindea) for the textures
- [mcmarius](https://github.com/mcmarius) for providing templates, resources and reviewing the code

#### The look and functionality of this project was inspired by Yipy's [RealZoo](https://realzoo.itsyipy.com/).

### Disclaimer
This project is a reference to Logan Paul's *Cryptozoo*, a similar game [that was proved to be a cryptoscam](https://youtu.be/386p68_lDHA).
The use of the "Crypto coins" is purely fictional and just pokes fun at the idea of spending money on some PNG's of balls.
I do not endorse investing into cryptocoins or NFTs of any kind in real life. 