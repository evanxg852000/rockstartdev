## SFML Project

```bash
brew install sfml
```

https://maksimdan.gitbooks.io/sfml-and-gamedevelopement/content/chapter1.html

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