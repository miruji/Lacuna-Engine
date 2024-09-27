# Lacuna-Engine
The engine was created in 2022 after it became clear that the previous engine was not suitable for subsequent games and merged with the Kingso game, which required a lengthy rebuild of the game, made it impossible to use for other games and genres with different mechanics, and a lack of funds to expand the project. The main task of this engine is divided into editor and launch of 2D games. The engine supports game projects, a lua script editor, a map editor, shader support, and logs.

The engine does not have bugs in itself, but some important functions are unfinished. In essence, much has either already begun to be implemented or has already been done. So, if you complete the editors and finish loading the project, then the engine will allow you to produce fast and simple 2D games.

I would also like to highlight that OpenGL + ImGui was used. C++ was chosen from-for speed in games and simply because at that time it was better for me when working, and also better when working with Lua. Now I would use Rust and forget about C++ and C as scary. In addition, I would not write such an engine now, which is why the project does not continue and is archived for free use,
since it is best to use Godot Engine at the moment, which has the same potential as this engine and even more due to the number of its contributors.

### Help
1. The project has x64 and x86, is assembled only under Windows and through Microsoft Visual Studio.
2. Here you can find only the x86 version compiled, in the folder you can find the bat files “start editor” and “start project” for launching in different modes. There you can also find ready-made blanks for 2 projects.
3. In the source folder of the engine itself you can also find only the x86 version of the libraries used, I would advise you to transfer the code to lowerCamelCase.
4. The editor itself does not allow you to run anything; to do this, as far as I remember, you need to uncomment and add some functions in the code itself. There is code for shaders, render windows, scripts and the editor itself.