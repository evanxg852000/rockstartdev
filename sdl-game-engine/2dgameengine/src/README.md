Tut: https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
Assets:
    https://craftpix.net/
    https://itch.io
Game{
    EntityManager
    AssetManager
    KeyboarManager
    window
    renderer
    setScreen(name)
}

GameScreen{
    game
}

EntityManager: {
    screen
    vector<Entity>
}

Entity {
    manager
    processEvent(event)
    update(deltat)
    render(renderer)

}


SpriteAnimator{
    component_to_animate_an_entity_spritesheet
}
EntityNavigator{
    component_to_move_around_entity
}