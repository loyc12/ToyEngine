#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "./objects/Object2D.hpp"
# include "./display/Viewport.hpp" // ?

class Engine // make this a static class ???
{
	private:
	// ================================ ATTRIBUTES
		// gobal var struct
		// viewport/canvas
		// object register(ies)

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Engine();
		~Engine();

	// ================================ CORE METHODS
		void init();
		void launch();
			void getInput();
			void runScripts();
			void runPhysics();
			void renderObjects();
		void close();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS

};

#endif // ENGINE_HPP