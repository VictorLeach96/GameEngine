#include <sdl/SDL.h>
#include <vector>

#include "Component.h"

class Input: public Component{
	
private:

	static vector<SDL_Keycode> keys;

public:

	void awake();
	void update(float delta);
	void render();
	void destroy();

	static bool Input::poll();

	bool isDown(SDL_Keycode type);

};