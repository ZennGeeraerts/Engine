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

I implemented the pimpl pattern for the XboxController to hide the implementation of xinput.