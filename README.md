# Engine

The render components register and unregister themselves to the renderer.
The renderer renders all the rendercomponents.
This is done so not all the scenes, gameobjects and components need to have a render function.

The renderer also renders the UI.
The UI consists of UI layers that can be added to an UI Manager.
UI Layers render on top of the rest of the scene.

When the observer gets deleted it unregisters its subjects.
The subjects are registered to an observer as a linked list.
This is done to increase performance a bit since the observer pattern can be slow at times.

I implemented the pimpl pattern for the XboxController and SDLInputSystem.

Levels can be loaded as a .txt or a .bin
There is a .txt so changes to the level can be made in this file by developers.

Scenes have a virtual CreateScene function to initalize the scene.
They also have a virtual OnSceneEnd function to load the next level for example.
GameObjects can be given a name and a tag.
The scene can find a gameobject by its name or a list of gameobjects by their tag.
Scenes can be marked for delete or for restart.

GameObjects can have children.
A child can be optained by index or by name.
GameObjects can be marked for delete.