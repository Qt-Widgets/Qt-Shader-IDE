# Qt Shader IDE
This is a GLSL shader IDE that I'm writing in Qt (and thus, inherently, C++) and a bit of OpenGL, mostly for educational purposes.

## To do
- [ ] Add ability to manage .glsl files.
- [ ] Add ability to change fonts.
- [ ] Syntax highlighting.
- [x] Basic error checking.
- [ ] UI cleanup.
- [x] Implement ```time``` uniform.
- [x] Implement ```resolution``` uniform.
- [x] Implement ```mouse``` uniform.
- [ ] Textures in vertex shader.
- [ ] ```Help``` section.
- [ ] Text formatting features.
- [x] Include all uniforms and attributes by default. (not visible to the user)

~~Doesn't work properly on Windows yet. GL context is blank on most test machines. Need to do more debugging.~~
With the new GL context code, the project works mostly fine on Windows.
