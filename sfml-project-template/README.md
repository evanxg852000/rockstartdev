## SFML Project

https://maksimdan.gitbooks.io/sfml-and-gamedevelopement/content/frame_rate.html


```bash
brew install sfml
```


## Game loop
```cpp
window.setFramerateLimit(30);
sf::Clock deltaClock;
sf::Time dt;
for (;;)
{
    mySprite.Move(velocity * dt.AsSeconds());
    // ...
    dt = deltaClock.Restart();
}
```