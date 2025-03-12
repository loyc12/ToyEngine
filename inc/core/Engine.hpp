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
		void launch(); // calls the functions below in a loop, each of which itters on every object
			void readInputs(); // reads the inputs and updates the global var struct
			void runPhysics(); // calls the onTick() method of every object
			void runScripts(); // calls the onUpdate() method of every object
			void renderObjects();
		void close();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS

};

#endif // ENGINE_HPP