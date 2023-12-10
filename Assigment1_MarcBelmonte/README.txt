I am not entirely satisfied with the result. What I have failed to implement is the camera adjustment to the size of the loaded model. Then, I had issues implementing input alongside ImGui. When using the mouse to move or interact with ImGui windows, that input was also considered for camera movement. Additionally, there were problems with the resizing of ImGui windows and the viewport. So, while trying to prevent events coming from ImGui from interfering with the viewport, the mouse has ceased to have an effect on the application, but still works for ImGui.

I believe this also affects the mouse interaction with the application window itself, and now you can no longer close the window by clicking the close button at the top right. Now, it can only be closed by pressing the ESC key.

Apart from that, everything else is as requested:
Camera movement with: WASD + QE
Camera rotation with: UP-DOWN-RIGHT-LEFT
In the variable section, you can adjust the camera's speed.

https://github.com/Akiramei11/MyAwesomeEngine