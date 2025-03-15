#ifndef ENGINE_HPP
# define ENGINE_HPP

# include "./objects/Object2D.hpp"
# include "./display/Viewport.hpp" // ?

typedef enum : byte_t
{
	E_UNINITIALIZED = 0,
	E_INITIALIZED,
	E_RUNNING

} engineState_e;

class Engine // make this a static class ???
{
	private:
	// ================================ MEMORY METHODS

	// ================================ ATTRIBUTES
		// gobal var struct
		// viewport/canvas
		vector< Object2D > ObjectContainer;
		engineState_e state;
		objID_t maxID;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Engine();
		~Engine();

	// ================================ CORE METHODS
	void start();
	void close();
	void launch(); // calls the functions below in a loop, each of which itters on every object

	void readInputs(); // reads the inputs and updates the global var struct
	void runPhysics(); // calls the onTick() method of every object
	void runScripts(); // calls the onUpdate() method of every object
	void renderObjects();

	// ================================ OBJECTS METHODS

		Object2D *addNewObject();
		Object2D *getObjectByID( objID_t id );

		bool delObject( Object2D *obj );
		bool delObjectByID( objID_t id );

	// ================================ ACCESSORS
		objID_t getNewID();
		objID_t getState() const;



	// ================================ OPERATORS

	// ================================ METHODS

};

Engine *getEngine(); // Engine is a singleton

#endif // ENGINE_HPP